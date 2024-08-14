#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_
#include <QString>
#include <QVector>
#include <QFile>
using namespace std;

class FileManager {
private:
    QVector<QString> manual;
public:
	FileManager() {};
	~FileManager() {};
    QString printManual(const QString& fileName);
};
#endif
