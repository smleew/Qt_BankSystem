#ifndef BANK_H
#define BANK_H
#include <QMap>
#include <QString>
#include <QVector>
#include "user.h"
using namespace std;

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Bank;
}
QT_END_NAMESPACE

class Bank : public QWidget
{
    Q_OBJECT

public:
    Bank(QWidget *parent = nullptr);
    ~Bank();


private:
    Ui::Bank *ui;

    /* ���� ���� */
    // bool useService = true;
    QMap<QString, int> idToIdx;
    QMap<long long, Account*> idToAccPtr;
    QVector<User> users;
    int curUserIdx = 0;

    /* �Լ� ���� */
    void bankService();		//�������
    void checkAccount();	//���� ��ȸ
    void makeAccount(); // ���� ����
    void signUp(); // ȸ������
    void signIn();	// �α���
    void loginSystem(); // �α��� �ý���
    void deposit();		//�Ա�
    void withdraw();	//���
    void sendMoney(); // �۱�
    bool checkCurUser(const QString& id, const QString& pw); // ���� ���� Ȯ��
    void linkButtons();

public slots:
    void btnCheckAccount();
    void btnDeposit();
    void btnDepositCheck();
    void btnMakeAccount();

};
#endif // BANK_H
