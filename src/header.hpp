#ifndef HEADER
#define HEADER

#include <vector>
#include <string>
#include <iostream>

typedef std::pair<std::string, std::string> CMD;

std::string fmt_cmd(CMD cmd, int cursor_x) {
    // format command consistantly across the program
    static std::string fmtd_cmd;
    fmtd_cmd = cmd.first + " $ " + cmd.second;
    if (cursor_x != -1) fmtd_cmd.insert(cmd.first.length() + 3 + cursor_x, "_");
    return fmtd_cmd;
}

// generated from https://patorjk.com/software/taag/#p=display&f=Impossible&t=Joss
const std::vector<std::string> WELCOME_CONTENT = {
        "              __       __           __          __       ", 
        "             /\\ \\     /\\ \\         / /\\        / /\\      ", 
        "             \\ \\ \\   /  \\ \\       / /  \\      / /  \\     ", 
        "             /\\ \\_\\ / /\\ \\ \\     / / /\\ \\__  / / /\\ \\__  ", 
        "            / /\\/_// / /\\ \\ \\   / / /\\ \\___\\/ / /\\ \\___\\ ", 
        "   _       / / /  / / /  \\ \\_\\  \\ \\ \\ \\/___/\\ \\ \\ \\/___/ ", 
        "  /\\ \\    / / /  / / /   / / /   \\ \\ \\       \\ \\ \\       ", 
        "  \\ \\_\\  / / /  / / /   / / /_    \\ \\ \\  _    \\ \\ \\      ", 
        "  / / /_/ / /  / / /___/ / //_/\\__/ / / /_/\\__/ / /      ", 
        " / / /__\\/ /  / / /____\\/ / \\ \\/___/ /  \\ \\/___/ /       ", 
        " \\/_______/   \\/_________/   \\_____\\/    \\_____\\/        ",                              
        "   Jacob's      Operating      System      Shell         ",
        "",
        "Welcome to JOSS! Please use key bindings listed on the bottom bar" +
        " and directory/file identifiers listed in the right panel to interface" +
        " with your operating system"
};

#endif