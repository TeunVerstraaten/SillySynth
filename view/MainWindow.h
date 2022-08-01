//
// Created by pc on 13-5-22.
//

#ifndef SYNTH_MAINWINDOW_H
#define SYNTH_MAINWINDOW_H

#include "../audio/Defines.h"
#include "../audio/SoundEngine.h"

#include <GLFW/glfw3.h>

namespace view {

    class MainWindow {
      public:
        MainWindow();
        ~MainWindow();
        void show();

      private:
        void buildOscillatorPanel();
        void buildOscillatorSendsPanel();
        void buildBusPanel();
        void buildEffectWindows();
        void buildBusButton(size_t bus, size_t ef);
        void buildEffectSelectPopUp(size_t bus, size_t ef);
        void buildFmPanel();
        void removeEffect(size_t bus, size_t ef);

        GLFWwindow* window;

        audio::SoundEngine                                                d_soundEngine;
        std::array<std::array<bool, NUM_EFFECTS_PER_BUS>, NUM_BUSSES + 1> d_showEffectFlags = {{{false}}};
    };
} // namespace view

#endif // SYNTH_MAINWINDOW_H
