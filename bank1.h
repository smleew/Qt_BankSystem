#ifndef _BANK1_H_
#define _BANK1_H_
#include <map>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

class Bank {
private:
    /* ���� ���� */
    // bool useService = true;
    map<string, int> idToIdx;
    map<long long, Account*> idToAccPtr;
    vector<User> users;
    int curUserIdx = 0;

    /* �Լ� ���� */
    void checkAccount();	//���� ��ȸ
    void makeAccount(); // ���� ����
    void signUp(); // ȸ������
    void signIn();	// �α���
    void loginSystem(); // �α��� �ý���
    void deposit();		//�Ա�
    void withdraw();	//���
    void sendMoney(); // �۱�
    bool checkCurUser(const string& id, const string& pw); // ���� ���� Ȯ��
public:
    Bank();
    ~Bank();
    void bankService();		//�������
};
#endif
