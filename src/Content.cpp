#include <iostream>
#include "Content.hpp"

int main() {
    // ���� Agenda �����ļ���Ϊ "agenda.txt"
    Agenda agenda("agenda.txt");

    while (true) {
        cout << "ѡ�������" << endl;
        cout << "1. �����Ϣ" << endl;
        cout << "2. ������Ϣ" << endl;
        cout << "3. ��ʾ������Ϣ" << endl;
        cout << "4. �˳�" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "������Ϣ��" << endl;
            string info;
            cin.ignore(); // Clear the newline from the buffer
            getline(cin, info);

            cout << "����ʱ�䣺" << endl;
            int year, month, day, hour, min, sec;
            cout << "��: ";
            cin >> year;
            cout << "��: ";
            cin >> month;
            cout << "��: ";
            cin >> day;
            cout << "ʱ: ";
            cin >> hour;
            cout << "��: ";
            cin >> min;
            cout << "��: ";
            cin >> sec;

            Informa infoToAdd(info, year, month, day, hour, min, sec);
            agenda.addInforma(infoToAdd);
            break;
        }
        case 2: {
            cout << "����Ҫ���ҵ�ʱ�䣺" << endl;
            int year, month, day, hour, min, sec;
            cout << "��: ";
            cin >> year;
            cout << "��: ";
            cin >> month;
            cout << "��: ";
            cin >> day;
            cout << "ʱ: ";
            cin >> hour;
            cout << "��: ";
            cin >> min;
            cout << "��: ";
            cin >> sec;

            TimeInfo searchTime = { year, month, day, hour, min, sec };
            int index = agenda.findInformaByTime(searchTime);
            if (index != -1) {
                cout << "�ҵ���Ϣ [" << index << "]: " << agenda.getInfoByIndex(index) << endl;
            }
            else {
                cout << "δ�ҵ�ƥ��ʱ�����Ϣ��" << endl;
            }
            break;
        }
        case 3:
            agenda.displayInforma();
            break;
        case 4:
            cout << "�������˳���" << endl;
            return 0;
        default:
            cout << "��Ч��ѡ��������ѡ�������" << endl;
        }
    }

    return 0;
}
