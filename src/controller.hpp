#ifndef JOSS_CONTROLLER
#define JOSS_CONTROLLER

#include "header.hpp"
#include "view.hpp"
#include "model.hpp"


class JOSSController {
public:
    JOSSView* view;
    JOSSModel* model;
    
    JOSSController();

    void start();
    void update_view();
    void handle_enter(std::string cmd);
};

#endif