//
// Created by bapti on 01/12/2022.
//

#include "menu.h"

void Menu::find_task() {
    list_task.clear();
    for (auto &file: std::filesystem::directory_iterator(folder_task)) {
        std::filesystem::path new_path = file.path();
        Menu::find_one_task(new_path);
    }
}

void Menu::find_one_task(std::filesystem::path &file) {
    std::ifstream open_file(file);
    std::string name = Menu::get_value_txt(open_file);
    int nb_execution = std::stoi(Menu::get_value_txt(open_file));
    int restart_time = std::stoi(Menu::get_value_txt(open_file));
    int x = std::stoi(Menu::get_value_txt(open_file));
    int y = std::stoi(Menu::get_value_txt(open_file));
    Task task(name, nb_execution, restart_time, x, y);
    std::string value;
    while (!open_file.eof()) {
        std::getline(open_file, value);
        std::getline(open_file, value);
        int type_action = std::stoi(Menu::get_value_txt(open_file));
        int time = std::stoi(Menu::get_value_txt(open_file));
        int place_x = std::stoi(Menu::get_value_txt(open_file));
        int place_y = std::stoi(Menu::get_value_txt(open_file));
        task.add_action(type_action, time, place_x, place_y);
    }
    list_task.push_back(task);
    open_file.close();
}

std::string Menu::get_value_txt(std::ifstream &open_file) {
    std::string value;
    std::getline(open_file, value, ':');
    std::getline(open_file, value, ' ');
    std::getline(open_file, value);
    return value;
}

void Menu::save_task(Task &task) {
    std::ofstream file(folder_task + task.name + ".txt");
    file << "Name: " << task.name << std::endl;
    file << "Number of execution: " << task.nb_execution << std::endl;
    file << "Time to restart (in ms): " << task.restart_time << std::endl;
    file << "Size of screen (x): " << task.size_screen.x << std::endl;
    file << "Size of screen (y): " << task.size_screen.y;
    int count = 1;
    for (auto &j: task.list_action) {
        file << std::endl << std::endl;
        file << "-> Action number " << count << std::endl;
        file << "Type of action: " << j.type_action << std::endl;
        file << "Time of action: " << j.time << std::endl;
        file << "Coord(x) of action: " << j.point.x << std::endl;
        file << "Coord(y) of action: " << j.point.y;
        count += 1;
    }
    file.close();
}

