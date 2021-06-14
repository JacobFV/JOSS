#include "header.hpp"
#include "view.hpp"
#include "model.hpp"

class JOSSController {
public:
    JOSSController(JOSSView* view, JOSSModel* model);

    void repl();

private:
    JOSSView* view;
    JOSSModel* model;

    void update_view();
}