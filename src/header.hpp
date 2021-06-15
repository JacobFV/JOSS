#ifndef HEADER
#define HEADER

#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <exception>
#include <csignal>
#include <fstream>
#include <iostream>

// copied from assignment1 template
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>


const int WINDOW_HEIGHT = 5; 
const int MAX_PATH_SIZE = 65536;

typedef std::pair<std::string, std::string> CMD;


const int NUM_DIRS = 5;
const int NUM_FILES = 5;

const std::wstring HELP_BAR_TEXT = 
    L"E edit | R run | C cd | S sort | I info | D display | M move | R remove | Q quit | N next | P prev | H help";

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
        "Welcome to JOSS! Please use key bindings listed on the bottom bar",
        " and directory/file identifiers listed in the right panel to interface",
        " with your operating system.",
        "Use the N and P commands to browse through the working directory.",
        "Use up, down, right, left arrow keys to navigate through command history."
        "Type HELP for more assistance using JOSS."
};

const std::vector<std::string> HELP_MESSAGE = {
    "How to use JOSS:",
    "Enter a command (case-insensitive) followed by space-padded parameters"
    "",
    "Commands:",
    "EDIT <file_identifier>",
    "Opens <file_identifier> in an editor. aliases: E",
    "",
    "RUN <file_identifier>",
    "Attempts to execute <file_identifier>. aliases: R EXECUTE X",
    "",
    "CHANGE <dir_identifier>",
    "Changes directory to <subdir_identifier>. aliases: C CD CH",
    "",
    "SORT (NAME|DATE|SIZE)",
    "Set files and directory sorting by name, date, or size. Note: this function is not implemented. Aliases: S",
    "",
    "DISPLAY <file_identifier>",
    "Display files contents. Aliases D DISP CAT PRINT",
    ""
    "INFO <file_identifier>",
    "Displays system info about a file. Aliases I",
    "",
    "MOVE <file_identifier> <dir_identifier>",
    "Moves <src_file> to <subdir>. This command does not rename a file. Aliases M MV",
    ""
    "REMOVE <file_identifier>",
    "Deletes the file. Aliases: R DEL DELETE",
    "",
    "QUIT",
    "Quits JOSS. Aliases Q EXIT GOODBYE",
    "",
    "TIME",
    "Prints system clock time. Aliases T",
    "",
    "HELP",
    "Prints this help page. Aliases H",
    ""
};

const std::string NEWLN = "\n";

extern std::string fmt_cmd(CMD cmd, int cursor_x);
extern std::string make_string_lowercase(std::string string);

class CommandExecutionException : public std::exception {
public:
    std::string reason = "";

    CommandExecutionException(std::string reason);

    const char* what();
};
class CommandParsingException : public std::exception {
public:
    std::string reason = "";

    CommandParsingException(std::string reason);

    const char* what();
};

#endif