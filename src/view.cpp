#include "view.hpp"

JOSSView::JOSSView() {
    
}


void JOSSView::refresh() {
    // everything is already defined by now
    Render(screen, document);
    std::cout << screen.ToString() << std::endl;
}


 int JOSSView::get_terminal_height() {
    return screen.dimy(); - 2;;
}


 void JOSSView::set_terminal_content(std::string val) {
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    terminal_content.assign(wstring_converter.from_bytes(val));
}


void JOSSView::set_dirs(std::vector<std::string>::iterator dir, std::vector<std::string>::iterator dirs_end) {
    std::string dirs8 = "";
    int i = 0;
    while(dir != dirs_end) {
        dirs8.append(std::to_string(i++) + " " + *dir++);
        // this condition prevents there being a newline on the final element
        if(dir != dirs_end)
            dirs8.append(NEWLN);
    }
    // convert to string format usable by FXTUI
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    this->dirs_content.assign(wstring_converter.from_bytes(dirs8));
}


void JOSSView::set_files(std::vector<std::string>::iterator file, std::vector<std::string>::iterator files_end) {
    std::string files8 = "";
    int i = 0;
    while(file != files_end) {
        files8.append(std::to_string(i++) + " " + *file++);
        // this condition prevents there being a newline on the final element
        if(file != files_end)
            files8.append(NEWLN);
    }
    // convert to string format usable by FXTUI
    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    this->files_content.assign(wstring_converter.from_bytes(files8));
}
