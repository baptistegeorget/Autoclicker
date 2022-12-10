//
// Created by bapti on 01/12/2022.
//
#include <windows.h>

#ifndef AUTO_CLICKER_ACTION_H
#define AUTO_CLICKER_ACTION_H

class Action
{
public:
    int type_action;
    int time;
    POINT point{};

    void start() const;

    Action(int new_type_action, int new_time, int x, int y)
    :type_action(new_type_action), time(new_time)
    {
        point.x = x;
        point.y = y;
    }
};

#endif //AUTO_CLICKER_ACTION_H
