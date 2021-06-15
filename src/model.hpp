#include "header.hpp"


class JOSSModel {
public:

    std::string cwd; // does not include trailing `/`

    std::vector<std::string> dirs = std::vector<std::string>();
    std::vector<std::string> files = std::vector<std::string>();
    Sorting sorting = Sorting::byName;

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

    void edit_file(std::string filename); // open file in editor
    void run_program(std::string filename); // run file marked for execution
    void change_directory(std::string dirname); // change directory
    void set_sorting(std::string type); // set sorting for dirs and files
    std::string display_file(std::string filename); // display file contents in terminal
    std::string get_file_info(std::string filename); // show system information on file
    void move_file(std::string filename, std::string subdir); // move file to subdir
    void remove_file(std::string filename);// delete file
    void quit(); // quit application
    void print_help(); // print help information

    // backend functions
    std::string get_time();
    void update_dirs_listing(); // `..` should always be a valid subdir
    void update_files_listing();

    // utility functions
    CMD curr_cmd();
    void print_lines(std::vector<std::string> lines);
    template<class Iterator> int get_dir_id(Iterator it);
    template<class Iterator> int get_file_id(Iterator it);
};

enum Sorting { byDate, byName, bySize };