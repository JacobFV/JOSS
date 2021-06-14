#include "header.hpp"


class JOSSModel {
public:

    std::string cwd; // does not include trailing `/`

    std::vector<std::string> dirs = std::vector<std::string>();
    std::vector<std::string> files = std::vector<std::string>();
    Sorting dirsSorting = Sorting::byName;
    Sorting filesSorting = Sorting::byName;

    int dirs_pos = 0; // which subset [dirs_pos, dis_pos+5] of dirs to display
    int files_pos = 0; // which subset [dirs_pos, dis_pos+5] of files to display
    int cursor_x = 0; // location to insert "_" in string
    int cursor_y = 0; // which command is being edited

    std::string all_past_content; // lines should be seaparated by newline chars
    std::vector<CMD> all_cmds;

    bool isDone = false; // signal for controller to terminate the REPL

    JOSSModel();

    void handle_key_event(int key);

    void start_new_cmd_line();
    void exec_cmd();

    std::string get_cwd();
    std::string get_time();
    std::string get_file_info(std::string filename);
    void edit_file(std::string filename);
    void run_program(std::string filename);
    void change_directory(std::string dirname); // might be `..`
    void remove_file(std::string filename);
    void quit(); // close any resources used

    void get_dirs_in_cwd();
    void get_files_in_cwd();

    CMD curr_cmd();
    void print_lines(std::vector<std::string> lines);
};

enum Sorting { byDate, byName };