#include "fileManager.h"
#include <QApplication>

//������ ���� ���
void FileManager::printManual(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // cout << "���� ���� ����" << endl;
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        // �� �پ� �о ó��
        qDebug() << line;
    }
    file.close();
}
