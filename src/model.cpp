#include "model.hpp"

JOSSModel::JOSSModel(JOSSView* view)
    : view(view) {
    cwd = get_cwd();
    files = std::vector<std::string>();
    get_dirs_in_cwd();
    get_files_in_cwd();

    generate_start_screen();
}

void JOSSModel::start() {
    int key;
    start_new_cmd_line();
    while(!isDone) {
        // get key event
        key = getchar();
        // parse
        handle_key_event(key);
        // refresh
        view->refresh();
    }
}

void JOSSModel::start_new_cmd_line() {
    cursor_x = 0;
    cursor_y = 0;
    curr_cmd = "";
    all_cmds += cwd + " $ " + curr_cmd;
    dirs_pos = 0;
    files_pos = 0;
    terminal_pos = 0;
    view->refresh();
}

void JOSSModel::generate_start_screen() {
    // generated from https://patorjk.com/software/taag/#p=display&f=Impossible&t=Joss
    print_lines(
        R"              __       __           __          __       ", 
        R"             /\ \     /\ \         / /\        / /\      ", 
        R"             \ \ \   /  \ \       / /  \      / /  \     ", 
        R"             /\ \_\ / /\ \ \     / / /\ \__  / / /\ \__  ", 
        R"            / /\/_// / /\ \ \   / / /\ \___\/ / /\ \___\ ", 
        R"   _       / / /  / / /  \ \_\  \ \ \ \/___/\ \ \ \/___/ ", 
        R"  /\ \    / / /  / / /   / / /   \ \ \       \ \ \       ", 
        R"  \ \_\  / / /  / / /   / / /_    \ \ \  _    \ \ \      ", 
        R"  / / /_/ / /  / / /___/ / //_/\__/ / / /_/\__/ / /      ", 
        R" / / /__\/ /  / / /____\/ / \ \/___/ /  \ \/___/ /       ", 
        R" \/_______/   \/_________/   \_____\/    \_____\/        ",                              
        R"   Jacob's      Operating      System      Shell         ",
        R"",
        R"Welcome to JOSS! Please use key bindings listed on the bottom bar" +
         " and directory/file identifiers listed in the right panel to interface" +
         " with your operating system");
}

