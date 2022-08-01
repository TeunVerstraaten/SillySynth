cmake_minimum_required(VERSION 3.22)
project(synth)
add_subdirectory("third_party/portaudio")
add_subdirectory("third_party/fftw-3.3.10")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Werror -Wall -Wextra")

add_executable(synth main.cpp audio/Oscillator.cpp audio/Oscillator.h audio/Defines.h view/MainWindow.cpp view/MainWindow.h third_party/implot-master/implot.cpp third_party/implot-master/implot_demo.cpp third_party/implot-master/implot_items.cpp third_party/imgui/imgui.cpp third_party/imgui/imgui_demo.cpp third_party/imgui/imgui_draw.cpp third_party/imgui/imgui_tables.cpp third_party/imgui/imgui_widgets.cpp third_party/imgui/backends/imgui_impl_opengl3.cpp third_party/imgui/backends/imgui_impl_glfw.cpp audio/SoundEngine.cpp audio/SoundEngine.h audio/ScopedPaHandler.cpp audio/ScopedPaHandler.h misc/EnumMap.h misc/EnumMap.cpp audio/math.h audio/LrBuffer.cpp audio/LrBuffer.h audio/Bus.cpp audio/Bus.h audio/fx/Effect.cpp audio/fx/Effect.h audio/fx/Distortion.cpp audio/fx/Distortion.h audio/fx/Empty.h misc/Overloaded.h misc/UniqueId.cpp misc/UniqueId.h misc/strConCat.h audio/fx/EffectFactory.cpp audio/fx/EffectFactory.h audio/fx/Spectrum.cpp audio/fx/Spectrum.h)

target_link_libraries(portaudio_static)
TARGET_LINK_LIBRARIES(synth pthread rt asound portaudio GL glfw fftw3)
target_include_directories(synth PUBLIC "third_party/imgui" "third_party/imgui/backends")
