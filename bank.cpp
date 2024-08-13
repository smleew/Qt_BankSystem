#include "bank.h"
#include "./ui_bank.h"
#include <iomanip>
#include <random>
#include <limits>
#define LL long long
#define CUR_USER users[curUserIdx]
#define CUR_ACC CUR_USER.getAccounts()

Bank::Bank(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bank)
{
    ui->setupUi(this);
    linkButtons();
    ui->selectLoginService->setCurrentIndex(1);
    users.emplace_back(User("Init", "0000"));
}

Bank::~Bank()
{
    delete ui;
}

void Bank::linkButtons() {
    connect(ui->btn_checkAccount, SIGNAL(clicked()), this, SLOT(btnCheckAccount()));
    connect(ui->btn_deposit, SIGNAL(clicked()), this, SLOT(btnDeposit()));
    connect(ui->btn_depositAccountList, SIGNAL(clicked()), this, SLOT(btnDepositAccountList()));
    connect(ui->btn_makeAccount, SIGNAL(clicked()), this, SLOT(btnMakeAccount()));

    connect(ui->btn_withdraw, SIGNAL(clicked()), this, SLOT(btnWithdraw()));
    connect(ui->btn_withdrawAccountList, SIGNAL(clicked()), this, SLOT(btnWithdrawAccountList()));

    connect(ui->btn_transfer, SIGNAL(clicked()), this, SLOT(btnTransfer()));
    connect(ui->btn_transferAccountList, SIGNAL(clicked()), this, SLOT(btnTransferAccountList()));
}

bool Bank::checkCurUser(const QString& id, const QString& pw) {
    if (!users[curUserIdx].checkId(id)) {
        return false;
    }
    if (!CUR_USER.checkPw(pw)) {
        return false;
    }
    return true;
}

void Bank::loginSystem() {
    int selection = 0;
    // cout << "[로그인시스템]" << endl;
    while (1) {
        // cout << "업무 선택 -> (1. 로그인 : Login / 2. 회원 가입 : Sign Up / 3. 종료 : Exit) : ";
        // cin >> selection;
        if (selection >= 1 && selection <= 3) {
            break;
        }
        // cout << "- 잘못된 숫자를 입력하셨습니다. -" << endl << endl;
    }
    switch (selection) {
    case 1:
        // cout << endl;
        signIn();
        break;
    case 2:
        // cout << endl;
        signUp();
        break;
    case 3:
    default:
        // cout << "- 시스템을 종료합니다. -" << endl;
        throw 1;
    }
}

void Bank::signUp() {
    QString id = "", pw = "";
    // cout << "[회원 가입]" << endl;
    while (1) {
        // cout << ">> ID : ";
        // cin >> id;
        if (idToIdx.find(id) == idToIdx.end()) {
            break;
        }
        // cout << "* 이미 존재하는 ID *" << endl;
        // cout << "- 다른 ID를 입력해 주십시오. -" << endl << endl;
    }
    // cout << ">> PW : ";
    // cin >> pw;
    idToIdx[id] = users.size();
    users.emplace_back(User(id, pw));
    // cout << "* 회원 가입 완료 *" << endl;
    // cout << "- 로그인을 시도해 주십시오. -" << endl << endl;
}

void Bank::signIn() {
    QString id = "", pw = "";
    // cout << "[로그인] (ID, PW에 -1 입력 : 취소)" << endl;
    while (1) {
        // cout << ">> ID : ";
        // cin >> id;
        // cout << ">> PW : ";
        // cin >> pw;
        if (id == "-1" && pw == "-1") {
            // cout << "* 로그인 취소 *" << endl << endl;
            return;
        }

        if (idToIdx.find(id) == idToIdx.end()) {
            // cout << "* 일치하는 ID 없음 *" << endl;
            // cout << "- 다시 입력해 주세요. -" << endl;
            continue;
        }

        if (!users[idToIdx[id]].checkPw(pw)) {
            // cout << "* 잘못된 비밀번호 *" << endl;
            // cout << "- 다시 입력해 주세요. -" << endl << endl;
        }
        else {
            // cout << "* 로그인 성공 *" << endl;
            curUserIdx = idToIdx[id];
            break;
        }
    }
}

