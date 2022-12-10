//
// Created by bapti on 01/12/2022.
//
#include "action.h"

void Action::start() const {
    switch (type_action) {
        case 1:
            SetCursorPos(point.x, point.y);
            Sleep(100);
            break;
        case 2:
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Sleep(100);
            break;
        case 3:
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(100);
            break;
        case 4:
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            Sleep(100);
            break;
        case 5:
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
            Sleep(100);
            break;
        case 6:
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Sleep(time);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(100);
            break;
        case 7:
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            Sleep(time);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
            Sleep(100);
            break;
        case 8:
            Sleep(time);
            break;
    }
}