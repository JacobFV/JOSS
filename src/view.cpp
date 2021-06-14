#include "view.hpp"

JOSSView::JOSSView() {

    auto summary = [&] {
        auto content = vbox({
            hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
            hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
            hbox({text(L"- active: "), text(L"4") | bold}) | color(Color::RedLight),
            hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
        });
        return window(text(L" Summary "), content);
    };

    this->document = 
        vbox({
            hbox({
                text() | flex,
                vbox()
            })
        });
    /*
        vbox({
            hbox({
                summary(),
                summary(),
                summary() | flex,
            }),
            summary(),
            summary(),
        });*/
}

void display(
    std::string content, 
    std::vector<std::string> dirs,
    std::vector<std::string> files,
    std::string help_text,
    ) {
    // everything is already defined by now
    Render(screen, document);
    std::cout << screen.ToString() << std::endl;
}