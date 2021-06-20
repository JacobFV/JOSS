#include "controller.hpp"

JOSSController::JOSSController() {
    view = new JOSSView();
    model = new JOSSModel();
}

void JOSSController::repl() {
    char key; 
    //std::string s;
    model->start_new_cmd_line();
    update_view();

    // main read-eval-print loop
    while(!model->isDone) {

        // get key event
        // TODO
        key = 'h';
        sleep(3);
        // parse
        model->handle_key_event(key);
        std::cout << "Handled key" << std::endl;
        // maybe update viewport
        update_view();
    }

    model->quit();
}

void JOSSController::update_view() {
    // grabs data from model and put it in the view
    
    // print terminal content
    view->set_terminal_content(model->all_past_content + "\n" 
        + fmt_cmd(model->curr_cmd(), model->cursor_x));

    // print dirs
    view->set_dirs(
        model->files.begin() + model->files_pos, 
        model->files.begin() + std::min(
            model->files_pos + NUM_FILES,
            static_cast<int>(model->files.size()))
    );

    // print files
    view->set_files(
        model->files.begin() + model->files_pos, 
        model->files.begin() + std::min(
            model->files_pos + NUM_FILES,
            static_cast<int>(model->files.size())
        )
    );

    view->refresh(); // TODO: this may not be necesary
}