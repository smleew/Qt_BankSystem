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
    ui->selectLoginService->setCurrentIndex(0);
    ui->selectLoginSignup->setCurrentIndex(0);
    users.emplace_back(User("Init", "0000"));

    fm = FileManager();
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

    connect(ui->btn_login, SIGNAL(clicked()), this, SLOT(btnSignIn()));
    connect(ui->btn_signup, SIGNAL(clicked()), this, SLOT(btnSignUp()));

    connect(ui->btn_loginToSignup, SIGNAL(clicked()), this, SLOT(btnOpenSignUp()));


    connect(ui->btn_cancelSignup, SIGNAL(clicked()), this, SLOT(btnCancelSignUp()));
    connect(ui->btn_exit1, SIGNAL(clicked()), this, SLOT(btnExit()));
    connect(ui->btn_exit2, SIGNAL(clicked()), this, SLOT(btnExit()));
    connect(ui->btn_logout, SIGNAL(clicked()), this, SLOT(btnLogOut()));

    connect(ui->btn_korManual, SIGNAL(clicked()), this, SLOT(btnShowKorManual()));
    connect(ui->btn_engManual, SIGNAL(clicked()), this, SLOT(btnShowEngManual()));

}

void Bank::clearServiceInfo() {
    ui->info_checkAccount->clear();
    ui->info_depositAccountList->clear();
    ui->info_makeAccount->clear();
    ui->info_transferAccountList->clear();
    ui->info_withdrawAccountList->clear();
}

void Bank::clearServiceInput() {
    ui->input_depositAccount->clear();
    ui->input_depositMoney->clear();
    ui->input_initMoney->clear();
    ui->input_makeAccountPw->clear();
    ui->input_transferFromAccount->clear();
    ui->input_transferMoney->clear();
    ui->input_transferPw->clear();
    ui->input_transferToAccount->clear();
    ui->input_withdrawAccount->clear();
    ui->input_withdrawMoney->clear();
    ui->input_withdrawPw->clear();
}


void Bank::btnLogOut() {
    curUserIdx = 0;
    QMessageBox::information(this, "로그아웃 완료", "로그아웃이 완료되었습니다. 로그인을 시도해주세요.",
                             QMessageBox::Ok);
    clearServiceInfo();
    clearServiceInput();
    ui->selectLoginService->setCurrentIndex(0);    
}

void Bank::btnExit() {
    QMessageBox::information(this, "프로그램 종료", "프로그램이 종료되었습니다.",
                             QMessageBox::Ok);
    QApplication::exit(0);
}

