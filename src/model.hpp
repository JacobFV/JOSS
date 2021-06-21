#ifndef JOSS_MODEL
#define JOSS_MODEL

#include "header.hpp"
#include "controller.hpp"


class JOSSModel {
public:

    std::string cwd; // does not include trailing `/`

    std::vector<std::string> dirs = std::vector<std::string>();
    std::vector<std::string> files = std::vector<std::string>();
    //enum Sorting sorting = Sorting::byName;

    int dirs_pos = 0; // which subset [dirs_pos, dis_pos+5] of dirs to display
    int files_pos = 0; // which subset [dirs_pos, dis_pos+5] of files to display

    std::vector<std::string> all_past_terminal_content;

    JOSSModel();

    void handle_enter(std::string cmd);
    void start_new_cmd_line();
    void exec_cmd(std::string cmd);

    void edit_file(std::string filename); // open file in editor
    void run_program(std::string filename); // run file marked for execution
    void change_directory(std::string dirname); // change directory
    void set_sorting(std::string type); // set sorting for dirs and files
    void display_file(std::string filename); // display file contents in terminal
    void get_file_info(std::string filename); // show system information on file
    void move_file(std::string filename, std::string subdir); // move file to subdir
    void remove_file(std::string filename);// delete file
    void quit(); // quit application
    void print_help(); // print help information

    // backend functions
    std::string get_time();
    void update_dirs_listing(); // `..` should always be a valid subdir
    void update_files_listing();

    // utility functions
    void print_lines(std::vector<std::string> lines);
    template<class Iterator> int get_dir_id(Iterator it, std::string cmd);
    template<class Iterator> int get_file_id(Iterator it, std::string cmd);
};

enum Sorting { byDate, byName, bySize };

#endif