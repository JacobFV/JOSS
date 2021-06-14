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

    // main read-eval-print loop
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
    curr_cmd = ""; // the view adds the '_' during rendering
    all_cmds.push_back(curr_cmd);
    all_content.push_back(cwd + " $ "); // the view adds the cmd 
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


void JOSSModel::handle_key_event(int key) {

    if (key > 255) return; // non-ansi key

    switch (key)
    {
    case -1:
        return;  // error reading key

    case 10: // enter
        parse_cmd(); 
        break;

    case 27: // escape
        break;

    // backspace and delete
    case 8: // backspace
        // curr_cmd: 0123_456 -> 012_456
        // cursor_x:    4     ->    3  
        if (cursor_x != 0) {
            curr_cmd = curr_cmd.substr(0, cursor_x-1)
                     + curr_cmd.substr(cursor_x, curr_cmd.size() - cursor_x);
        }
        break;
    case 127: // delete
        // curr_cmd: 0123_456 -> 0123_56
        // cursor_x:    4     ->    3  
        if (cursor_x != 0) {
            curr_cmd = curr_cmd.substr(0, cursor_x)
                     + curr_cmd.substr(cursor_x+1, curr_cmd.size() - cursor_x - 1);
        }
        break;

    // cursor navigation
    case 24: // up arrow
        all_cmds[cursor_y].assign(curr_cmd);
        cursor_y--;
        if (cursor_y < 0) cursor_y = 0;
        if (cursor_y == all_cmds.size()) cursor_y = all_cmds.size();
        curr_cmd = all_cmds.at(cursor_y);
        cursor_x = curr_cmd.size();
        break;
    case 25: // down arrow
        all_cmds[cursor_y].assign(curr_cmd);
        cursor_y++;
        if (cursor_y < 0) cursor_y = 0;
        if (cursor_y == all_cmds.size()) cursor_y = all_cmds.size();
        curr_cmd = all_cmds.at(cursor_y);
        cursor_x = curr_cmd.size();
        break;

    case 26: // right arrow
        cursor_x++;
        if (cursor_x < 0) cursor_x = 0;
        if (cursor_x == curr_cmd.size()) cursor_x = curr_cmd.size();
        break;
    case 27: // left arrow
        cursor_x--;
        if (cursor_x < 0) cursor_x = 0;
        if (cursor_x == curr_cmd.size()) cursor_x = curr_cmd.size();
        break;

    // data input    
    default: // a valid character
        // curr_cmd: 0123_456 -> 0123x_456
        // cursor_x:     4    ->      5
        curr_cmd.insert(cursor_x, (char)key);
        //curr_cmd = curr_cmd.substr(0, cursor_x-1)
        //         + std::string(1, (char)key)
        //        + curr_cmd.substr(cursor_x, curr_cmd.size() - cursor_x);
        cursor_x++;
        break;
    }
}

void JOSSModel::parse_cmd() {
    
}