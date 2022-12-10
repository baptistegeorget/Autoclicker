//
// Created by bapti on 01/12/2022.
//

#include <iostream>
#include <ctime>
#include <fstream>

#ifndef AUTO_CLICKER_TASK_HISTORICAL_H
#define AUTO_CLICKER_TASK_HISTORICAL_H

class TaskHistorical
{
private:
    std::string name;
    clock_t run_time;
    time_t datetime;
    static std::string file;
    static int count_line_txt();
    static std::string get_this_line(int nb_line);
    void add_task_historical();

public:
    static void display(int nb);
    static void delete_historical();

    TaskHistorical(std::string &new_name, clock_t &new_run_time, time_t &new_datetime)
    :name(new_name), run_time(new_run_time), datetime(new_datetime)
    {
        this->add_task_historical();
    }
};

#endif //AUTO_CLICKER_TASK_HISTORICAL_H
