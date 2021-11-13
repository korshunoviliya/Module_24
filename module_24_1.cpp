#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>

struct Task{
    std::string task_name{"unknown task"};
    std::time_t task_time{std::time(nullptr)};
};
void newTask(std::vector<Task> &task, bool &activeTask)
{
    static int counter{0};
    std::string new_task;
    std::cout << "Enter the new task:";
    std::cin >> new_task;
    task.emplace_back();
    task[counter].task_name = new_task;
    task[counter].task_time = std::time(nullptr);
    activeTask = true;
    ++counter;
}

void endTask(std::vector<Task> &task, bool &activeTask)
{
    std::time_t current_time = std::time(nullptr);
    task.back().task_time = (std::time_t)(std::difftime(current_time, task.back().task_time));
    activeTask = false;
}

void printTask(std::vector<Task> &task, bool &activeTask)
{
    if(!task.empty())
    {
        if(activeTask) std::cout << task.back().task_name << std::endl;
        for(int i = 0; i < task.size() - (int)activeTask; i++)
        {
            std::cout << "TASK: " << task[i].task_name << std::endl;
            std::tm *a = std::gmtime(&task[i].task_time);
            std::cout << std::put_time(a, "%H:%M:%S") << std::endl;
        }
    }
    else std::cout << "No tasks saved!" << std::endl;
}

int main() {
    std::vector<Task> task;
    std::string command;
    bool activeTask = false;

    while (true) {
        std::cout << "Enter the command: begin, end, status or exit:";
        std::cin >> command;
        if (command == "begin") {
            if (activeTask) endTask(task, activeTask);
            newTask(task, activeTask);
        }else if (command == "end") {
            if (activeTask) endTask(task, activeTask);
            else std::cout << "No active task!" << std::endl;
        }else if (command == "status") printTask(task, activeTask);
        else if (command == "exit") {
            std::cout << "Goodbye!!!";
            return 0;
        } else std::cout << "Input is not correct! Try again!!!" << std::endl;
    }
}