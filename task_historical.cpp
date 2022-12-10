//
// Created by bapti on 01/12/2022.
//

#include "task_historical.h"

std::string TaskHistorical::file = "../historical.txt";

void TaskHistorical::display(int nb) {
    int nb_line = count_line_txt();
    if(nb < 1) {
        nb = 1;
    } else if(nb > nb_line) {
        nb = nb_line;
    }
    std::ifstream open_file(file);
    if(open_file) {
        for(int i = nb_line; i > nb_line-nb; i--) {
            std::cout << get_this_line(i) << std::endl;
        }
        open_file.close();
    } else {
        std::cout << "! ERROR FILE, not find \"" << file << "\" file." << std::endl;
    }
}

void TaskHistorical::add_task_historical() {
    std::ofstream open_file(file, std::ios::app);
    if(open_file) {
        open_file << "-> \"" << name << "\" (" << ((float)run_time/1000) << "s) at " << ctime(&datetime);
        open_file.close();
    } else {
        std::cout << "! ERROR FILE, not find \"" << file << "\" file." << std::endl;
    }
}

int TaskHistorical::count_line_txt() {
    std::ifstream open_file(file);
    int nb_line = 0;
    std::string text;
    if(open_file) {
        while(!open_file.eof()) {
            std::getline(open_file,text);
            nb_line += 1;
        }
        open_file.close();
    } else {
        std::cout << "! ERROR FILE, not find \"" << file << "\" file." << std::endl;
    }
    return nb_line-1;
}

std::string TaskHistorical::get_this_line(int nb_line) {
    if(nb_line < 1) {
        nb_line = 1;
    }
    std::string text;
    std::ifstream open_file(file);
    if(open_file) {
        for(int i = 0; i < nb_line; i++) {
            if(!open_file.eof()) {
                std::getline(open_file, text);
            }
        }
        open_file.close();
    } else {
        std::cout << "! ERROR FILE, not find \"" << file << "\" file." << std::endl;
    }
    return text;
}

void TaskHistorical::delete_historical() {
    std::ofstream open_file(file);
    if(open_file) {
        open_file.close();
    } else {
        std::cout << "! ERROR FILE, not find \"" << file << "\" file." << std::endl;
    }
}
