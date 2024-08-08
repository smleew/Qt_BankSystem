#include "fileManager.h"

//파일의 내용 출력
void FileManager::printManual(const string& fileName)
{
    ifstream fin(fileName);
    if (!fin) {
        cout << "파일 열기 실패" << endl;
        return;
    }
    char buf[200];
    while (fin.getline(buf, 200)) {
        cout << buf << endl;
    }
    fin.close();
}
