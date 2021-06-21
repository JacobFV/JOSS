#include "header.hpp"

#include "ftxui/dom/node.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/screen/box.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

class JOSSView {

public:
    JOSSView();

    void refresh();
    int get_terminal_height();

    void set_terminal_content(std::string val);
    void set_dirs(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
    void set_files(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
    void set_help_bar_text(std::string val);

private:
    // use newlines to separate elements
    std::wstring terminal_content;
    std::wstring dirs_content;
    std::wstring files_content;
    int panel_size = 24;

    Elements terminal_lines_texts = { };
    Elements dirs_texts = { };
    Elements files_texts = { };

    Component all_components =
        ResizableSplitRight(
            Renderer([this] {return vbox({
                text(L"Folders"),
                vbox(dirs_texts), 
                separator(),
                text(L"Files"),
                vbox(files_texts),
            }); }),
            Renderer([this] {return vbox(terminal_lines_texts) }),
            &panel_size);
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
};