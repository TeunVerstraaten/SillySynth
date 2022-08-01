//
// Created by pc on 13-5-22.
//

#include "MainWindow.h"

#include "../audio/fx/EffectFactory.h"
#include "../misc/EnumMap.h"
#include "../misc/Overloaded.h"
#include "../misc/strConCat.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <cstdio>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <vector>


namespace view {
    static void glfw_error_callback(int error, const char *description) {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    MainWindow::MainWindow() {
        // Setup window
        glfwSetErrorCallback(glfw_error_callback);
        assert(glfwInit());
        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
        // GL 3.0 + GLSL 130
        const char *glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only
#endif

        // Create window with graphics context
        window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
        assert(window != nullptr);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        d_soundEngine.play();
    }

    MainWindow::~MainWindow() { // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        ImPlot::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    template<typename ENUM>
    void buildEnumSelector(const std::string &name, ENUM &anEnum) {
        const auto &stringMap = EnumMap<ENUM>::stringMap;

        auto it = stringMap.begin();
        if (ImGui::BeginTable(name.c_str(), stringMap.size(),
                              ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)) {
            for (size_t i = 0; i != stringMap.size(); i++) {
                ImGui::TableNextColumn();
                if (ImGui::Selectable(it->second.c_str(), anEnum == it->first))
                    anEnum = it->first;

                ++it;
            }
            ImGui::EndTable();
        }
    }

    void MainWindow::show() {
        bool show_demo_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::StyleColorsLight();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window) {
                ImGui::ShowDemoWindow(&show_demo_window);
                ImPlot::ShowDemoWindow();
            }

            ImGui::Begin(std::string("Charles").c_str());
            buildOscillatorPanel();
            ImGui::SameLine();
            buildBusPanel();
            ImGui::SameLine();
            buildFmPanel();
            ImGui::End();
            buildEffectWindows();

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                         clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }
    }

    void MainWindow::buildOscillatorPanel() {
        ImGui::BeginChild("oscillator panel", ImVec2(300, 800));
        auto &oscillators = d_soundEngine.oscillators();
        for (size_t i = 0; i != NUM_OSCILLATORS; ++i) {
            if (ImGui::CollapsingHeader(strConCat("osc", i).c_str(), ImGuiTreeNodeFlags_None)) {
                auto &oscillator = oscillators[i];
                ImGui::Checkbox(strConCat("on##on", i).c_str(), &oscillator.d_active);
                ImGui::PushItemWidth(100);
                ImGui::SliderFloat(strConCat("##volume", i).c_str(), &oscillator.d_volume, 0.0f, 1.0f, "VOL = %.2f",
                                   ImGuiSliderFlags_AlwaysClamp);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                ImGui::PushItemWidth(100);
                ImGui::SliderFloat(strConCat("##pan", i).c_str(), &oscillator.d_pan, -1.0f, 1.0f, "PAN = %.2f",
                                   ImGuiSliderFlags_AlwaysClamp);
                ImGui::PopItemWidth();

                ImGui::SliderInt(strConCat("##pitch", i).c_str(), &oscillator.d_pitch, -144, 144, "pitch = %d",
                                 ImGuiSliderFlags_AlwaysClamp);
                ImGui::SliderFloat(strConCat("##width", i).c_str(), &oscillator.d_width, 0.0f, 2.0f, "width = %.4f",
                                   ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp);
                ImGui::SliderInt(strConCat("##voices", i).c_str(), &oscillator.d_voices, 1, 64, "voices = %.3f",
                                 ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp);
                buildEnumSelector(strConCat("oscillator type##", i), oscillator.d_type);
            }
        }
        if (ImGui::TreeNode("osc sends##OscSend")) {
            buildOscillatorSendsPanel();
            ImGui::TreePop();
        }
        ImGui::EndChild();
    }

