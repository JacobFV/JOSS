#include <locale>  // These imports come from a stackoverflow answer on how to 
#include <codecvt> // portably convert from std::string to std::wstring
#include <string>  // https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t

#include "header.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/string.hpp"

using namespace ftxui;

class JOSSView {

public:
    JOSSView();

    void refresh();
    int get_terminal_height();

    void set_terminal_content(std::string val);
    void set_dirs(std::vector<std::string> files);
    void set_files(std::vector<std::string> files);
    void set_help_bar_text(std::string val);

private:
    // use newlines to separate elements
    std::wstring terminal_content;
    std::wstring dirs;
    std::wstring files;
    std::wstring help_bar_text;
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstring_converter; 

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