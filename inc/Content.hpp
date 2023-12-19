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
    string fileName; // �ճ̱��Ӧ���ļ���

public:
    // ���캯������������ʱ�½��ĵ�
    Agenda(string _fileName) : fileName(_fileName) {
        size = 0;
        loadFromFile();  // ���ļ�������Ϣ���ճ̱�
    }

    ~Agenda() {
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

    // ��ʾ�ճ̱��е�������Ϣ
    void displayInforma() const {
        cout << "�ճ̱��е���Ϣ��" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "[" << i << "] " << elements[i].getInfo() << endl;
        }
    }

private:
    // ���ļ�������Ϣ���ճ̱�
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

    // ������Ϣ���ļ�
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