    void MainWindow::buildOscillatorSendsPanel() {
        auto &oscillatorSends = d_soundEngine.oscillatorSends();
        if (ImGui::BeginTable("##osc sends", NUM_BUSSES + 2)) {
            ImGui::TableNextColumn();
            for (size_t b = 0; b != NUM_BUSSES; ++b) {
                ImGui::TableNextColumn();
                ImGui::Text("%s", strConCat("Bus", b).c_str());
            }
            ImGui::TableNextColumn();
            ImGui::Text("Mstr");
            for (size_t i = 0; i != NUM_OSCILLATORS; i++) {
                ImGui::TableNextColumn();
                ImGui::Text("%s", strConCat("osc", i).c_str());
                for (size_t j = 0; j != NUM_BUSSES + 1; ++j) {
                    ImGui::TableNextColumn();
                    ImGui::DragFloat(strConCat("##bus slider", i, ", ", j).c_str(), &oscillatorSends[i][j], 0.01, 0.0f,
                                     1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
            }

            ImGui::EndTable();
        }
    }

    void MainWindow::buildBusPanel() {
        ImGui::BeginChild("bus panel", ImVec2(300, 400));
        if (ImGui::BeginTable("Fake id", NUM_BUSSES + 1)) {
            for (size_t bus = 0; bus != NUM_BUSSES; ++bus) {
                ImGui::TableNextColumn();
                ImGui::Text("%s", strConCat("Bus", bus).c_str());
            }
            ImGui::TableNextColumn();
            ImGui::Text("mstr");
            for (size_t ef = 0; ef != NUM_EFFECTS_PER_BUS; ++ef) {
                for (size_t bus = 0; bus != NUM_BUSSES + 1; ++bus) {

                    ImGui::PushID(static_cast<int>((NUM_BUSSES + 1) * ef + bus));
                    ImGui::TableNextColumn();
                    buildBusButton(bus, ef);
                    auto &effect = d_soundEngine.getBus(bus).effects()[ef];
                    auto const name = effect.getName();
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
                        size_t indices[2] = {bus, ef};
                        ImGui::SetDragDropPayload("DND_EFFECT", &indices, 2 * sizeof(size_t));
                        ImGui::Text("Swap %s", name.c_str());
                        ImGui::EndDragDropSource();
                    }
                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("DND_EFFECT")) {
                            IM_ASSERT(payload->DataSize == 2 * sizeof(size_t));
                            size_t otherBus = *static_cast<size_t *>(payload->Data);
                            size_t otherEf = *(static_cast<size_t *>(payload->Data) + 1);
                            std::swap(d_showEffectFlags[bus][ef], d_showEffectFlags[otherBus][otherEf]);
                            std::swap(d_soundEngine.getBus(bus).effects()[ef],
                                      d_soundEngine.getBus(otherBus).effects()[otherEf]);
                        }
                        ImGui::EndDragDropTarget();
                    }
                    ImGui::PopID();
                }
            }
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }

    void MainWindow::buildBusButton(size_t bus, size_t ef) {
        ImGui::BeginGroup();
        auto &effect = d_soundEngine.getBus(bus).effects()[ef];
        auto const name = effect.getName();

        if (ImGui::Button(name.c_str(), ImVec2(60, 20))) {
            if (effect.empty())
                ImGui::OpenPopup(strConCat("select effect", ef, ", ", bus).c_str());
            else
                d_showEffectFlags[bus][ef] = true;
        }

        buildEffectSelectPopUp(bus, ef);
        ImGui::SameLine();
        if (ImGui::Button("x", ImVec2(20, 20)))
            removeEffect(bus, ef);

        ImGui::EndGroup();
    }

    void MainWindow::buildEffectSelectPopUp(size_t bus, size_t ef) {
        auto &effect = d_soundEngine.getBus(bus).effects()[ef];
        if (ImGui::BeginPopupContextItem(strConCat("select effect", ef, ", ", bus).c_str())) {

            const auto &stringMap = EnumMap<audio::fx::EffectFactory::EFFECT_ENUM>::stringMap;
            for (const auto &el: stringMap) {
                if (ImGui::Selectable(el.second.c_str())) {
                    effect = audio::fx::EffectFactory::build(el.first);
                    d_showEffectFlags[bus][ef] = el.first != audio::fx::EffectFactory::EFFECT_ENUM::EMPTY;
                }
            }
            ImGui::EndPopup();
        }
    }

