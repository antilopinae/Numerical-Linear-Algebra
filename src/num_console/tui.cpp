#include "tui.h"

// #include <Eigen/Dense>
// #include <ftxui/dom/elements.hpp>
// #include <gmtl/Matrix.h>
// #include <gmtl/gmtl.h>

#include "buildinfo.h"
#include "calc/calc.h"

#include <array>      // for array
#include <atomic>     // for atomic
#include <chrono>     // for operator""s, chrono_literals
#include <cmath>      // for sin
#include <functional> // for ref, reference_wrapper, function
#include <memory>     // for allocator, shared_ptr, __shared_ptr_access
#include <stddef.h>   // for size_t
#include <string> // for string, basic_string, char_traits, operator+, to_string
#include <thread> // for sleep_for, thread
#include <utility> // for move
#include <vector>  // for vector

#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/component/component_base.hpp"    // for ComponentBase, Component
#include "ftxui/component/component_options.hpp" // for MenuOption, InputOption
#include "ftxui/component/event.hpp"             // for Event, Event::Custom
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp" // for text, color, operator|, bgcolor, filler, Element, vbox, size, hbox, separator, flex, window, graph, EQUAL, paragraph, WIDTH, hcenter, Elements, bold, vscroll_indicator, HEIGHT, flexbox, hflow, border, frame, flex_grow, gauge, paragraphAlignCenter, paragraphAlignJustify, paragraphAlignLeft, paragraphAlignRight, dim, spinner, LESS_THAN, center, yframe, GREATER_THAN
#include "ftxui/dom/flexbox_config.hpp" // for FlexboxConfig
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui
#include "ftxui/screen/color_info.hpp" // for ColorInfo
#include "ftxui/screen/terminal.hpp"   // for Size, Dimensions

using namespace ftxui;
using namespace std;

class lab_renderer {
private:
public:
  std::vector<std::string> tab_values{
      "tab_1",
      "tab_2",
      "tab_3",
  };
  int tab_selected = 0;
  Component tab_toggle = Toggle(&tab_values, &tab_selected);
  std::vector<std::string> tab_1_entries{
      "Forest",
      "Water",
      "I don't know",
  };
  int tab_1_selected = 0;
  std::vector<std::string> tab_2_entries{
      "Hello",
      "Hi",
      "Hay",
  };
  int tab_2_selected = 0;
  std::vector<std::string> tab_3_entries{
      "Table",
      "Nothing",
      "Is",
      "Empty",
  };
  int tab_3_selected = 0;
  Component tab_container = Container::Tab(
      {
          Radiobox(&tab_1_entries, &tab_1_selected),
          Radiobox(&tab_2_entries, &tab_2_selected),
          Radiobox(&tab_3_entries, &tab_3_selected),
      },
      &tab_selected);
  Component lab1_container = Container::Vertical({
      tab_toggle,
      tab_container,
  });
  auto get_lab_renderer() {
    auto lab_renderer = Renderer(lab1_container, [&] {
      return vbox({
                 tab_toggle->Render(),
                 separator(),
                 tab_container->Render(),
             }) |
             border;
    });
    return lab_renderer;
  }
};

Component getTui(int &shift, ScreenInteractive &screen) {
  // ----
  // HTOP
  // ----

  auto my_graph = [&shift](int width, int height) {
    std::vector<int> output(width);
    for (int i = 0; i < width; ++i) {
      float v = 0.5f;
      v += 0.1f * sin((i + shift) * 0.1f);
      v += 0.2f * sin((i + shift + 10) * 0.15f);
      v += 0.1f * sin((i + shift) * 0.03f);
      v *= height;
      output[i] = (int)v;
    }
    return output;
  };

  auto htop = Renderer([&] {
    auto frequency = vbox({
        text("Frequency [Mhz]") | hcenter,
        hbox({
            vbox({
                text("2400 "),
                filler(),
                text("1200 "),
                filler(),
                text("0 "),
            }),
            graph(std::ref(my_graph)) | flex,
        }) | flex,
    });

    auto utilization = vbox({
        text("Utilization [%]") | hcenter,
        hbox({
            vbox({
                text("100 "),
                filler(),
                text("50 "),
                filler(),
                text("0 "),
            }),
            graph(std::ref(my_graph)) | color(Color::RedLight),
        }) | flex,
    });

    auto ram = vbox({
        text("Ram [Mo]") | hcenter,
        hbox({
            vbox({
                text("8192"),
                filler(),
                text("4096 "),
                filler(),
                text("0 "),
            }),
            graph(std::ref(my_graph)) | color(Color::BlueLight),
        }) | flex,
    });

    return hbox({
               vbox({
                   frequency | flex,
                   separator(),
                   utilization | flex,
               }) | flex,
               separator(),
               ram | flex,
           }) |
           flex;
  });

  // ----
  // Labs
  // ----

  auto lab1_renderer = lab_renderer();
  auto lab2_renderer = lab_renderer();

  // ----
  // Tabs
  // ----

  int tab_index = 0;
  std::vector<std::string> tab_entries = {"htop", "Lab 1", "Lab 2"};
  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content = Container::Tab(
      {
          htop,
          lab1_renderer.get_lab_renderer(),
          lab2_renderer.get_lab_renderer(),
      },
      &tab_index);

  auto exit_button =
      Button("Exit", [&] { screen.Exit(); }, ButtonOption::Ascii());

  auto main_container = Container::Vertical({
      Container::Horizontal({
          tab_selection,
          exit_button,
      }),
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("FTXUI Demo") | bold | hcenter,
        hbox({
            tab_selection->Render() | flex,
            exit_button->Render(),
        }),
        tab_content->Render() | flex,
    });
  });

  return main_renderer;
}

/*

string a{"12"}, b{"90"};
auto input_a = Input(&a, "");
auto input_b = Input(&b, "");
auto component = Container::Vertical({input_a, input_b});*/

// Component getTui() {
//   return Renderer(component, [&] {
//     Calc::TestGMTL();
//     auto sum = Calc::Sum(stoi(a), stoi(b));
//
//     using Eigen::MatrixXd;
//     MatrixXd m(2, 2);
//
//     gmtl::Matrix22f test_matrix;
//     test_matrix.set(1, 4, 3, 4);
//
//     Calc::TestIterativeMethods();
//
//     return vbox({
//                text("CalcConsole " + BuildInfo::Version),
//                text("Built: " + BuildInfo::Timestamp),
//                text("SHA: " + BuildInfo::CommitSHA),
//                separator(),
//                input_a->Render(),
//                input_b->Render(),
//                separator(),
//                text("Sum: " + to_string(sum)),
//                border(text("The element")),
//            }) |
//            border;
//   });
// }
