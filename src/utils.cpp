// for std::string lowercase
// from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
#include <algorithm>
#include <cctype>
#include <string>

#include "header.hpp"

std::string make_string_lowercase(std::string string) {
    // this transform implementation is copied from
    // https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
    //std::transform(string.data.begin(), string.data.end(), string.data.begin(),
    //    [](unsigned char c){ return std::tolower(c); });
    //TODO
    return string;
}

CommandExecutionException::CommandExecutionException(std::string reason) {
    this->reason = reason;
}
const char* CommandExecutionException::what() {
    return reason.c_str();
}


CommandParsingException::CommandParsingException(std::string reason) {
    this->reason = reason;
}
const char* CommandParsingException::what() {
    return reason.c_str();
}