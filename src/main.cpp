#include "header.hpp"
#include "controller.hpp"

int main(int argc, const char **argp) {

  JOSSController* controller = new JOSSController();

  controller->repl();

  return EXIT_SUCCESS;
}