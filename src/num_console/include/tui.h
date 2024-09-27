#include <ftxui/dom/table.hpp>     // for Table, TableSelection
#include <ftxui/screen/screen.hpp> // for Screen
#include <iostream>                // for endl, cout, ostream
#include <string>                  // for basic_string, allocator, string
#include <vector>                  // for vector

#include "ftxui/dom/node.hpp" // for Render
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui

#include <memory> // for shared_ptr, __shared_ptr_access

#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp" // for separator, gauge, text, Element, operator|, vbox, border

ftxui::Component getTui(int &shift, ftxui::ScreenInteractive &screen);
