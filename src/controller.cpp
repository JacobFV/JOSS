#ifndef JOSS_CONTROLLER_DEF
#define JOSS_CONTROLLER_DEF

#include "controller.hpp"


JOSSController::JOSSController() {
    view = new JOSSView();
    model = new JOSSModel();
}

void JOSSController::start() {
    update_view();
}

void JOSSController::update_view() {
    // grabs data from model and put it in the view

    // print dirs
    view->set_dirs(
        model->dirs.begin() + model->dirs_pos, 
        model->dirs.begin() + std::min(
            model->dirs_pos + NUM_DIRS,
            static_cast<int>(model->dirs.size()))
    );

    // print files
    view->set_files(
        model->files.begin() + model->files_pos, 
        model->files.begin() + std::min(
            model->files_pos + NUM_FILES,
            static_cast<int>(model->files.size())
        )
    );

    // print terminal content
    view->set_terminal_content(this);

    view->refresh(); // TODO: this may not be necesary
}


void JOSSController::handle_enter(std::string cmd) {
    // just enter logic
    this->model->print_lines({this->model->cwd + " $ " + cmd});
    this->model->exec_cmd(cmd);
    this->model->start_new_cmd_line();
    this->update_view();
}

#endif