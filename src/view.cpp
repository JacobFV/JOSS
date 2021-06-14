#include "view.hpp"

JOSSView::JOSSView() {
    
}

void JOSSView::refresh() {
    // everything is already defined by now
    Render(screen, document);
    std::cout << screen.ToString() << std::endl;
}

inline int JOSSView::get_terminal_height() {
    return screen.dimy(); - 2;;
}

inline void JOSSView::set_terminal_content(std::string val) {
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    terminal_content.assign(wstring_converter.from_bytes(val));
}

inline void JOSSView::set_dirs(std::string val) {
}

inline void JOSSView::set_files(std::vector<std::string> files) {
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    terminal_content.assign(wstring_converter.from_bytes(val));
}

inline void JOSSView::set_help_bar_text(std::string val) {
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    terminal_content.assign(wstring_converter.from_bytes(val));
}
