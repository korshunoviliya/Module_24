#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

struct Birthday_list{
    std::tm birthday{};
    std::string name;
};
void input_birthday_list(std::vector<Birthday_list> &birthday_list, std::string &name)
{
    static int counter{0};
    std::time_t t = std::time(nullptr);
    std::tm *birth_day = std::localtime(&t);
    std::cout << "Enter the birthday in format YEAR/MONTH/DAY: ";
    std::cin >> std::get_time(birth_day, "%Y/%m/%d");
    birthday_list.emplace_back();
    birthday_list[counter].name = name;
    birthday_list[counter].birthday = *birth_day;
    ++counter;
}

void reminders (std::vector<Birthday_list> &birthday_list)
{
    bool check{false};
    std::time_t t {std::time(nullptr)};
    std::tm *now {std::localtime(&t)};
    Birthday_list temp {*now,""};
    for(auto & i : birthday_list){
        if(temp.birthday.tm_mon == i.birthday.tm_mon &&
            temp.birthday.tm_mday == i.birthday.tm_mday) {
            std::cout << "Today is " << i.name << "`s Birthday\n";
        }
        if(i.birthday.tm_mon == now->tm_mon
            && i.birthday.tm_mday <= temp.birthday.tm_mday
            && i.birthday.tm_mday >= now->tm_mday){
            temp = i;
            check = true;
        }
        else if(!check
                && i.birthday.tm_mon > temp.birthday.tm_mon
                && i.birthday.tm_mday < temp.birthday.tm_mday){
            temp = i;
        }
    }
    std::cout << temp.name << "'s next birthday "
            << temp.birthday.tm_mday << "/"
            << temp.birthday.tm_mon << "/"
            << temp.birthday.tm_year << std::endl;
}

int main() {

    std::vector<Birthday_list> birthday_list;
    while(true) {
        std::cout << "Enter the name: ";
        std::string name;
        std::cin >> name;
        if (name == "end") reminders(birthday_list);
        else if(name == "exit") return 0;
        else input_birthday_list(birthday_list, name);
    }
}

