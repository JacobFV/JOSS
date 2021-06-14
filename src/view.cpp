#include "view.hpp"

JOSSView::JOSSView() {
}

void JOSSView::refresh() {
    // everything is already defined by now
    Render(screen, document);
    std::cout << screen.ToString() << std::endl;
}