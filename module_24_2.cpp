#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

void inputR(std::vector<std::tm> &birthday_list)
{
    std::time_t t = std::time(nullptr);
    std::tm *birth_day = std::localtime(&t);
    std::cout << "Enter the birthday in format YEAR/MONTH/DAY: ";
    std::cin >> std::get_time(birth_day, "%Y/%m/%d");
    birthday_list.push_back(*birth_day);
}

void reminders (std::vector<std::tm> &birthday_list, std::vector<std::string> &listName)
{
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    //std::tm *temp = now;
    for(int i = 0; i < birthday_list.size(); ++i){
        if(now->tm_mon == birthday_list[i].tm_mon &&
            now->tm_mday == birthday_list[i].tm_mday) {
            std::cout << "Today is " << listName[i] << "`s Birthday\n";
        }
    //
    }
}

int main() {
    std::vector<std::tm> birthday_list;
    std::vector<std::string> listName;

    while(true) {

        std::cout << "Enter the name: ";
        std::string name;
        std::cin >> name;
        if (name == "end") reminders(birthday_list, listName);
        else if(name == "exit") return 0;
        else{
            listName.push_back(name);
            inputR(birthday_list);
        }
    }
}

