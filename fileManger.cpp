#include "fileManager.h"

//������ ���� ���
void FileManager::printManual(const string& fileName)
{
    ifstream fin(fileName);
    if (!fin) {
        cout << "���� ���� ����" << endl;
        return;
    }
    char buf[200];
    while (fin.getline(buf, 200)) {
        cout << buf << endl;
    }
    fin.close();
}