    void MainWindow::removeEffect(size_t bus, size_t ef) {
        d_soundEngine.getBus(bus).effects()[ef] = audio::fx::Effect{};
        d_showEffectFlags[bus][ef] = false;
    }

    void showEffect(audio::fx::Distortion &distortion, size_t id) {
        ImGui::Begin((std::string("distortion##") + std::to_string(id)).c_str());
        buildEnumSelector(std::string("type##") + std::to_string(id), distortion.type());
        ImGui::SliderFloat((std::string("##amount dist panel") + std::to_string(id)).c_str(), &distortion.amount(),
                           0.0f, 1.0f, "amnt = %.2f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::End();
    }

    void showEffect(audio::fx::Spectrum &spectrum, size_t id) {
        ImGui::Begin((std::string("spectrum##") + std::to_string(id)).c_str());

        const float frequencyResolution = SAMPLE_RATE / static_cast<float>(LOOK_AHEAD);
        static const size_t N = LOOK_AHEAD / 2 + 1;
        static float xs1[N], ys1[N];
        auto const &frequencies = spectrum.lrBuffer().leftBuffer;
        for (int i = 0; i != N; ++i) {
            xs1[i] = frequencyResolution * static_cast<float>(i);
            ys1[i] = frequencies[i];
        }
        if (ImPlot::BeginPlot("Spectrum")) {
            ImPlot::SetupAxes("Hz", "Power", ImPlotAxisFlags_LogScale | ImPlotAxisFlags_Lock, ImPlotAxisFlags_Lock);
            ImPlot::SetupAxesLimits(40, 20000, -10, 10);
            ImPlot::PlotLine(strConCat("##Spectrum panel", id).c_str(), xs1, ys1, N);
            ImPlot::EndPlot();
        }
        ImGui::End();
    }

    void showEffectWindow(audio::fx::Effect &effect) {
        assert(not effect.empty());
        std::visit(Overloaded{[](audio::fx::Empty &) {}, [&](auto &ef) { showEffect(ef, effect.id()); }},
                   effect.effectVariant());
    }

    void MainWindow::buildEffectWindows() {
        for (size_t bus = 0; bus != NUM_BUSSES + 1; ++bus)
            for (size_t ef = 0; ef != NUM_EFFECTS_PER_BUS; ++ef)
                if (d_showEffectFlags[bus][ef]) {
                    if (bus == NUM_BUSSES)
                        showEffectWindow(d_soundEngine.master().effects()[ef]);
                    else
                        showEffectWindow(d_soundEngine.busses()[bus].effects()[ef]);
                }
    }

    void MainWindow::buildFmPanel() {
        ImGui::BeginChild("FM panel", ImVec2(600, 1000));
        if (ImGui::TreeNode("Fm Matrix")) {
            ImGui::Text("FM Matrix Yay");
            if (ImGui::BeginTable("Fake id FM", NUM_OSCILLATORS)) {
                for (size_t osc1 = 0; osc1 != NUM_OSCILLATORS; ++osc1)
                    for (size_t osc2 = 0; osc2 != NUM_OSCILLATORS; ++osc2) {
                        ImGui::TableNextColumn();
                        ImGui::DragFloat(
                                strConCat("##FM slider", osc1, ",", osc2).c_str(),
                                &d_soundEngine.fmMatrix()[osc1][osc2], 0.01, 0.0f, 3.0f, "%.2f",
                                ImGuiSliderFlags_AlwaysClamp);
                    }
                ImGui::EndTable();
            }
            ImGui::TreePop();
        }
        ImGui::EndChild();
    }
} // namespace view