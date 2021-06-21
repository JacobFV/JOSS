#include "model.hpp"

JOSSModel::JOSSModel() {
    // Initializes JOSSModel

    update_dirs_listing();
    update_files_listing();

    print_lines(WELCOME_CONTENT);
}


void JOSSModel::handle_key_event(char key) {
    // Covers all the logic required to properly respond to an incoming key
    // by typing characters, executing commands, navigating, etc.

    if (key == -1 || key > 255) return; // error reading key or non-ansi key

    switch (key)
    {
    case 10: // enter
        // maybe execute command

        // if previous command was just the move up or down operation 
        // for the sidebar windows, don't actually execute it
        //bool did_only_move; did_only_move = false;
        if(curr_cmd()->second == "N" || curr_cmd()->second == "n") {
            // move displayed files and dirs sublist windows up and down
            // previous
            // increment displayed dirs and files sublist index
            dirs_pos++;
            files_pos++;
            //did_only_move = true;

            curr_cmd()->second.assign("");
            break;
        }
        else if(curr_cmd()->second == "P" || curr_cmd()->second == "p") {
            // previous
            // decrement displayed dirs and files sublist index
            dirs_pos--;
            files_pos--;
            //did_only_move = true;

            curr_cmd()->second.assign("");
            break;
        } 
/*
        if(did_only_move) {
            //if(dirs_pos < 0) dirs_pos++;
            //if(dirs.size() > WINDOW_HEIGHT && dirs_pos == dirs.size() - WINDOW_HEIGHT) dirs_pos--;
            //if(files_pos < 0) files_pos++;
            //if(files.size() > WINDOW_HEIGHT && files_pos == files.size() - WINDOW_HEIGHT) files_pos--;

            curr_cmd()->second.assign("");

            // we only moved the window so break and don't execute the command
            break;
        }*/


        // if the command executed was not the actual last command,
        // it should now become the most recently executed command
        // for historical (uparrow, downarrow) reasons
        all_cmds[all_cmds.size() - 1]->first.assign(all_cmds[cursor_y]->first);
        all_cmds[all_cmds.size() - 1]->second.assign(all_cmds[cursor_y]->second);
        cursor_y = all_cmds.size() - 1;
        // now the most recent command is the one executed regardless
        // of previous cursor navigation through history

        // normally the controller does this, but now 
        // the directory will be burned into the string all_past_content
        all_past_content.append(NEWLN + fmt_cmd(curr_cmd(), -1));

        exec_cmd(); 
        
        start_new_cmd_line();
        break;


    // removing characters
    case 8: // backspace
        // on display: 0123_456 -> 012_456
        // curr_cmd:   0123456  -> 012456
        // cursor_x:      4     ->    3 
        if (cursor_x != 0) {
            curr_cmd()->second.assign(
                curr_cmd()->second.substr(0, cursor_x-1) +
                curr_cmd()->second.substr(cursor_x)
            );
            cursor_x--;
        }
        break;
    case 127: // delete
        // on display: 0123_456 -> 0123_56
        // curr_cmd:   0123456  -> 012356
        // cursor_x:      4     ->    4
        if (cursor_x == curr_cmd()->second.length()-1) {
            curr_cmd()->second.assign(
                curr_cmd()->second.substr(0, 
                    curr_cmd()->second.length()-1));
        } 
        else {
            curr_cmd()->second.assign(
                curr_cmd()->second.substr(0, cursor_x) +
                curr_cmd()->second.substr(cursor_x+1)
            );
        }
        break;

    // browse/edit previous commands
    case 24: // up arrow
        cursor_y++;
        if (cursor_y == all_cmds.size()) cursor_y = all_cmds.size();
        cursor_x = curr_cmd()->second.length();
        break;
    case 25: // down arrow
        cursor_y--;
        if (cursor_y < 0) cursor_y = 0;
        cursor_x = curr_cmd()->second.length();
        break;

    // move cursor "_" left and right
    case 26: // right arrow
        cursor_x++;
        if (cursor_x == curr_cmd()->second.length()) cursor_x = curr_cmd()->second.length();
        break;
    case 27: // left arrow
        cursor_x--;
        if (cursor_x < 0) cursor_x = 0;
        break;

    // data input    
    default: // a valid character
        // curr_cmd: 0123_456 -> 0123x_456
        // cursor_x:     4    ->      5
        curr_cmd()->second.insert(cursor_x, 1, key);
        cursor_x++;
        break;
    }
}


