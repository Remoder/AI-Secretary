#include "content.hpp"

int main() {
    // 创建日程表并指定文件名，会在创建对象时新建文档
    Agenda myAgenda("agenda.txt");

    while (true) {
        cout << "请选择操作:" << endl;
        cout << "1. 添加日程" << endl;
        cout << "2. 显示日程" << endl;
        cout << "3. 删除日程" << endl;
        cout << "4. 查找日程" << endl;
        cout << "0. 退出" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "请输入要添加的日程信息：";
            string info;
            cin.ignore(); // 忽略前面的换行符
            getline(cin, info);
            myAgenda.addInforma(Informa(info));
            break;
        }
        case 2:
            myAgenda.displayInforma();
            break;
        case 3: {
            cout << "请输入要删除的日程的索引：";
            int indexToDelete;
            cin >> indexToDelete;
            myAgenda.removeInforma(indexToDelete);
            break;
        }
        case 4: {
            cout << "请输入要查找的日程信息：";
            string infoToFind;
            cin.ignore(); // 忽略前面的换行符
            getline(cin, infoToFind);
            Informa info(infoToFind);
            int foundIndex = myAgenda.findInforma(info);
            if (foundIndex != -1) {
                cout << "找到信息在索引 " << foundIndex << " 处。" << endl;
            }
            else {
                cout << "未找到信息。" << endl;
            }
            break;
        }
        case 0:
            cout << "程序退出。" << endl;
            return 0;
        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
    }

    return 0;
}