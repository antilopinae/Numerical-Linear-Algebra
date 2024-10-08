#include "ftxui/screen/color.hpp"
#include "ftxui/screen/color_info.hpp"
#include "ftxui/screen/terminal.hpp"
#include "tui.h"
#include <ftxui/component/screen_interactive.hpp>

int main(int argc, char **argv) {
  int shift = 0;

  auto screen = ftxui::ScreenInteractive::Fullscreen();

  std::atomic<bool> refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      // The |shift| variable belong to the main thread. `screen.Post(task)`
      // will execute the update on the thread where |screen| lives (e.g. the
      // main thread). Using `screen.Post(task)` is threadsafe.
      screen.Post([&] { shift++; });
      // After updating the state, request a new frame to be drawn. This is done
      // by simulating a new "custom" event to be handled.
      screen.Post(ftxui::Event::Custom);
    }
  });

  screen.Loop(getTui(shift, screen));
  refresh_ui_continue = false;
  refresh_ui.join();

  return 0;
}
