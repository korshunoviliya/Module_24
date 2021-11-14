#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

struct Birthday_list{
    std::tm birthday{};
    std::string name;
};

bool compare(const Birthday_list &a, const Birthday_list &b){
    if(a.birthday.tm_mon < b.birthday.tm_mon) return true;
    if(a.birthday.tm_mon > b.birthday.tm_mon) return false;
    return a.birthday.tm_mday < b.birthday.tm_mday;
}

void remindersSort (std::vector<Birthday_list> &birthday_list){
    bool check{false};
    bool last_year{false};
    bool today_birthday{false};

    std::sort(birthday_list.begin(), birthday_list.end(), compare);

    std::time_t t{std::time(nullptr)};
    std::tm *now{std::localtime(&t)};

    for (int i = 0; i < birthday_list.size(); ++i){

        if (!last_year
                && ((now->tm_mon == birthday_list[i].birthday.tm_mon)
                && (now->tm_mday == birthday_list[i].birthday.tm_mday))){
            std::cout << "Today is " << birthday_list[i].name << "`s Birthday!\n";
            check = true;
            today_birthday = true;
        }
        else if ((!today_birthday)
                 && ((birthday_list[i].birthday.tm_mon == now->tm_mon)
                 && ((birthday_list[i].birthday.tm_mday > now->tm_mday))
                 || (birthday_list[i].birthday.tm_mon > now->tm_mon))){
            std::cout << birthday_list[i].name << "'s next birthday "
                      << std::put_time(&(birthday_list[i].birthday), "%Y/%m/%d") << std::endl;
            check = true;

               if ((i != birthday_list.size() - 1)
                    && ((birthday_list[i + 1].birthday.tm_mon != birthday_list[i].birthday.tm_mon)
                    || (birthday_list[i + 1].birthday.tm_mday != birthday_list[i].birthday.tm_mday))){
                    break;
               }
        }
        if ((i == birthday_list.size() - 1) && !check) {
                    i = -1;
                    now->tm_mon = 0;
                    now->tm_mday = 0;
                    last_year = true;
        }

    }
}

void input_birthday_list(std::vector<Birthday_list> &birthday_list, std::string &name){
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

int main() {
    std::vector<Birthday_list> birthday_list;
    while(true) {
        std::cout << "Enter the name: ";
        std::string name;
        std::cin >> name;
        if (name == "end") remindersSort(birthday_list);
        else if(name == "exit") return 0;
        else input_birthday_list(birthday_list, name);
    }
}