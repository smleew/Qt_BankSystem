#include <iostream>
#include <iomanip>
#include <random>
#include <limits>
#include "bank1.h"
#define LL long long
#define CUR_USER users[curUserIdx]
#define CUR_ACC CUR_USER.getAccounts()

Bank::Bank() {
	users.emplace_back(User("Init", "0000"));
}

Bank::~Bank() {

}

bool Bank::checkCurUser(const string& id, const string& pw) {
	if (!users[curUserIdx].checkId(id)) {
		return false;
	}
	if (!CUR_USER.checkPw(pw)) {
		return false;
	}
	return true;
}

void Bank::bankService() {		//은행업무
	bool useService = true;
	int selection;
	cout << endl << "[은행 업무를 시작합니다.]" << endl << endl;
	while (useService) {
		while (checkCurUser(users[0].getId(), users[0].getPw())) { // User가 초기 값이라면
			try {
				loginSystem();
			}
			catch (int n) {
				return;
			}
		}

        // cout << endl << "[업무 선택]" << endl;
        // cout << left << setw(20) << "1. 계좌 조회";
        // cout << left << setw(20) << "1. Check Account" << endl;
        // cout << left << setw(20) << "2. 계좌 개설";
        // cout << left << setw(20) << "2. Open Account" << endl;
        // cout << left << setw(20) << "3. 입금";
        // cout << left << setw(20) << "3. Deposit" << endl;
        // cout << left << setw(20) << "4. 출금";
        // cout << left << setw(20) << "4. Withdraw" << endl;
        // cout << left << setw(20) << "5. 이체";
        // cout << left << setw(20) << "5. Transfer" << endl;
        // cout << left << setw(20) << "6. 로그아웃";
        // cout << left << setw(20) << "6. Logout" << endl;
        // cout << left << setw(20) << "7. 종료";
        // cout << left << setw(20) << "7. Exit" << endl;
		cout << ">> ";
		cin >> selection;
		switch (selection) {
		case 1:
			checkAccount();
			break;
		case 2:
			makeAccount();
			break;
		case 3:
			deposit();
			break;
		case 4:
			withdraw();
			break;
		case 5:
			sendMoney();
			break;
		case 6:
			curUserIdx = 0;
			break;
		case 7:
			useService = false;
			cout << " - 업무를 종료합니다. -" << endl;
			break;
		default:
			cout << "- 잘못된 번호를 입력하셨습니다. -" << endl;
			break;
		}
	} 
}

void Bank::makeAccount() {
	long long input, id;
	string pw, name;

	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<long long> dis(numeric_limits<long long>::min(), numeric_limits<long long>::max());
	id = abs(dis(gen) % 100000000000000);
	while (idToAccPtr.find(id) != idToAccPtr.end()) { // id 중복 방지
		id = dis(gen) % 100000000000000;
		id = abs(id);
	}
	cout << endl << "[계좌 개설]" << endl;
	cout << "초기 입금액 입력 (-1 : 취소)" << endl;
	cout << ">> ";
	cin >> input;
	if (input == -1) {
		cout << "* 계좌 개설 취소 *" << endl;
		return;
	}

	cout << "비밀번호 입력 (-1 : 취소)" << endl;
	cout << ">> ";
	cin >> pw;
	if (pw == "-1") {
		cout << "- 계좌 개설을 취소합니다. -" << endl;
		return;
	}

	CUR_USER.addAccount(id, input, pw);
	idToAccPtr[id] = &(CUR_ACC.back());
	cout << "* 계좌 개설 완료 *" << endl;
}

void Bank::loginSystem() {
	int selection;
	cout << "[로그인 시스템]" << endl;
	while (1) {
		cout << "업무 선택 -> (1. 로그인 : Login / 2. 회원 가입 : Sign Up / 3. 종료 : Exit) : ";
		cin >> selection;
		if (selection >= 1 && selection <= 3) {
			break;
		}
		cout << "- 잘못된 숫자를 입력하셨습니다. -" << endl << endl;
	}
	switch (selection) {
	case 1:
		cout << endl;
		signIn();
		break;
	case 2:
		cout << endl;
		signUp();
		break;
	case 3:
	default:
		cout << "- 시스템을 종료합니다. -" << endl;
		throw 1;
	}
}

