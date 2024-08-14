#include "bank.h"
#include "fileManager.h"

#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bank w;
    w.show();
    return a.exec();
}
