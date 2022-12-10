//
// Created by bapti on 01/12/2022.
//
#include "task.h"
#include <filesystem>

#ifndef AUTO_CLICKER_MENU_H
#define AUTO_CLICKER_MENU_H

class Menu
{
private:
    std::string folder_task;
    std::string file_historical;
    std::vector<Task> list_task;

    void find_task();
    void find_one_task(std::filesystem::path &file);
    static std::string get_value_txt(std::ifstream &open_file);
    void save_task(Task &task);
    void create_task(std::string &name, int nb_execution, int restart_time);
    void remove_task(std::string &name);
    void duplicate_task(std::string &name);
    void rename_task(std::string &name, std::string &new_name);
    void set_nb_execution(std::string &name, int nb);
    void set_restart_time(std::string &name, int nb);
    void start_task(std::string &name);
    void preview_task(std::string &name);
    void display();
    void add_action(Task &task);
    void remove_action(Task &task);
    void duplicate_action(Task &task);
    void move_action(Task &task);
    void read_action(Task &task);

    //Fonction "display" découpée
    void action_1(std::string &name);
    void action_2(std::string &name);
    void action_3(std::string &name);
    void action_4(std::string &name);
    void action_5(std::string &name);
    void action_6(std::string &name);
    void action_7(std::string &name);
    void action_8(std::string &name);
    void action_9(std::string &name);
    void action_10();

public:
    Menu(std::string &path_folder_task, std::string &path_historical)
    :folder_task(path_folder_task), file_historical(path_historical)
    {
        Menu::find_task();
        Menu::display();
    }
};

#endif //AUTO_CLICKER_MENU_H