void JOSSModel::start_new_cmd_line() {
    // Configures the internal state of `this` such that the
    // console will have a new empty current command

    update_dirs_listing();
    update_files_listing();

    all_cmds.push_back(new std::pair<std::string, std::string>(cwd, ""));

    cursor_x = 0;
    cursor_y = all_cmds.size() - 1;
    
    // try to minimally adjust the window positions
    if(dirs.size() > WINDOW_HEIGHT && dirs_pos == dirs.size() - WINDOW_HEIGHT) 
        dirs_pos = dirs.size() - WINDOW_HEIGHT;
    else if(dirs_pos < 0) dirs_pos = 0;
    if(files.size() > WINDOW_HEIGHT && files_pos == files.size() - WINDOW_HEIGHT) 
        files_pos = files.size() - WINDOW_HEIGHT;
    else if(files_pos < 0) files_pos = 0;
}


void JOSSModel::exec_cmd() {
    // Executes the current command

    // the compiler ends up linking a pointer either way
    // but  makes code more readable
     auto cmd_str = curr_cmd()->second;

    // content checking
    if(curr_cmd()->second.length() == 0) return; // empty command

    // attempt to parse command
    try {

        // replace multiple spaces
        std::regex_replace(cmd_str, std::regex(" +"), " ");

        // Special Case: If the user types "./path/to/local/file"
        // replace "./" with "execute " and with logic below
        if(cmd_str.length() > 2 && cmd_str.substr(0,2) == "./") {
            cmd_str.assign("run " + cmd_str.substr(2));
        }

        // general case
        auto pos = cmd_str.begin();
        
        while (*pos++ != ' ') ;
         auto cmd = make_string_lowercase(cmd_str.substr(0, pos-cmd_str.begin()));

        // open file in editor
        if(cmd=="e" || 
           cmd=="edit") {
            edit_file(files[get_file_id(pos, cmd_str)]);
        }
        // run file marked for execution
        else if(cmd == "r" ||
                cmd == "run" ||
                cmd == "x" ||
                cmd == "execute") {
            run_program(cmd_str.substr(pos - cmd_str.begin()));
        }
        // change directory
        else if(cmd == "c" ||
                cmd == "ch" ||
                cmd == "cd" ||
                cmd == "change") {
            change_directory(dirs[get_dir_id(pos, cmd_str)]);
        }
        // set sorting for dirs and files
        else if(cmd == "s" ||
                cmd == "sort") {
            set_sorting(cmd_str.substr(pos - cmd_str.begin()));
        }
        // display file contents in terminal
        else if(cmd == "d" ||
                cmd == "disp" ||
                cmd == "display" ||
                cmd == "cat" ||
                cmd == "print") {
            display_file(files[get_file_id(pos, cmd_str)]);
        }
        // show system information on file
        else if(cmd == "i" ||
                cmd == "info") {
            get_file_info(files[get_file_id(pos, cmd_str)]);
        }
        // move file to subdir
        else if(cmd == "m" ||
                cmd == "mv" ||
                cmd == "move") {
            auto file = files[get_file_id(pos, cmd_str)];
            auto dir = dirs[get_dir_id(pos, cmd_str)];
            move_file(file, dir);
        }
        // delete file
        else if(cmd == "r" ||
                cmd == "remove" ||
                cmd == "del" ||
                cmd == "delete") {
            remove_file(files[get_file_id(pos, cmd_str)]);
        }
        // quit application
        else if(cmd == "q" ||
                cmd == "quit" ||
                cmd == "exit" ||
                cmd == "goodbye") {
            quit();
        }
        else if(cmd == "t" ||
                cmd == "time") {
            print_lines({"The time is " + get_time()});
        }
        // print help information
        else if(cmd == "h" ||
                cmd == "help") {
            print_help();
        }
        else {
            throw new CommandParsingException("command `" + cmd + "` not recognized. See HELP");
        }

    // print any error that occurs during parsing to the terminal
    } catch (CommandParsingException& err) {
        print_lines({"Error parsing command: " +std::string( err.what())});
    } catch (CommandExecutionException& err) {
        print_lines({"Error during command execution: " + std::string(err.what())});
    } catch (std::bad_alloc& err) {
        print_lines({"bad_alloc: " + std::string(err.what())});
    } catch (std::bad_cast err) {
        print_lines({"bad_cast: " + std::string(err.what())});
    } catch (std::bad_function_call err) {
        print_lines({"bad_function_call: " + std::string(err.what())});
    } catch (std::logic_error err) {
        print_lines({"logic_error: " + std::string(err.what())});
    } catch (std::runtime_error err) {
        print_lines({"runtime_error: " + std::string(err.what())});
    } catch (std::bad_exception err) {
        print_lines({"bad_exception: " +std::string( err.what())});
    } catch (...) {
        print_lines({"An error occured."});
    }
}


// open file in editor
void JOSSModel::edit_file(std::string filename) {
    system(std::string("pico " + filename).c_str());
}


