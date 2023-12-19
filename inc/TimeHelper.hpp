#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>

class TimeInfo {
public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    TimeInfo(int y = 0, int mon = 0, int d = 0, int h = 0, int min = 0, int sec = 0)
        : year(y), month(mon), day(d), hour(h), minute(min), second(sec) {}

    bool operator<(const TimeInfo& other) const {
        if (year != other.year) {
            return year < other.year;
        }
        if (month != other.month) {
            return month < other.month;
        }
        if (day != other.day) {
            return day < other.day;
        }
        if (hour != other.hour) {
            return hour < other.hour;
        }
        if (minute != other.minute) {
            return minute < other.minute;
        }
        return second < other.second;
    }

    std::tm to_tm() const {
        std::tm tmTargetTime = {};
        tmTargetTime.tm_year = year - 1900;
        tmTargetTime.tm_mon = month - 1;
        tmTargetTime.tm_mday = day;
        tmTargetTime.tm_hour = hour;
        tmTargetTime.tm_min = minute;
        tmTargetTime.tm_sec = second;
        return tmTargetTime;
    }
};

void showMessage(const std::string& message) {
    std::cout << message << std::endl;
}
