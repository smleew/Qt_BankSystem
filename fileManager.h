#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "bank.h"
using namespace std;

class FileManager {
private:
	vector<string> manual;
public:
	FileManager() {};
	~FileManager() {};
	void printManual(const string& fileName);
};
#endif