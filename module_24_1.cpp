#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>

void newTask(std::vector<std::string> &task, std::vector<time_t> &taskTime, bool &activeTask)
{
    std::string new_task;
    std::cout << "Enter the new task:";
    std::cin >> new_task;
    task.push_back(new_task);
    taskTime.push_back(std::time(nullptr));
    activeTask = true;
}

void endTask(std::vector<time_t> &taskTime, bool &activeTask)
{
    std::time_t current_time = std::time(nullptr);
    taskTime.back() = (std::time_t)(std::difftime(current_time, taskTime.back()));
    activeTask = false;
}

void printTask(std::vector<std::string> &task, std::vector<time_t> &taskTime, bool &activeTask)
{
    if(!task.empty())
    {
        if(activeTask) std::cout << task.back() << std::endl;
        for(int i = 0; i < task.size() - (int)activeTask; i++)
        {
            std::cout << "TASK: " << task[i] << std::endl;
            std::tm *a = std::gmtime(&taskTime[i]);
            std::cout << std::put_time(a, "%H:%M:%S") << std::endl;
        }
    }
    else std::cout << "No tasks saved!" << std::endl;
}

int main() {
    std::string command;
    std::vector<std::string> task;
    std::vector<std::time_t> taskTime;
    bool activeTask = false;
    while (true) {
        std::cout << "Enter the command: begin, end, status or exit:";
        std::cin >> command;
        if (command == "begin") {
            if (activeTask) endTask(taskTime, activeTask);
            newTask(task, taskTime, activeTask);
        }else if (command == "end") {
            if (activeTask) endTask(taskTime, activeTask);
            else std::cout << "No active task!" << std::endl;
        }else if (command == "status") printTask(task, taskTime, activeTask);
        else if (command == "exit") {
            std::cout << "Goodbye!!!";
            return 0;
        } else std::cout << "Input is not correct! Try again!!!" << std::endl;
    }
}