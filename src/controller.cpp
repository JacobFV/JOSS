#include "controller.hpp"


JOSSController::JOSSController(JOSSView* view, JOSSModel* model)
    : view(view), model(model) { }

void JOSSController::start() {
    int key;
    model->start_new_cmd_line();

    // main read-eval-print loop
    while(!model->isDone) {
        // get key event
        key = getchar();
        // parse
        model->handle_key_event(key);
        // maybe update viewport
        update_view();
    }
}

void JOSSController::update_view() {
    // grab data from model and put it in the view
    

    // print to terminal
    // I will have to modify this code to make 
    // everything fit vertically and horizontally
    int terminal_height = ?;
    view->terminal_content.clear();
    for(int i = std::max(model->all_content.size - terminal_height, 
                         terminal_height);
        i < model->all_content.size; 
        i++) {

        // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
        view->terminal_content.append(wstring_converter.from_bytes(line));

        if (i != model->all_content.size-1)
            view->terminal_content.append(L"\n");
    }

    // print dirs
    view->dirs->

    // print files

    // set help bar text

    view->refresh(); // TODO: this may not be necesary
}