void Bank::btnCancelSignUp() {
    ui->input_signupId->clear();
    ui->input_signupPw->clear();
    ui->selectLoginSignup->setCurrentIndex(0);
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

void Bank::btnOpenSignUp() {
    ui->input_loginId->clear();
    ui->input_loginPw->clear();
    ui->selectLoginSignup->setCurrentIndex(1);
}


void Bank::btnSignUp() {
    QString id = ui->input_signupId->text();
    QString pw = ui->input_signupPw->text();
    if(id == "") {
        QMessageBox::warning(this, "ID 입력 오류", "현재 ID가 입력되지 않았습니다. ID를 입력해주세요.");
        return;
    }
    if(pw == "") {
        QMessageBox::warning(this, "비밀번호 입력 오류", "현재 비밀번호가 입력되지 않았습니다. 비밀번호를 입력해주세요.");
        return;
    }
    if (idToIdx.find(id) != idToIdx.end()) {
        QMessageBox::warning(this, "ID 중복", "이미 존재하는 ID입니다.\n다른 ID를 입력해주세요.");
        return;
    }
    idToIdx[id] = users.size();
    users.emplace_back(User(id, pw));
    QMessageBox::information(this, "회원가입 완료", "회원가입이 완료되었습니다. 로그인을 시도해주세요.",
                             QMessageBox::Ok);

    btnCancelSignUp();
    return;
}

void Bank::btnSignIn() {
    QString id = ui->input_loginId->text();
    QString pw = ui->input_loginPw->text();

    if (idToIdx.find(id) == idToIdx.end()) {
        QMessageBox::warning(this, "일치하는 ID 없음", "일치하는 ID가 없습니다.\n다시 입력해주세요.");
        return;

    }
    if (!users[idToIdx[id]].checkPw(pw)) {
        QMessageBox::warning(this, "잘못된 비밀번호", "비밀번호가 잘못되었습니다. 다시 입력해주세요.");
        return;
    }
    QMessageBox::information(this, "로그인 성공", "로그인에 성공했습니다!",
                             QMessageBox::Ok);
    curUserIdx = idToIdx[id];
    ui->input_loginId->clear();
    ui->input_loginPw->clear();
    ui->selectLoginService->setCurrentIndex(1);
    ui->selectService->setCurrentIndex(0);

    return;
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
    bool success;
    LL money = ui->input_depositMoney->text().toLongLong(&success);
    if(!success) {
        ui->info_depositAccountList->setPlainText("잘못된 입금 금액입니다. 다시 입력해주세요.");
        return;
    }
    if(money < 0) {
        ui->info_depositAccountList->setPlainText("잘못된 입금 금액입니다. 다시 입력해주세요.");
        return;
    }

    LL account = ui->input_depositAccount->text().toLongLong(&success);
    if(!success) {
        ui->info_depositAccountList->setPlainText("잘못된 계좌번호입니다. 다시 입력해주세요.");
        return;
    }
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
    ui->input_depositAccount->clear();
    ui->input_depositMoney->clear();
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
    bool success;

    long long input = initMoney.toLongLong(&success);
    if(!success) {
        ui->info_makeAccount->setPlainText("잘못된 입금 금액입니다. 다시 입력해주세요.");
        return;
    }
    if(input < 0) {
        ui->info_makeAccount->setPlainText("잘못된 입금 금액입니다. 다시 입력해주세요.");
        return;
    }

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
    ui->input_makeAccountPw->clear();
    ui->input_initMoney->clear();
    ui->info_makeAccount->setPlainText(tmp);
}


void Bank::btnWithdraw() {
    bool success;
    LL account = ui->input_withdrawAccount->text().toLongLong(&success);
    if(!success) {
        ui->info_withdrawAccountList->setPlainText("잘못된 계좌번호입니다. 다시 입력해주세요.");
        return;
    }

    LL money = ui->input_withdrawMoney->text().toLongLong(&success);
    if(!success) {
        ui->info_withdrawAccountList->setPlainText("잘못된 금액입니다. 다시 입력해주세요.");
        return;
    }
    if(money < 0) {
        ui->info_withdrawAccountList->setPlainText("잘못된 금액입니다. 다시 입력해주세요.");
        return;
    }

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
    bool success;
    LL account = ui->input_transferFromAccount->text().toLongLong(&success);
    if(!success) {
        ui->info_transferAccountList->setPlainText("잘못된 내 계좌번호입니다. 다시 입력해주세요.");
        return;
    }

    LL dest = ui->input_transferToAccount->text().toLongLong(&success);
    if(!success) {
        ui->info_transferAccountList->setPlainText("잘못된 상대 계좌번호입니다. 다시 입력해주세요.");
        return;
    }

    LL money = ui->input_transferMoney->text().toLongLong(&success);
    if(!success) {
        ui->info_transferAccountList->setPlainText("잘못된 송금액입니다. 다시 입력해주세요.");
        return;
    }
    if(money < 0) {
        ui->info_transferAccountList->setPlainText("잘못된 송금액입니다. 다시 입력해주세요.");
        return;
    }

    QString pw = ui->input_transferPw->text();
    account--;

    QString info;
    if(account < 0 || account > CUR_ACC.size()) {
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
        info = info.arg(QString::number(CUR_ACC[account].getBalance()));
    }
    else {
        CUR_ACC[account].subBalance(money);
        (*idToAccPtr[dest]).addBalance(money);
        info = "계좌번호 %1로 이체가 완료되었습니다.\n현재 잔액 : %2";
        info = info.arg(QString::number(dest)).arg(QString::number(CUR_ACC[account].getBalance()));
        ui->info_transferAccountList->setPlainText(info);

        ui->input_transferPw->clear();
        ui->input_transferFromAccount->clear();
        ui->input_transferToAccount->clear();
        ui->input_transferMoney->clear();
        return;
    }
    ui->info_transferAccountList->setPlainText(info);
}

void Bank::btnShowKorManual() {
    QString manual = fm.printManual("korManual.txt");
    QMessageBox::information(nullptr, "한국어 메뉴얼", manual);
    return;
}

void Bank::btnShowEngManual() {
    QString manual = fm.printManual("engManual.txt");
    QMessageBox::information(nullptr, "English Manual", manual);
    return;
}