void Bank::btnCheckAccount() {
    QString info = "";
    if (CUR_ACC.empty()) {
        info = "* 계좌 없음 *\n- 계좌를 개설해주세요. -";
    }
    else {
        QString tmp;
        for (int i = 0; i < CUR_ACC.size(); i++) {
            tmp = "[%1번 계좌]\n";
            tmp = tmp.arg(QString::number(i + 1));
            tmp.append("계좌번호: ");
            tmp.append(QString::number(CUR_ACC[i].getId()));
            tmp.append("\n잔액: ");
            tmp.append(QString::number(CUR_ACC[i].getBalance()));
            tmp.append("\n\n");
            info.append(tmp);
        }
    }
    ui->info_checkAccount->setPlainText(info);
}
void Bank::btnDeposit() {
    LL account = ui->input_depositAccount->text().toLongLong();
    LL money = ui->input_depositMoney->text().toLongLong();
    account--;

    QString info;
    if(account >= CUR_ACC.size() || account < 0) {
        info = "잘못된 계좌입니다. 다시 입력해주세요";
    }
    else if (CUR_ACC[account].addBalance(money)) {// 입금
        info = "입금에 성공했습니다.\n입금 계좌: %1\n입금 금액: %2\n현재 잔액: %3";
        info = info.arg(QString::number(CUR_ACC[account].getId())).arg(QString::number(money)).arg(QString::number(CUR_ACC[account].getBalance()));
    }
    else {
        info = "입금에 실패했습니다.";
    }
    ui->info_depositAccountList->setPlainText(info);
}


void Bank::btnDepositAccountList() {
    QString info = "";
    if (CUR_ACC.empty()) {
        info = "* 계좌 없음 *\n- 계좌를 개설해주세요. -";
    }
    else {
        QString tmp;
        for (int i = 0; i < CUR_ACC.size(); i++) {
            tmp = "[%1번 계좌]\n";
            tmp = tmp.arg(QString::number(i + 1));
            tmp.append("계좌번호: ");
            tmp.append(QString::number(CUR_ACC[i].getId()));
            tmp.append("\n잔액: ");
            tmp.append(QString::number(CUR_ACC[i].getBalance()));
            tmp.append("\n\n");
            info.append(tmp);
        }
    }
    ui->info_depositAccountList->setPlainText(info);
}


void Bank::btnMakeAccount() {
    QString initMoney = ui->input_initMoney->text();
    QString pw = ui->input_makeAccountPw->text();

    long long input = initMoney.toLongLong();
    long long id = 0;

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dis(numeric_limits<long long>::min(), numeric_limits<long long>::max());
    id = abs(dis(gen) % 100000000000000);
    while (idToAccPtr.find(id) != idToAccPtr.end()) { // id 중복 방지
        id = dis(gen) % 100000000000000;
        id = abs(id);
    }

    CUR_USER.addAccount(id, input, pw);
    idToAccPtr[id] = &(CUR_ACC.back());
    QString tmp = "[계좌 개설 완료]\n계좌번호: %1\n잔액: %2원\n비밀번호: %3\n";
    tmp = tmp.arg(QString::number(id)).arg(initMoney).arg(pw);
    ui->info_makeAccount->setPlainText(tmp);
}