void Bank::signUp() {
	string id, pw;
	cout << "[회원 가입]" << endl;
	while (1) {
		cout << ">> ID : ";
		cin >> id;
		if (idToIdx.find(id) == idToIdx.end()) {
			break;
		}
		cout << "* 이미 존재하는 ID *" << endl;
		cout << "- 다른 ID를 입력해 주십시오. -" << endl << endl;
	}
	cout << ">> PW : ";
	cin >> pw;
	idToIdx[id] = users.size();
	users.emplace_back(User(id, pw));
	cout << "* 회원 가입 완료 *" << endl;
	cout << "- 로그인을 시도해 주십시오. -" << endl << endl;
}

void Bank::signIn() {
	string id, pw;
	cout << "[로그인] (ID, PW에 -1 입력 : 취소)" << endl;
	while (1) {
		cout << ">> ID : ";
		cin >> id;
		cout << ">> PW : ";
		cin >> pw;
		if (id == "-1" && pw == "-1") {
			cout << "* 로그인 취소 *" << endl << endl;
			return;
		}

		if (idToIdx.find(id) == idToIdx.end()) {
			cout << "* 일치하는 ID 없음 *" << endl;
			cout << "- 다시 입력해 주세요. -" << endl;
			continue;
		}

		if (!users[idToIdx[id]].checkPw(pw)) {
			cout << "* 잘못된 비밀번호 *" << endl;
			cout << "- 다시 입력해 주세요. -" << endl << endl;
		}
		else {
			cout << "* 로그인 성공 *" << endl;
			curUserIdx = idToIdx[id];
			break;
		}
	}
}


void Bank::checkAccount() {	//계좌조회
	if (CUR_ACC.empty()) {
		cout << "* 계좌 없음 *" << endl;
		cout << "- 계좌를 개설해주세요. -" << endl;
	}
	else {
		for (int i = 0; i < CUR_ACC.size(); i++) {
			cout << endl;
			cout << "[" << i + 1 << "번 계좌]";
			CUR_ACC[i].printAccountInfo();
		}
	}
}

void Bank::deposit() {		//입금
	int selection = 0;
	LL input;
	while (selection != -1) {
		checkAccount();
		cout << endl << "입금 받을 계좌 선택 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> selection;
		if (selection <= CUR_ACC.size()) {
			cout << selection << "번 계좌가 선택되었습니다." << endl;
			selection--;
			break;
		}
		else if(selection == -1) {
			cout << "* 입금 취소 *" << endl;
			return;
		}
		else {
			cout << "* 잘못된 숫자 입력 *" << endl;
			cout << "- 다시 입력해주세요. -" << endl;
		}
	}
	while (1) {
		cout << endl << "입금할 금액 입력 (-1 : 취소) : " << endl;
		cout << ">> ";
		cin >> input;

		try {
			if (input == -1) {
				cout << "* 입금 취소 *" << endl;
				return;
			}
			if (input > 0) {
				break;
			}
			else {
				throw 1;
			}
		}
		catch (int n) { cout << "- 양의 정수를 입력해주세요. -" << endl; }
	}

	if (CUR_ACC[selection].addBalance(input)) {// 입금 
		cout << "* 입금 성공 *" << endl;
	}
	else {
		cout << "* 입금 실패 *" << endl;
	}
}

