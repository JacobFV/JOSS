#include "header.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/string.hpp"

using namespace ftxui;

class JOSSView {

public:
    // the model can directly edit these strings
    std::string terminal_content;
    std::vector<std::string> dirs;
    std::vector<std::string> files;
    std::string help_bar_text;

    JOSSView();

    void refresh();

private:
    Element document;
    Screen screen = Screen::Create(Dimension::Full(), Dimension::Full());
};