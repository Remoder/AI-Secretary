#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include "TimeHelper.hpp"

using namespace std;

const int Maxvalue = 1000;

class Informa {
private:
    string infor;
    TimeInfo Time;

public:
    Informa(string _infor = "", int _year = 0, int _month = 0, int _day = 0, int _hour = 0, int _min = 0, int _sec = 0) {
        infor = _infor;
        Time.year = _year;
        Time.month = _month;
        Time.day = _day;
        Time.hour = _hour;
        Time.minute = _min;
        Time.second = _sec;
    }

    string getInfo() const {
        return infor;
    }

    TimeInfo getTime() const {
        return Time;
    }
};

class Agenda {
private:
    int size;
    Informa* elements; // 使用指针
    string fileName; // 日程表对应的文件名

public:
    // 构造函数，创建对象时新建文档
    Agenda(string _fileName) : fileName(_fileName) {
        size = 0;
        elements = new Informa[Maxvalue]; // 动态分配内存
        loadFromFile(); // 从文件加载信息到日程表
    }

    ~Agenda() {
        delete[] elements; // 释放内存
        saveToFile(); // 保存信息到文件
    }
    // 添加信息到日程表
    void addInforma(const Informa& info) {
        if (size < Maxvalue) {
            elements[size++] = info;
            cout << "信息已添加到日程表。" << endl;
            saveToFile(); // 每次添加信息后保存到文件
        }
        else {
            cout << "日程表已满，无法添加更多信息。" << endl;
        }
    }

    // 删除指定位置的信息
    void removeInforma(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; ++i) {
                elements[i] = elements[i + 1];
            }
            size--;
            cout << "信息已从日程表中删除。" << endl;
            saveToFile(); // 每次删除信息后保存到文件
        }
        else {
            cout << "无效的索引，无法删除信息。" << endl;
        }
    }

    // 查找信息并返回其索引，如果不存在返回-1
    int findInforma(const Informa& info) const {
        for (int i = 0; i < size; ++i) {
            if (elements[i].getInfo() == info.getInfo()) {
                return i;
            }
        }
        return -1; // 未找到信息
    }

    // 按时间查找信息并返回其索引，如果不存在返回-1
    int findInformaByTime(const TimeInfo& time) const {
        for (int i = 0; i < size; ++i) {
            if (compareTimes(elements[i].getTime(), time) == 0) {
                return i;
            }
        }
        return -1; // 未找到信息
    }

    // 显示日程表中的所有信息，包括时间
    void displayInforma() const {
        cout << "日程表中的信息：" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "[" << i << "] " << elements[i].getInfo()
                << " 时间：" << elements[i].getTime().year << "-"
                << elements[i].getTime().month << "-"
                << elements[i].getTime().day << " "
                << elements[i].getTime().hour << ":"
                << elements[i].getTime().minute << ":"
                << elements[i].getTime().second << endl;
        }
    }

    // 获取指定索引的信息
    string getInfoByIndex(int index) const {
        if (index >= 0 && index < size) {
            return elements[index].getInfo();
        }
        return "无效的索引";
    }

private:
    // 从文件加载信息到日程表
    void loadFromFile() {
        ifstream inputFile(fileName);
        if (inputFile.is_open()) {
            string info; // 添加此行
            while (size < Maxvalue && getline(inputFile, info)) {
                // 使用stringstream解析时间和事件信息
                istringstream iss(info);
                string eventInfo;
                int year, month, day, hour, min, sec;

                // 尝试解析一行信息
                if (!(iss >> eventInfo >> year >> month >> day >> hour >> min >> sec)) {
                    cout << "无效的行: " << info << endl;
                    continue;
                }

                elements[size++] = Informa(eventInfo, year, month, day, hour, min, sec);
            }
            inputFile.close();
        }
    }




    // 保存信息到文件
    void saveToFile() const {
        ofstream outputFile(fileName);
        if (outputFile.is_open()) {
            for (int i = 0; i < size; ++i) {
                outputFile << elements[i].getInfo() << " "
                    << elements[i].getTime().year << " "
                    << elements[i].getTime().month << " "
                    << elements[i].getTime().day << " "
                    << elements[i].getTime().hour << " "
                    << elements[i].getTime().minute << " "
                    << elements[i].getTime().second << endl;
            }
            outputFile.close();
        }
    }

    // 比较两个时间是否相等
    int compareTimes(const TimeInfo& time1, const TimeInfo& time2) const {
        if (time1.year != time2.year) return time1.year - time2.year;
        if (time1.month != time2.month) return time1.month - time2.month;
        if (time1.day != time2.day) return time1.day - time2.day;
        if (time1.hour != time2.hour) return time1.hour - time2.hour;
        if (time1.minute != time2.minute) return time1.minute - time2.minute;
        return time1.second - time2.second;
    }
};
