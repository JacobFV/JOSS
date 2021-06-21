#ifndef JOSS_CONTROLLER
#define JOSS_CONTROLLER

#include "header.hpp"
#include "view.hpp"
#include "model.hpp"


class JOSSController {
public:
    JOSSController();

    void repl();

private:
    JOSSView* view;
    JOSSModel* model;

    void update_view();
};

#endif