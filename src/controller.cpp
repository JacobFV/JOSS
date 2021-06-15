#include "controller.hpp"


JOSSController::JOSSController(JOSSView* view, JOSSModel* model)
    : view(view), model(model) { }

void JOSSController::repl() {
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

    model->quit();
}

void JOSSController::update_view() {
    // grabs data from model and put it in the view
    
    // print terminal content
    view->set_terminal_content(model->all_past_content + "\n" 
        + fmt_cmd(model->curr_cmd(), model->cursor_x));

    // print dirs
    view->set_dirs(
        model->dirs.begin() + model->dirs_pos, 
        model->dirs.begin() + std::min(
            model->dirs_pos + NUM_DIRS,
            static_cast<int>(model->dirs.size())
        )
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