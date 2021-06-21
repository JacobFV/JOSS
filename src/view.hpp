#ifndef JOSS_VIEW
#define JOSS_VIEW

#include "header.hpp"
#include "controller.hpp"

#include "ftxui/dom/node.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/screen/box.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/input.hpp"

using namespace ftxui;

class JOSSView {

public:
    JOSSView();

    void refresh();
    int get_terminal_height();
    void set_terminal_content(JOSSController* controller);
    void set_dirs(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
    void set_files(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
    void set_help_bar_text(std::string val);
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();

private:
    // use newlines to separate elements
    std::wstring terminal_content;
    std::wstring dirs_content;
    std::wstring files_content;
    int panel_size = 24;
    std::wstring input_contents;

    Elements terminal_lines_texts = { };
    Elements dirs_texts = { };
    Elements files_texts = { };

    Component cmd_input = ftxui::Input(&input_contents, "");
    Component renderer =
        ResizableSplitRight(
            Renderer([&] {return vbox({
                text(L"Folders"),
                vbox(dirs_texts), 
                separator(),
                text(L"Files"),
                vbox(files_texts),
            }); }),
            Renderer(cmd_input, [&] {return vbox(this->terminal_lines_texts); }),
            &panel_size);
};

#endif
