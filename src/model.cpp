#include "model.hpp"

JOSSModel::JOSSModel() {
    cwd = get_cwd();
    get_dirs_in_cwd();
    get_files_in_cwd();

    print_lines(WELCOME_CONTENT);
}


void JOSSModel::handle_key_event(int key) {

    if (key == -1 || key > 255) return; // error reading key or non-ansi key

    switch (key)
    {
    case 10: // enter

        // if the command executed was not the actual last command,
        // it should now become the most recently executed command
        // for historical (uparrow, downarrow) reasons
        all_cmds[all_cmds.size() - 1].first.assign(all_cmds[cursor_y].first);
        all_cmds[all_cmds.size() - 1].second.assign(all_cmds[cursor_y].second);

        // normally the controller does this, but now 
        // the directory will be burned into the string all_past_content
        all_past_content.append("\n" + fmt_cmd(curr_cmd(), -1));

        exec_cmd(); 
        
        start_new_cmd_line();
        break;

    case 27: // escape
        break;

    // removing characters
    case 8: // backspace
        // on display: 0123_456 -> 012_456
        // curr_cmd:   0123456  -> 012456
        // cursor_x:      4     ->    3 
        if (cursor_x != 0) {
            curr_cmd().second.assign(
                curr_cmd().second.substr(0, cursor_x-1) +
                curr_cmd().second.substr(cursor_x)
            );
            cursor_x--;
        }
        break;
    case 127: // delete
        // on display: 0123_456 -> 0123_56
        // curr_cmd:   0123456  -> 012356
        // cursor_x:      4     ->    4
        if (cursor_x != curr_cmd().second.length()-1) {
            curr_cmd().second.assign(
                curr_cmd().second.substr(0, cursor_x) +
                curr_cmd().second.substr(cursor_x+1)
            );
        }
        break;

    // browse/edit previous commands
    case 24: // up arrow
        cursor_y++;
        if (cursor_y == all_cmds.size()) cursor_y = all_cmds.size();
        cursor_x = curr_cmd().second.length();
        break;
    case 25: // down arrow
        cursor_y--;
        if (cursor_y < 0) cursor_y = 0;
        cursor_x = curr_cmd().second.length();
        break;

    // move cursor "_" left and right
    case 26: // right arrow
        cursor_x++;
        if (cursor_x == curr_cmd().second.length()) cursor_x = curr_cmd().second.length();
        break;
    case 27: // left arrow
        cursor_x--;
        if (cursor_x < 0) cursor_x = 0;
        break;

    // data input    
    default: // a valid character
        // curr_cmd: 0123_456 -> 0123x_456
        // cursor_x:     4    ->      5
        static char ch; ch = key; // `insert` requires an lvalue char
        curr_cmd().second.insert(static_cast<size_t>(cursor_x), &ch);
        cursor_x++;
        break;
    }
}


void JOSSModel::start_new_cmd_line() {
    cwd = get_cwd();
    get_dirs_in_cwd();
    get_files_in_cwd();

    all_cmds.push_back(CMD(cwd, ""));

    cursor_x = 0;
    cursor_y = all_cmds.size() - 1;

    dirs_pos = 0;
    files_pos = 0;
}


void JOSSModel::exec_cmd() {
    
}

inline CMD JOSSModel::curr_cmd() {
    return all_cmds[cursor_y];
}