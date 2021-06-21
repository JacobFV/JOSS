#ifndef JOSS_MODEL_DEF
#define JOSS_MODEL_DEF


#include "model.hpp"


JOSSModel::JOSSModel() {
    // Initializes JOSSModel

    update_dirs_listing();
    update_files_listing();

    print_lines(WELCOME_CONTENT);
    start_new_cmd_line();
}


void JOSSModel::start_new_cmd_line() {
    // Configures the internal state of `this` such that the
    // console will have a new empty current command

    update_dirs_listing();
    update_files_listing();

    // try to minimally adjust the window positions
    if(dirs.size() > WINDOW_HEIGHT && dirs_pos == dirs.size() - WINDOW_HEIGHT) 
        dirs_pos = dirs.size() - WINDOW_HEIGHT;
    else if(dirs_pos < 0) dirs_pos = 0;
    if(files.size() > WINDOW_HEIGHT && files_pos == files.size() - WINDOW_HEIGHT) 
        files_pos = files.size() - WINDOW_HEIGHT;
    else if(files_pos < 0) files_pos = 0;
}


void JOSSModel::exec_cmd(std::string cmd) {
    // Executes the current command

    // content checking
    if(cmd.length() == 0) return; // empty command

    // attempt to parse command
    try {

        // replace multiple spaces
        std::regex_replace(cmd, std::regex(" +"), " ");

        // Special Case: If the user types "./path/to/local/file"
        // replace "./" with "execute " and with logic below
        if(cmd.length() > 2 && cmd.substr(0,2) == "./") {
            cmd.assign("run " + cmd.substr(2));
        }

        // general case
        auto pos = cmd.begin();
        
        while (*pos++ != ' ') ;
            auto cmd_cmd = make_string_lowercase(cmd.substr(0, pos-cmd.begin()));

        // previous
        if(cmd_cmd=="p" || 
           cmd_cmd=="prev" ||
           cmd_cmd=="previous") {
            // decrement displayed dirs and files sublist index
            dirs_pos--; files_pos--;
        }
        // next
        if(cmd_cmd=="n" || 
           cmd_cmd=="next") {
            // decrement displayed dirs and files sublist index
            dirs_pos++; files_pos++;
        }
        // open file in editor
        else if(cmd_cmd=="e" || 
           cmd_cmd=="edit") {
            edit_file(files[get_file_id(pos, cmd)]);
        }
        // run file marked for execution
        else if(cmd_cmd == "r" ||
                cmd_cmd == "run" ||
                cmd_cmd == "x" ||
                cmd_cmd == "execute") {
            run_program(cmd.substr(pos - cmd.begin()));
        }
        // change directory
        else if(cmd_cmd == "c" ||
                cmd_cmd == "ch" ||
                cmd_cmd == "cd" ||
                cmd_cmd == "change") {
            change_directory(dirs[get_dir_id(pos, cmd)]);
        }
        // set sorting for dirs and files
        else if(cmd_cmd == "s" ||
                cmd_cmd == "sort") {
            set_sorting(cmd.substr(pos - cmd.begin()));
        }
        // display file contents in terminal
        else if(cmd_cmd == "d" ||
                cmd_cmd == "disp" ||
                cmd_cmd == "display" ||
                cmd_cmd == "cat" ||
                cmd_cmd == "print") {
            display_file(files[get_file_id(pos, cmd)]);
        }
        // show system information on file
        else if(cmd_cmd == "i" ||
                cmd_cmd == "info") {
            get_file_info(files[get_file_id(pos, cmd)]);
        }
        // move file to subdir
        else if(cmd_cmd == "m" ||
                cmd_cmd == "mv" ||
                cmd_cmd == "move") {
            auto file = files[get_file_id(pos, cmd)];
            auto dir = dirs[get_dir_id(pos, cmd)];
            move_file(file, dir);
        }
        // delete file
        else if(cmd_cmd == "r" ||
                cmd_cmd == "remove" ||
                cmd_cmd == "del" ||
                cmd_cmd == "delete") {
            remove_file(files[get_file_id(pos, cmd)]);
        }
        // quit application
        else if(cmd_cmd == "q" ||
                cmd_cmd == "quit" ||
                cmd_cmd == "exit" ||
                cmd_cmd == "goodbye") {
            quit();
        }
        else if(cmd_cmd == "t" ||
                cmd_cmd == "time") {
            print_lines({"The time is " + get_time()});
        }
        // print help information
        else if(cmd_cmd == "h" ||
                cmd_cmd == "help") {
            print_help();
        }
        else {
            throw new CommandParsingException("command `" + cmd_cmd + "` not recognized. See HELP");
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
    exit(EXIT_SUCCESS);
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


void JOSSModel::print_lines(std::vector<std::string> lines) {
    for(auto line : lines) {
        all_past_terminal_content.push_back(std::string(line));
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

#endif