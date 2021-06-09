#include "view.hpp"
#include "model.hpp"

int main(int argc, const char **argp) {
  
  JOSSView* view = new JOSSView();
  JOSSModel* model = new JOSSModel(view);

  model->start();

  return EXIT_SUCCESS;
}