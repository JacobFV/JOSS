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

std::string fmt_cmd(CMD cmd, int cursor_x) {
    // format command consistantly across the program
    std::string fmtd_cmd = cmd->first + " $ " + cmd->second;
    if (cursor_x != -1) {
        fmtd_cmd.insert(cmd->first.length() + 3 + cursor_x, "_");
    }
    return fmtd_cmd;
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