void Bank::btnWithdraw() {
    LL account = ui->input_withdrawAccount->text().toLongLong();
    LL money = ui->input_withdrawMoney->text().toLongLong();
    QString pw = ui->input_withdrawPw->text();
    account--;

    QString info;
    if(account >= CUR_ACC.size() || account < 0) {
        info = "잘못된 계좌입니다. 다시 입력해주세요";
    }
    else if (CUR_ACC[account].getPw() != pw) {
        info = "비밀번호가 잘못되었습니다. 다시 입력해주세요";
    }
    else if(money <= 0) {
        info = "출금할 금액을 양의 정수로 입력해주세요.";
    }
    else if (CUR_ACC[account].subBalance(money)) {// 입금
        info = "출금에 성공했습니다.\n출금 계좌: %1\n출금 금액: %2\n현재 잔액: %3";
        info = info.arg(QString::number(CUR_ACC[account].getId())).arg(QString::number(money)).arg(QString::number(CUR_ACC[account].getBalance()));
    }
    else {
        info = "출금에 실패했습니다.\n사유 : 잔액부족";
    }
    ui->info_withdrawAccountList->setPlainText(info);
}

void Bank::btnWithdrawAccountList() {
    QString info = "";
    if (CUR_ACC.empty()) {
        info = "* 계좌 없음 *\n- 계좌를 개설해주세요. -";
    }
    else {
        QString tmp;
        for (int i = 0; i < CUR_ACC.size(); i++) {
            tmp = "[%1번 계좌]\n";
            tmp = tmp.arg(QString::number(i + 1));
            tmp.append("계좌번호: ");
            tmp.append(QString::number(CUR_ACC[i].getId()));
            tmp.append("\n잔액: ");
            tmp.append(QString::number(CUR_ACC[i].getBalance()));
            tmp.append("\n\n");
            info.append(tmp);
        }
    }
    ui->info_withdrawAccountList->setPlainText(info);
}

void Bank::btnTransferAccountList() {
    QString info = "";
    if (CUR_ACC.empty()) {
        info = "* 계좌 없음 *\n- 계좌를 개설해주세요. -";
    }
    else {
        QString tmp;
        for (int i = 0; i < CUR_ACC.size(); i++) {
            tmp = "[%1번 계좌]\n";
            tmp = tmp.arg(QString::number(i + 1));
            tmp.append("계좌번호: ");
            tmp.append(QString::number(CUR_ACC[i].getId()));
            tmp.append("\n잔액: ");
            tmp.append(QString::number(CUR_ACC[i].getBalance()));
            tmp.append("\n\n");
            info.append(tmp);
        }
    }
    ui->info_transferAccountList->setPlainText(info);
}


void Bank::btnTransfer() {
    LL account = ui->input_transferFromAccount->text().toLongLong();
    LL dest = ui->input_transferToAccount->text().toLongLong();
    LL money = ui->input_transferMoney->text().toLongLong();
    QString pw = ui->input_transferPw->text();
    account--;

    QString info;
    if(account < 0 || account < CUR_ACC.size()) {
        info = "잘못된 계좌입니다. 다시 선택해주세요.";
    }
    else if(CUR_ACC[account].getPw() != pw) {
        info = "비밀번호가 틀렸습니다. 다시 입력해주세요.";
    }
    else if (dest < 10000000000000 || dest >= 100000000000000) {
        info = "* 잘못된 계좌번호 형식 *\n- 14자리의 계좌번호를 입력해 주십시오. -";
    }
    else if(idToAccPtr.find(dest) == idToAccPtr.end()) {
        info = "* 존재하지 않는 계좌 *\n- 다시 입력해주세요. -";
    }
    else if (money <= 0) {
        info = "* 금액 형식 오류 *\n양의 정수로 입력해 주십시오.";
    }
    else if (money > CUR_ACC[account].getBalance()) {
        info = "* 잔액을 초과하여 이체할 수 없습니다. *\n";
        info.append("현재 잔액 : %1");
        info.arg(QString::number(CUR_ACC[account].getBalance()));
    }
    else {
        CUR_ACC[account].subBalance(money);
        (*idToAccPtr[dest]).addBalance(money);
        info = "계좌번호 %1로 이체가 완료되었습니다.\n";
        info.append("현재 잔액: %2");
        info.arg(QString::number(dest)).arg(QString::number(CUR_ACC[account].getBalance()));
    }
    ui->info_transferAccountList->setPlainText(info);
}
