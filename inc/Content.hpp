#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int Maxvalue = 1000;

class Informa {
private:
    string infor;

public:
    Informa(string _infor="") {
        infor = _infor;
    }

    string getInfo() const {
        return infor;
    }
};

class Agenda {
private:
    int size;
    Informa elements[Maxvalue];
    string fileName; // 日程表对应的文件名

public:
    // 构造函数，创建对象时新建文档
    Agenda(string _fileName) : fileName(_fileName) {
        size = 0;
        loadFromFile();  // 从文件加载信息到日程表
    }

    ~Agenda() {
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

    // 显示日程表中的所有信息
    void displayInforma() const {
        cout << "日程表中的信息：" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "[" << i << "] " << elements[i].getInfo() << endl;
        }
    }

private:
    // 从文件加载信息到日程表
    void loadFromFile() {
        ifstream inputFile(fileName);
        if (inputFile.is_open()) {
            while (!inputFile.eof() && size < Maxvalue) {
                string info;
                getline(inputFile, info);
                if (!info.empty()) {
                    elements[size++] = Informa(info);
                }
            }
            inputFile.close();
        }
    }

    // 保存信息到文件
    void saveToFile() const {
        ofstream outputFile(fileName);
        if (outputFile.is_open()) {
            for (int i = 0; i < size; ++i) {
                outputFile << elements[i].getInfo() << endl;
            }
            outputFile.close();
        }
    }
};


