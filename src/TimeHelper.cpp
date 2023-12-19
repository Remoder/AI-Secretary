#include "TimeHelper.hpp"

int main() {
    std::vector<TimeInfo> timeList;

    int numTimes;
    std::cout << "Enter the number of times: ";
    std::cin >> numTimes;

    for (int i = 0; i < numTimes; ++i) {
        TimeInfo time;
        std::cout << "Enter time " << i + 1 << " (YYYY MM DD HH MM SS): ";
        std::cin >> time.year >> time.month >> time.day >> time.hour >> time.minute >> time.second;

        if (time.year < 1900 || time.month < 1 || time.month > 12 ||
            time.day < 1 || time.day > 31 || time.hour < 0 || time.hour > 23 ||
            time.minute < 0 || time.minute > 59 || time.second < 0 || time.second > 59) {
            std::cerr << "Invalid input. Please enter a valid date and time." << std::endl;
            return 1;
        }

        timeList.push_back(time);
    }

    std::sort(timeList.begin(), timeList.end());

    for (const auto& targetTime : timeList) {
        auto target_tm = targetTime.to_tm();
        auto targetTimePoint = std::chrono::system_clock::from_time_t(std::mktime(&target_tm));

        auto currentTimePoint = std::chrono::system_clock::now();
        auto timeToWait = std::chrono::duration_cast<std::chrono::seconds>(targetTimePoint - currentTimePoint);

        if (timeToWait.count() > 0) {
            std::cout << "Waiting for target time..." << std::endl;
            std::this_thread::sleep_for(timeToWait);
        }

        showMessage("Time's up!");
    }

    showMessage("Last time's up!");

    return 0;
}
