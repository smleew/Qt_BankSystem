#include "bank.h"
#include "fileManager.h"

#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // cout << "[���� ���� �޴��� : Bank System Manual]" << endl;
    // cout << "�� �����Ͻʽÿ�. : Choose Language" << endl;
    // cout << "1. �ѱ���" << endl;
    // cout << "2. English" << endl;
    // cout << ">> ";

    int select;
    // cin >> select;
    FileManager fileManager;
    string fileName;
    switch (select) {
    case 1:
        fileName = "korManual.txt";
        break;
    default:
        fileName = "engManual.txt";
        break;
    }
    fileManager.printManual(fileName);


    Bank w;

    w.show();
    return a.exec();
}