void Menu::create_task(std::string &name, int nb_execution, int restart_time) {
    Task task(name, nb_execution, restart_time * 1000, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    Menu::save_task(task);
    task.~Task();
    Menu::find_task();
}

void Menu::remove_task(std::string &name) {
    for (const auto &file: std::filesystem::directory_iterator(folder_task)) {
        if (file.path().filename() == name + ".txt") {
            remove(file.path());
        }
    }
    Menu::find_task();
}

void Menu::duplicate_task(std::string &name) {
    int nb = 1;
    std::filesystem::path source;
    for (const auto &file: std::filesystem::directory_iterator(folder_task)) {
        if (file.path().filename() == name + ".txt") {
            source = file.path();
        }
    }
    if (std::filesystem::exists(source)) {
        std::filesystem::path target;
        while (std::filesystem::exists(folder_task + name + std::to_string(nb) + ".txt")) {
            nb += 1;
        }
        target = folder_task + name + std::to_string(nb) + ".txt";
        std::filesystem::copy_file(source, target, std::filesystem::copy_options::overwrite_existing);
        list_task.clear();
        Menu::find_one_task(target);
        list_task[0].name = name + std::to_string(nb);
        Menu::save_task(list_task[0]);
        Menu::find_task();
    }
}

void Menu::rename_task(std::string &name, std::string &new_name) {
    std::filesystem::path source = folder_task + name + ".txt";
    remove(source);
    for (auto &i: list_task) {
        if (i.name == name) {
            i.name = new_name;
            Menu::save_task(i);
        }
    }
    Menu::find_task();
}

void Menu::set_nb_execution(std::string &name, int nb) {
    for (auto &i: list_task) {
        if (i.name == name) {
            i.nb_execution = nb;
            Menu::save_task(i);
        }
    }
    Menu::find_task();
}

void Menu::set_restart_time(std::string &name, int nb) {
    for (auto &i: list_task) {
        if (i.name == name) {
            i.restart_time = nb * 1000;
            Menu::save_task(i);
        }
    }
    Menu::find_task();
}

void Menu::start_task(std::string &name) {
    for (auto &i: list_task) {
        if (i.name == name) {
            i.start();
        }
    }
}

void Menu::preview_task(std::string &name) {
    for (auto &i: list_task) {
        if (i.name == name) {
            i.preview();
        }
    }
}

void Menu::display() {
    while (true) {
        int action = 0;
        while (action < 1 || action > 11) {
            system("cls");
            std::cout << "Auto-clicker by Scott and Baptiste" << std::endl << std::endl;
            for (auto &i: list_task) {
                std::cout << "-> \"" + i.name + "\" [Repetition:" + std::to_string(i.nb_execution) +
                             ", Repetition time:" + std::to_string(i.restart_time / 1000) + "s]" << std::endl;
            }
            std::cout << std::endl;
            std::cout << "Choose action :" << std::endl;
            std::cout << "1 -> Create task" << std::endl;
            std::cout << "2 -> Remove task" << std::endl;
            std::cout << "3 -> Duplicate task" << std::endl;
            std::cout << "4 -> Rename task" << std::endl;
            std::cout << "5 -> Change the number of execution for a task" << std::endl;
            std::cout << "6 -> Change the restart time for a task" << std::endl;
            std::cout << "7 -> Edit task" << std::endl;
            std::cout << "8 -> Start task" << std::endl;
            std::cout << "9 -> Preview task" << std::endl;
            std::cout << "10 -> Display historical" << std::endl;
            std::cout << "11 -> Close auto-clicker" << std::endl << std::endl;
            std::cout << ">>>";
            std::cin >> action;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::string name;
        if (action > 0 && action < 10) {
            system("cls");
            std::cout << "Enter the name of the task :" << std::endl;
            std::cout << ">>>";
            std::cin >> name;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (std::filesystem::exists(folder_task + name + ".txt") || action == 1 || action == 10 || action == 11) {
            switch (action) {
                case 1:
                    Menu::action_1(name);
                    break;
                case 2:
                    Menu::action_2(name);
                    break;
                case 3:
                    Menu::action_3(name);
                    break;
                case 4:
                    Menu::action_4(name);
                    break;
                case 5:
                    Menu::action_5(name);
                    break;
                case 6:
                    Menu::action_6(name);
                    break;
                case 7:
                    Menu::action_7(name);
                    break;
                case 8:
                    Menu::action_8(name);
                    break;
                case 9:
                    Menu::action_9(name);
                    break;
                case 10:
                    Menu::action_10();
                    break;
                case 11:
                    exit(EXIT_SUCCESS);
                default:
                    break;
            }
        }
    }
}

void Menu::action_1(std::string &name) {
    int nb_execution = -1;
    int restart_time = -1;
    while (nb_execution < 1) {
        system("cls");
        std::cout << "Enter a number of execution for this task :" << std::endl;
        std::cout << ">>>";
        std::cin >> nb_execution;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (restart_time < 0) {
        system("cls");
        std::cout << "Enter the restart time :" << std::endl;
        std::cout << ">>>";
        std::cin >> restart_time;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    Menu::create_task(name, nb_execution, restart_time);
}

void Menu::action_2(std::string &name) {
    Menu::remove_task(name);
}

void Menu::action_3(std::string &name) {
    Menu::duplicate_task(name);
}

void Menu::action_4(std::string &name) {
    std::string new_name;
    system("cls");
    std::cout << "Enter the new name :" << std::endl;
    std::cout << ">>>";
    std::cin >> new_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Menu::rename_task(name, new_name);
}

void Menu::action_5(std::string &name) {
    int nb_execution = -1;
    while (nb_execution < 1) {
        system("cls");
        std::cout << "Enter a number of execution for this task :" << std::endl;
        std::cout << ">>>";
        std::cin >> nb_execution;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    Menu::set_nb_execution(name, nb_execution);
}

void Menu::action_6(std::string &name) {
    int restart_time = -1;
    while (restart_time < 1) {
        system("cls");
        std::cout << "Enter the restart time :" << std::endl;
        std::cout << ">>>";
        std::cin >> restart_time;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    Menu::set_restart_time(name, restart_time);
}

void Menu::action_7(std::string &name) {
    std::string vide = "vide";
    Task task(vide, 0, 0, 0, 0);
    bool a = true;
    while (a) {
        int action = 0;
        while (action < 1 || action > 6) {
            system("cls");
            std::cout << "Task :" << std::endl;
            for (auto &i: list_task) {
                if (i.name == name) {
                    task = i;
                    std::cout << "\"" + i.name + "\" [Repetition:" + std::to_string(i.nb_execution) +
                                 ", Repetition time:" + std::to_string(i.restart_time / 1000) + "s]" << std::endl;
                }
            }
            std::cout << std::endl;
            int count = 1;
            for (auto &j: task.list_action) {
                switch (j.type_action) {
                    case 1:
                        std::cout << std::to_string(count) + "-> Place cursor (" + std::to_string(j.point.x) + "," +
                                     std::to_string(j.point.y) + ")" << std::endl;
                        break;
                    case 2:
                        std::cout << std::to_string(count) + "-> Left click down" << std::endl;
                        break;
                    case 3:
                        std::cout << std::to_string(count) + "-> Left click up" << std::endl;
                        break;
                    case 4:
                        std::cout << std::to_string(count) + "-> Right click down" << std::endl;
                        break;
                    case 5:
                        std::cout << std::to_string(count) + "-> Right click up" << std::endl;
                        break;
                    case 6:
                        std::cout << std::to_string(count) + "-> Left click (" + std::to_string(j.time) + "ms)"
                                  << std::endl;
                        break;
                    case 7:
                        std::cout << std::to_string(count) + "-> Right click (" + std::to_string(j.time) + "ms)"
                                  << std::endl;
                        break;
                    case 8:
                        std::cout << std::to_string(count) + "-> Break (" + std::to_string(j.time) + "ms)" << std::endl;
                        break;
                }
                count += 1;
            }
            std::cout << std::endl;
            std::cout << "Choose action :" << std::endl;
            std::cout << "1 -> Create action" << std::endl;
            std::cout << "2 -> Remove action" << std::endl;
            std::cout << "3 -> Duplicate action" << std::endl;
            std::cout << "4 -> Move action" << std::endl;
            std::cout << "5 -> Read action on the screen" << std::endl;
            std::cout << "6 -> Back to menu" << std::endl << std::endl;
            std::cout << ">>>";
            std::cin >> action;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (action) {
            case 1:
                Menu::add_action(task);
                break;
            case 2:
                Menu::remove_action(task);
                break;
            case 3:
                Menu::duplicate_action(task);
                break;
            case 4:
                Menu::move_action(task);
                break;
            case 5:
                Menu::read_action(task);
                break;
            case 6:
                a = false;
                break;
            default:
                break;
        }
    }
}

void Menu::action_8(std::string &name) {
    Menu::start_task(name);
}

void Menu::action_9(std::string &name) {
    Menu::preview_task(name);
}

void Menu::action_10() {
    std::string value;
    system("cls");
    TaskHistorical::display(20);
    std::cout << std::endl;
    std::cout << "Enter something:" << std::endl;
    std::cout << ">>>";
    std::cin >> value;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::add_action(Task &task) {
    int new_type_action = -1;
    int new_time = -1;
    int new_x = -1;
    int new_y = -1;
    while (new_type_action < 1 || new_type_action > 8) {
        system("cls");
        std::cout << "Enter the type of action :" << std::endl;
        std::cout << "1 -> Place the cursor" << std::endl;
        std::cout << "2 -> Left click down" << std::endl;
        std::cout << "3 -> left click up" << std::endl;
        std::cout << "4 -> Right click down" << std::endl;
        std::cout << "5 -> Right click up" << std::endl;
        std::cout << "6 -> Left click" << std::endl;
        std::cout << "7 -> Right click" << std::endl;
        std::cout << "8 -> Break" << std::endl << std::endl;
        std::cout << ">>>";
        std::cin >> new_type_action;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (new_type_action == 1) {
        new_time = 0;
        while (new_x < 0 || new_x > task.size_screen.x) {
            system("cls");
            std::cout << "Enter the position x :" << std::endl;
            std::cout << ">>>";
            std::cin >> new_x;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        while (new_y < 0 || new_y > task.size_screen.y) {
            system("cls");
            std::cout << "Enter the position y :" << std::endl;
            std::cout << ">>>";
            std::cin >> new_y;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } else if (new_type_action > 1 && new_type_action < 6) {
        new_time = 0;
        new_x = 0;
        new_y = 0;
    } else if (new_type_action > 5 && new_type_action < 9) {
        new_x = 0;
        new_y = 0;
        while (new_time < 1) {
            system("cls");
            std::cout << "Enter the time :" << std::endl;
            std::cout << ">>>";
            std::cin >> new_time;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    task.add_action(new_type_action, new_time, new_x, new_y);
    Menu::save_task(task);
    Menu::find_task();
}

void Menu::remove_action(Task &task) {
    int place = -1;
    while (place < 1 || place > task.list_action.size()) {
        system("cls");
        std::cout << "Choose action to remove :" << std::endl;
        std::cout << ">>>";
        std::cin >> place;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    task.remove_action(place);
    Menu::save_task(task);
    Menu::find_task();
}

void Menu::move_action(Task &task) {
    int place = -1;
    int new_place = -1;
    while (place < 1 || place > task.list_action.size()) {
        system("cls");
        std::cout << "Choose action to move :" << std::endl;
        std::cout << ">>>";
        std::cin >> place;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (new_place < 1 || new_place > task.list_action.size()) {
        system("cls");
        std::cout << "Choose new place : " << std::endl;
        std::cout << ">>>";
        std::cin >> new_place;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    task.move_action(place, new_place);
    Menu::save_task(task);
    Menu::find_task();
}

void Menu::duplicate_action(Task &task) {
    int place = -1;
    while (place < 1 || place > task.list_action.size()) {
        system("cls");
        std::cout << "Choose action to duplicate :" << std::endl;
        std::cout << ">>>";
        std::cin >> place;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    task.duplicate_action(place);
    Menu::save_task(task);
    Menu::find_task();
}

void Menu::read_action(Task &task) {
    bool a = true;
    clock_t time = clock();
    system("cls");
    std::cout << "Press \"SPACE\" button for echap." << std::endl;
    while (a) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            a = false;
        }
        if (GetKeyState(VK_LBUTTON) & 0x8000) {
            clock_t actual_time = clock();
            auto point = new POINT;
            GetCursorPos(point);
            task.add_action(8, actual_time - time, 0, 0);
            time = actual_time;
            task.add_action(1, 0, point->x, point->y);
            task.add_action(2, 0, 0, 0);
            task.add_action(3, 0, 0, 0);
            Sleep(500);
        }
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
            clock_t actual_time = clock();
            auto point = new POINT;
            GetCursorPos(point);
            task.add_action(8, actual_time - time, 0, 0);
            time = actual_time;
            task.add_action(1, 0, point->x, point->y);
            task.add_action(4, 0, 0, 0);
            task.add_action(5, 0, 0, 0);
            Sleep(500);
        }
    }
    Menu::save_task(task);
    Menu::find_task();
}