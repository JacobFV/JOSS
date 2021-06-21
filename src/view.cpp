#include "view.hpp"

JOSSView::JOSSView() {
    
}


void JOSSView::refresh() {
    // everything is already defined by now
    //screen.Print();
    screen.Loop(all_components);
    //Render(screen, document);
    //std::cout << screen.ToString() << std::endl;
}


 int JOSSView::get_terminal_height() {
    return 80;// screen.dimy(); - 2;;
}


 void JOSSView::set_terminal_content(std::vector<std::string> lines,
                                     CMD current_command) {
    terminal_lines_texts.clear();
    for(auto line : lines) {
        terminal_lines_texts.push_back(
            ftxui::text(to_wstring(line)));
    }
    terminal_lines_texts.push_back(
        ftxui::hbox({
            ftxui::text(current_command->first + " $ ")
        })
    )
}


void JOSSView::set_dirs(std::vector<std::string>::iterator dir, 
                        std::vector<std::string>::iterator dirs_end) {
    dirs_texts.clear();
    int i = 0;
    while(dir != dirs_end) {
        dirs_texts.push_back(
            ftxui::text(to_wstring(std::to_string(i++) + " " + *dir++)));
    }
}


void JOSSView::set_files(std::vector<std::string>::iterator file,
                         std::vector<std::string>::iterator files_end) {
    files_texts.clear();
    int i = 0;
    while(file != files_end) {
        files_texts.push_back(
            ftxui::text(to_wstring(std::to_string(i++) + " " + *file++)));
    }
}
