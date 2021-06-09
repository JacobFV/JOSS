#include "header.hpp"
#include "view.hpp"

class JOSSModel {
public:
    JOSSView* view;

    std::string cwd; // does not include trailing `/`

    std::vector<std::string> dirs;
    std::vector<std::string> files;
    Sorting dirsSorting = Sorting::byName;
    Sorting filesSorting = Sorting::byName;

    int dirs_pos = 0; // 0 means top
    int files_pos = 0; // 0 means top
    int terminal_pos = 0; // 0 means most recent
    int cursor_x = 0; // 0 means begining of string
    int cursor_y = 0; // negative based indexing of previous commands. 0 means current line

    std::deque<std::string> all_content;
    std::deque<std::string> all_cmds;
    std::string curr_cmd = "";

    bool isDone = false;

    JOSSModel(JOSSView* view);

    void start();

    void start_new_cmd_line();
    void generate_start_screen();
    void handle_key_event(int key);
    void parse_cmd();

    std::string get_cwd();
    std::string get_time();
    std::string get_file_info(std::string filename);
    void edit_file(std::string filename);
    void run_program(std::string filename);
    void change_directory(std::string dirname); // might be ..
    void remove_file(std::string filename);
    void quit();

    void get_dirs_in_cwd();
    void get_files_in_cwd();

    void print_lines(std::string lines...);
};

enum Sorting { byDate, byName };