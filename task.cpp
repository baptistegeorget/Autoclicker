//
// Created by bapti on 01/12/2022.
//

#include "task.h"

void Task::add_action(int new_type_action, int new_time, int new_x, int new_y) {
    Action action(new_type_action, new_time, new_x, new_y);
    list_action.push_back(action);
}

void Task::remove_action(int place) {
    list_action.erase(list_action.begin() + place-1);
}

void Task::move_action(int place, int new_place) {
    Action save_action = list_action[place-1];
    list_action.erase(list_action.begin() + place-1);
    list_action.insert(list_action.begin() + new_place-1, save_action);
}

void Task::duplicate_action(int place) {
    list_action.insert(list_action.begin() + place, list_action[place-1]);
}

void Task::start() {
    clock_t start_run_time = clock();
    time_t datetime = time(nullptr);
    for(int j = 0; j < nb_execution; j++) {
        for(auto i : list_action) {
            i.start();
        }
        if(nb_execution > 1) {
            Sleep(restart_time*1000);
        }
    }
    clock_t end_run_time = clock();
    clock_t run_time = end_run_time-start_run_time;
    TaskHistorical new_task_historical(name, run_time, datetime);
}

void Task::preview() {
    clock_t start_run_time = clock();
    time_t datetime = time(nullptr);
    for(int j = 0; j < nb_execution; j++) {
        for(auto i : list_action) {
            if(i.type_action == 1 || i.type_action == 8) {
                i.start();
            }
        }
        if(nb_execution > 1) {
            Sleep(restart_time*1000);
        }
    }
    clock_t end_run_time = clock();
    clock_t run_time = end_run_time-start_run_time;
    TaskHistorical new_task_historical(name, run_time, datetime);
}

