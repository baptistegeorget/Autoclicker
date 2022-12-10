//
// Created by bapti on 01/12/2022.
//
#include <vector>
#include "action.h"
#include "task_historical.h"

#ifndef AUTO_CLICKER_TASK_H
#define AUTO_CLICKER_TASK_H

class Task
{
public:
    std::string name;
    int restart_time;
    int nb_execution;
    POINT size_screen{};
    std::vector<Action> list_action;

    void add_action(int new_type_action, int new_time, int new_x, int new_y);
    void remove_action(int place);
    void move_action(int place, int new_place);
    void duplicate_action(int place);
    void start();
    void preview();

    Task(std::string &new_name, int new_nb_execution, int new_restart_time, int size_screen_x, int size_screen_y)
    :name(new_name), restart_time(new_restart_time), nb_execution(new_nb_execution)
    {
        size_screen.x = size_screen_x;
        size_screen.y = size_screen_y;
    }
};

#endif //AUTO_CLICKER_TASK_H
