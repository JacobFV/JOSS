#include "view.hpp"
#include "model.hpp"
#include "controller.hpp"

int main(int argc, const char **argp) {
  
  JOSSView* view = new JOSSView();
  JOSSModel* model = new JOSSModel();
  JOSSController* controller = new JOSSController(view, model);

  controller->repl();

  return EXIT_SUCCESS;
}