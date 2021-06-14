#include "header.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/string.hpp"

using namespace ftxui;

class JOSSView {

public:
    // the model can directly edit these strings
    // use newlines to separate elements
    std::wstring terminal_content;
    std::wstring dirs;
    std::wstring files;
    std::wstring help_bar_text;

    JOSSView();

    void refresh();

private:
    Element document = vbox({
            hbox({
                text(terminal_content) | flex,
                vbox({
                    text(dirs), 
                    separator(),
                    text(files),
                })
            }),
            text(help_bar_text),
        });
    Screen screen = Screen::Create(Dimension::Full(), Dimension::Full());
};