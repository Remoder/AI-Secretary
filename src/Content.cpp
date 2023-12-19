#include <iostream>
#include "Content.hpp"

int main() {
    // 创建 Agenda 对象，文件名为 "agenda.txt"
    Agenda agenda("agenda.txt");

    while (true) {
        cout << "选择操作：" << endl;
        cout << "1. 添加信息" << endl;
        cout << "2. 查找信息" << endl;
        cout << "3. 显示所有信息" << endl;
        cout << "4. 退出" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "输入信息：" << endl;
            string info;
            cin.ignore(); // Clear the newline from the buffer
            getline(cin, info);

            cout << "输入时间：" << endl;
            int year, month, day, hour, min, sec;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            cout << "时: ";
            cin >> hour;
            cout << "分: ";
            cin >> min;
            cout << "秒: ";
            cin >> sec;

            Informa infoToAdd(info, year, month, day, hour, min, sec);
            agenda.addInforma(infoToAdd);
            break;
        }
        case 2: {
            cout << "输入要查找的时间：" << endl;
            int year, month, day, hour, min, sec;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            cout << "时: ";
            cin >> hour;
            cout << "分: ";
            cin >> min;
            cout << "秒: ";
            cin >> sec;

            TimeInfo searchTime = { year, month, day, hour, min, sec };
            int index = agenda.findInformaByTime(searchTime);
            if (index != -1) {
                cout << "找到信息 [" << index << "]: " << agenda.getInfoByIndex(index) << endl;
            }
            else {
                cout << "未找到匹配时间的信息。" << endl;
            }
            break;
        }
        case 3:
            agenda.displayInforma();
            break;
        case 4:
            cout << "程序已退出。" << endl;
            return 0;
        default:
            cout << "无效的选择。请重新选择操作。" << endl;
        }
    }

    return 0;
}
