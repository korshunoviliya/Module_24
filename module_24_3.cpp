#include <iostream>
#include <ctime>
#include <iomanip>

#define SECONDS_PER_MINUTE 60

void startTimer(std::tm *timer){
    std::time_t temp = (timer->tm_min * SECONDS_PER_MINUTE) + timer->tm_sec;
    std::time_t now_time = std::time(nullptr);
    temp += now_time;
    timer->tm_min = 0;
    timer->tm_sec = 0;
    std::time_t count = now_time;

    while (true){
        now_time = std::time(nullptr);
        if(temp == now_time){
            std::cout << "DING! DING! DING!\n";
            break;
        }
        if(count == now_time){
            std::cout << std::put_time(timer, "%M:%S") << std::endl;
            ++count;
            ++(timer->tm_sec);
            if(timer->tm_sec >= (SECONDS_PER_MINUTE)){
                ++(timer->tm_min);
                timer->tm_sec = 0;
            }
        }
    }
}

int main() {

    std::time_t t = std::time(nullptr);
    std::tm *timer = std::localtime(&t);
    std::cout << "Enter the time in format MM:SS : ";
    std::cin >> std::get_time(timer, "%M:%S");

    startTimer(timer);
    return 0;
}