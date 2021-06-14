#include <locale>  // These imports come from a stackoverflow answer
#include <codecvt> // on how to convert from std::string to std::wstring
#include <string>  // https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t

#include "header.hpp"
#include "view.hpp"
#include "model.hpp"

class JOSSController {
public:
    JOSSController(JOSSView* view, JOSSModel* model);

    void start();

private:
    JOSSView* view;
    JOSSModel* model;

    // wstring conversion: https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstring_converter; 

    void update_view();
}