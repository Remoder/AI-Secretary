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
    Informa* elements; // ʹ��ָ��
    string fileName; // �ճ̱��Ӧ���ļ���

public:
    // ���캯������������ʱ�½��ĵ�
    Agenda(string _fileName) : fileName(_fileName) {
        size = 0;
        elements = new Informa[Maxvalue]; // ��̬�����ڴ�
        loadFromFile(); // ���ļ�������Ϣ���ճ̱�
    }

    ~Agenda() {
        delete[] elements; // �ͷ��ڴ�
        saveToFile(); // ������Ϣ���ļ�
    }
    // �����Ϣ���ճ̱�
    void addInforma(const Informa& info) {
        if (size < Maxvalue) {
            elements[size++] = info;
            cout << "��Ϣ����ӵ��ճ̱�" << endl;
            saveToFile(); // ÿ�������Ϣ�󱣴浽�ļ�
        }
        else {
            cout << "�ճ̱��������޷���Ӹ�����Ϣ��" << endl;
        }
    }

    // ɾ��ָ��λ�õ���Ϣ
    void removeInforma(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; ++i) {
                elements[i] = elements[i + 1];
            }
            size--;
            cout << "��Ϣ�Ѵ��ճ̱���ɾ����" << endl;
            saveToFile(); // ÿ��ɾ����Ϣ�󱣴浽�ļ�
        }
        else {
            cout << "��Ч���������޷�ɾ����Ϣ��" << endl;
        }
    }

    // ������Ϣ����������������������ڷ���-1
    int findInforma(const Informa& info) const {
        for (int i = 0; i < size; ++i) {
            if (elements[i].getInfo() == info.getInfo()) {
                return i;
            }
        }
        return -1; // δ�ҵ���Ϣ
    }

    // ��ʱ�������Ϣ����������������������ڷ���-1
    int findInformaByTime(const TimeInfo& time) const {
        for (int i = 0; i < size; ++i) {
            if (compareTimes(elements[i].getTime(), time) == 0) {
                return i;
            }
        }
        return -1; // δ�ҵ���Ϣ
    }

    // ��ʾ�ճ̱��е�������Ϣ������ʱ��
    void displayInforma() const {
        cout << "�ճ̱��е���Ϣ��" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "[" << i << "] " << elements[i].getInfo()
                << " ʱ�䣺" << elements[i].getTime().year << "-"
                << elements[i].getTime().month << "-"
                << elements[i].getTime().day << " "
                << elements[i].getTime().hour << ":"
                << elements[i].getTime().minute << ":"
                << elements[i].getTime().second << endl;
        }
    }

    // ��ȡָ����������Ϣ
    string getInfoByIndex(int index) const {
        if (index >= 0 && index < size) {
            return elements[index].getInfo();
        }
        return "��Ч������";
    }

private:
    // ���ļ�������Ϣ���ճ̱�
    void loadFromFile() {
        ifstream inputFile(fileName);
        if (inputFile.is_open()) {
            string info; // ��Ӵ���
            while (size < Maxvalue && getline(inputFile, info)) {
                // ʹ��stringstream����ʱ����¼���Ϣ
                istringstream iss(info);
                string eventInfo;
                int year, month, day, hour, min, sec;

                // ���Խ���һ����Ϣ
                if (!(iss >> eventInfo >> year >> month >> day >> hour >> min >> sec)) {
                    cout << "��Ч����: " << info << endl;
                    continue;
                }

                elements[size++] = Informa(eventInfo, year, month, day, hour, min, sec);
            }
            inputFile.close();
        }
    }




    // ������Ϣ���ļ�
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

    // �Ƚ�����ʱ���Ƿ����
    int compareTimes(const TimeInfo& time1, const TimeInfo& time2) const {
        if (time1.year != time2.year) return time1.year - time2.year;
        if (time1.month != time2.month) return time1.month - time2.month;
        if (time1.day != time2.day) return time1.day - time2.day;
        if (time1.hour != time2.hour) return time1.hour - time2.hour;
        if (time1.minute != time2.minute) return time1.minute - time2.minute;
        return time1.second - time2.second;
    }
};
