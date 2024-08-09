#include "fileManager.h"
#include <QApplication>

//파일의 내용 출력
void FileManager::printManual(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // cout << "파일 열기 실패" << endl;
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        // 한 줄씩 읽어서 처리
        qDebug() << line;
    }
    file.close();
}
