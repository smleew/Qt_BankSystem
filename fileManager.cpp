#include "fileManager.h"
#include <QApplication>
#include <QDir> // 디버깅용

//파일의 내용 출력
QString FileManager::printManual(const QString& fileName)
{
    QDir::setCurrent("C:/Users/change30/Desktop/Qt/Qt_BankSystem"); // 절대경로 지정 필요
    QString result = "";
    QFile file(fileName);
    if (!file.exists()) {
        return QDir::currentPath();
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        result = "파일 열기 실패";
        return result;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        result.append("\n");
        result.append(line);
    }
    file.close();
    return result;
}
