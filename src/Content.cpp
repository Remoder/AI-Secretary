#include "content.hpp"

int main() {
    // �����ճ̱�ָ���ļ��������ڴ�������ʱ�½��ĵ�
    Agenda myAgenda("agenda.txt");

    while (true) {
        cout << "��ѡ�����:" << endl;
        cout << "1. ����ճ�" << endl;
        cout << "2. ��ʾ�ճ�" << endl;
        cout << "3. ɾ���ճ�" << endl;
        cout << "4. �����ճ�" << endl;
        cout << "0. �˳�" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "������Ҫ��ӵ��ճ���Ϣ��";
            string info;
            cin.ignore(); // ����ǰ��Ļ��з�
            getline(cin, info);
            myAgenda.addInforma(Informa(info));
            break;
        }
        case 2:
            myAgenda.displayInforma();
            break;
        case 3: {
            cout << "������Ҫɾ�����ճ̵�������";
            int indexToDelete;
            cin >> indexToDelete;
            myAgenda.removeInforma(indexToDelete);
            break;
        }
        case 4: {
            cout << "������Ҫ���ҵ��ճ���Ϣ��";
            string infoToFind;
            cin.ignore(); // ����ǰ��Ļ��з�
            getline(cin, infoToFind);
            Informa info(infoToFind);
            int foundIndex = myAgenda.findInforma(info);
            if (foundIndex != -1) {
                cout << "�ҵ���Ϣ������ " << foundIndex << " ����" << endl;
            }
            else {
                cout << "δ�ҵ���Ϣ��" << endl;
            }
            break;
        }
        case 0:
            cout << "�����˳���" << endl;
            return 0;
        default:
            cout << "��Ч��ѡ�����������롣" << endl;
        }
    }

    return 0;
}