void Bank::withdraw() {	//출금
	int selection = 0;
	LL output;
	string pw = "";
	while (selection != -1) {
		checkAccount();
		cout << endl << "출금할 계좌 선택 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> selection;
		if (selection == -1) {
			cout << "* 출금 취소 *" << endl;
			return;
		}
		else if (selection <= CUR_ACC.size()) {
			cout << selection << "번 계좌가 선택되었습니다." << endl;
			selection--;
			break;
		}
		else {
			cout << "* 잘못된 숫자 입력 *" << endl;
			cout << "- 다시 입력해주세요. -" << endl;
		}
	}

	while (1) {
		cout << endl << "계좌 비밀번호 입력 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> pw;
		if (pw == "-1") {
			cout << "* 출금 취소 *" << endl;
			return;
		}
		else if (CUR_ACC[selection].getPw() == pw) {
			break;
		}
		else {
			cout << "* 잘못된 비밀번호 *" << endl;
			cout << "- 다시 입력해주세요. -" << endl;
		}
	}

	while (1) {
		cout << endl << "출금할 금액 입력 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> output;
		if (output == -1) {
			cout << "* 출금 취소 *" << endl;
			return;
		}
		if (output > 0) {
			break;
		}
		else {
			cout << "- 양의 정수를 입력해주세요. -" << endl;
		}
	}

	if (CUR_ACC[selection].subBalance(output)) {// 입금 
		cout << "* 출금 성공 *" << endl;
		cout << "- 현재 잔액 : " << CUR_ACC[selection].getBalance() << "원 -" << endl;
	}
	else {
		cout << "* 출금 실패 *" << endl;
	}
}

void Bank::sendMoney() {
	int selection = 0;
	LL dest, money;
	string pw;
	while (selection != -1) {
		checkAccount();
		cout << endl << "이체할 계좌 선택 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> selection;
		if (selection <= CUR_ACC.size()) {
			cout << selection << "번 계좌가 선택되었습니다." << endl;
			selection--;
			break;
		}
		else if (selection == -1) {
			cout << "* 이체 취소 *" << endl;
			return;
		}
		else {
			cout << "* 잘못된 숫자 입력 *" << endl;
			cout << "- 다시 입력해주세요. -" << endl;
		}
	}

	while (1) {
		cout << endl << "비밀번호 입력 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> pw;
		if (pw == "-1") {
			cout << "* 이체 취소 *" << endl;
			return;
		}
		else if (CUR_ACC[selection].getPw() == pw) {
			break;
		}
		else {
			cout << "* 잘못된 비밀번호 *" << endl;
			cout << "- 다시 입력해주세요. -" << endl;
		}
	}

	while (1) {
		cout << endl << "이체 받을 계좌번호 입력 (14자리) (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> dest;
		if (dest == -1) {
			cout << "* 이체 취소 *" << endl;
			return;
		}
		if (dest < 10000000000000 || dest >= 100000000000000) {
			cout << "* 잘못된 계좌번호 형식 *" << endl;
			cout << "- 14자리의 계좌번호를 입력해 주십시오. -" << endl << endl;
		}
		else if(idToAccPtr.find(dest) == idToAccPtr.end()) {
			cout << "* 존재하지 않는 계좌 *" << endl;
			cout << "- 다시 입력해주세요. -" << endl << endl;
		}
		else {
			break;
		}
	}
	while (1) {
		cout << endl << "이체할 금액 입력 (-1 : 취소)" << endl;
		cout << ">> ";
		cin >> money;
		if (money == -1) {
			cout << "* 이체 취소 *" << endl;
			return;
		}
		if (money <= 0) {
			cout << "* 금액 형식 오류 *" << endl;
			cout << "양의 정수로 입력해 주십시오." << endl << endl;
		}
		else if (money > CUR_ACC[selection].getBalance()) {
			cout << "* 잔액을 초과하여 이체할 수 없습니다. *" << endl;
			cout << "현재 잔액 : " << CUR_ACC[selection].getBalance() << endl << endl;
		}
		else {
			break;
		}
	}
	CUR_ACC[selection].subBalance(money);
	(*idToAccPtr[dest]).addBalance(money);
	cout << endl << "계좌번호 " << dest << "로 이체가 완료되었습니다." << endl;
	cout << "현재 잔액 : " << CUR_ACC[selection].getBalance() << endl << endl;
	return;
}