// run file marked for execution
void JOSSModel::run_program(std::string entire_cmd) {
    system(entire_cmd.c_str());
}


// change directory
void JOSSModel::change_directory(std::string dirname) {
    auto res = chdir(dirname.c_str());
    if (res != -1) {
        getcwd(&cwd[0], MAX_PATH_SIZE); // set cwd
    }
    else throw new CommandExecutionException("Error changing directories");
}


// set sorting for dirs and files
void JOSSModel::set_sorting(std::string type) {
    if(type == "name" || "n") {
        //sorting = Sorting::byName;
    }
    else if(type == "size" || "s") {
        //sorting = Sorting::bySize;
    }
    else if(type == "date" || "d") {
        //sorting = Sorting::byDate;
    }
    else throw new CommandParsingException(
        "Please specify a sorting method (name/date/size): ex: \"sort name\".");

    dirs_pos = 0;
    files_pos = 0;
    update_files_listing();
    update_dirs_listing();
}


// display file contents in terminal
void JOSSModel::display_file(std::string filename) {
    std::fstream file;
    file.open(filename);
    if(file.is_open()) {
        std::string line;
        while(getline(file, line)) print_lines({line});
        file.close();
    }
}


// show system information on file
void JOSSModel::get_file_info(std::string filename) {

}


// move file to subdir
void JOSSModel::move_file(std::string filename, std::string subdir) {
    rename(filename.c_str(), std::string(subdir + "/" + filename).c_str());
}


// delete file
void JOSSModel::remove_file(std::string filename) {
    unlink(filename.c_str());
}


// quit application
void JOSSModel::quit() {
    print_lines({"Goodbye!"});
    isDone = true;
}


// print help information
void JOSSModel::print_help() {
    print_lines(HELP_MESSAGE);
}


std::string JOSSModel::get_time() {
    time_t t = time(NULL);
    return std::string(ctime(&t));
}


void JOSSModel::update_dirs_listing() {
    dirs.clear();

    // modified from assignment 1 template
    struct dirent* de;
    DIR* d;

    d = opendir( "." );
    while ((de = readdir(d))){
        if ((de->d_type) & DT_DIR) 
            dirs.push_back(std::string(de->d_name)); 
    }
    closedir( d );
}


void JOSSModel::update_files_listing() {
    files.clear();

    // modified from assignment 1 template
    struct dirent* de;
    DIR* d;

    d = opendir( "." );
    while ((de = readdir(d))){
        if ((de->d_type) & DT_REG) 
            files.push_back(std::string(de->d_name)); 
    }
    closedir( d );
}


CMD JOSSModel::curr_cmd() {
    return all_cmds[cursor_y];
}

void JOSSModel::print_lines(std::vector<std::string> lines) {
    auto it = lines.begin();
    while(it != lines.end()) {
        all_past_content.append(*it++);
        if(it != lines.end()) all_past_content.append(NEWLN);
    }
}


template<class Iterator> 
int JOSSModel::get_dir_id(Iterator it, std::string cmd_str) {
    // look for either a dir name or dirid.
    // On completion `it` points to the first char after the file
    // Then return the fid or throw a 
    // CommandExecutionException("filename `file` does not match any paths")
    if(it == cmd_str.end()) throw CommandParsingException("no subdirectory is given");

    const auto start = it;
    while(*it++ != ' ') ;

    auto dirname = cmd_str.substr(start - cmd_str.begin(), it-start);

    // first assume it is a string dirname
    for (int i = 0; i < dirs.size(); i++) {
        if(dirs[i] == dirname) return i;
    }

    // second try if its a valid integer
    int dir_num = atoi(dirname.c_str());
    if(dir_num == -1) {throw CommandParsingException(
        "no subdirectory identified by `" + dirname + 
        "exists in the working directory");}

    return dir_num;
}


template<class Iterator> 
int JOSSModel::get_file_id(Iterator it, std::string cmd_str) {
    // look for either a file name or fid.
    // On completion `it` points to the first char after the file
    // Then return the fid or throw a 
    // CommandExecutionException("filename `file` does not match any paths")
    if(it == cmd_str.end()) throw CommandParsingException("no file is given");

    const auto start = it;
    while(*it++ != ' ') ;

    auto filename = cmd_str.substr(start - cmd_str.begin(), it-start);

    // first assume it is a string filename
    for (int i = 0; i < files.size(); i++) {
        if(files[i] == filename) return i;
    }

    // second try if its a valid integer
    int file_num = atoi(filename.c_str());
    if(file_num == -1) {throw CommandParsingException(
        "no file identified by `" + filename + 
        "exists in the working directory");}

    return file_num;
}