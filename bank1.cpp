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

void Bank::bankService() {		//�������
	bool useService = true;
	int selection;
	cout << endl << "[���� ������ �����մϴ�.]" << endl << endl;
	while (useService) {
		while (checkCurUser(users[0].getId(), users[0].getPw())) { // User�� �ʱ� ���̶��
			try {
				loginSystem();
			}
			catch (int n) {
				return;
			}
		}

        // cout << endl << "[���� ����]" << endl;
        // cout << left << setw(20) << "1. ���� ��ȸ";
        // cout << left << setw(20) << "1. Check Account" << endl;
        // cout << left << setw(20) << "2. ���� ����";
        // cout << left << setw(20) << "2. Open Account" << endl;
        // cout << left << setw(20) << "3. �Ա�";
        // cout << left << setw(20) << "3. Deposit" << endl;
        // cout << left << setw(20) << "4. ���";
        // cout << left << setw(20) << "4. Withdraw" << endl;
        // cout << left << setw(20) << "5. ��ü";
        // cout << left << setw(20) << "5. Transfer" << endl;
        // cout << left << setw(20) << "6. �α׾ƿ�";
        // cout << left << setw(20) << "6. Logout" << endl;
        // cout << left << setw(20) << "7. ����";
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
			cout << " - ������ �����մϴ�. -" << endl;
			break;
		default:
			cout << "- �߸��� ��ȣ�� �Է��ϼ̽��ϴ�. -" << endl;
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
	while (idToAccPtr.find(id) != idToAccPtr.end()) { // id �ߺ� ����
		id = dis(gen) % 100000000000000;
		id = abs(id);
	}
	cout << endl << "[���� ����]" << endl;
	cout << "�ʱ� �Աݾ� �Է� (-1 : ���)" << endl;
	cout << ">> ";
	cin >> input;
	if (input == -1) {
		cout << "* ���� ���� ��� *" << endl;
		return;
	}

	cout << "��й�ȣ �Է� (-1 : ���)" << endl;
	cout << ">> ";
	cin >> pw;
	if (pw == "-1") {
		cout << "- ���� ������ ����մϴ�. -" << endl;
		return;
	}

	CUR_USER.addAccount(id, input, pw);
	idToAccPtr[id] = &(CUR_ACC.back());
	cout << "* ���� ���� �Ϸ� *" << endl;
}

void Bank::loginSystem() {
	int selection;
	cout << "[�α��� �ý���]" << endl;
	while (1) {
		cout << "���� ���� -> (1. �α��� : Login / 2. ȸ�� ���� : Sign Up / 3. ���� : Exit) : ";
		cin >> selection;
		if (selection >= 1 && selection <= 3) {
			break;
		}
		cout << "- �߸��� ���ڸ� �Է��ϼ̽��ϴ�. -" << endl << endl;
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
		cout << "- �ý����� �����մϴ�. -" << endl;
		throw 1;
	}
}

void Bank::signUp() {
	string id, pw;
	cout << "[ȸ�� ����]" << endl;
	while (1) {
		cout << ">> ID : ";
		cin >> id;
		if (idToIdx.find(id) == idToIdx.end()) {
			break;
		}
		cout << "* �̹� �����ϴ� ID *" << endl;
		cout << "- �ٸ� ID�� �Է��� �ֽʽÿ�. -" << endl << endl;
	}
	cout << ">> PW : ";
	cin >> pw;
	idToIdx[id] = users.size();
	users.emplace_back(User(id, pw));
	cout << "* ȸ�� ���� �Ϸ� *" << endl;
	cout << "- �α����� �õ��� �ֽʽÿ�. -" << endl << endl;
}

void Bank::signIn() {
	string id, pw;
	cout << "[�α���] (ID, PW�� -1 �Է� : ���)" << endl;
	while (1) {
		cout << ">> ID : ";
		cin >> id;
		cout << ">> PW : ";
		cin >> pw;
		if (id == "-1" && pw == "-1") {
			cout << "* �α��� ��� *" << endl << endl;
			return;
		}

		if (idToIdx.find(id) == idToIdx.end()) {
			cout << "* ��ġ�ϴ� ID ���� *" << endl;
			cout << "- �ٽ� �Է��� �ּ���. -" << endl;
			continue;
		}

		if (!users[idToIdx[id]].checkPw(pw)) {
			cout << "* �߸��� ��й�ȣ *" << endl;
			cout << "- �ٽ� �Է��� �ּ���. -" << endl << endl;
		}
		else {
			cout << "* �α��� ���� *" << endl;
			curUserIdx = idToIdx[id];
			break;
		}
	}
}


void Bank::checkAccount() {	//������ȸ
	if (CUR_ACC.empty()) {
		cout << "* ���� ���� *" << endl;
		cout << "- ���¸� �������ּ���. -" << endl;
	}
	else {
		for (int i = 0; i < CUR_ACC.size(); i++) {
			cout << endl;
			cout << "[" << i + 1 << "�� ����]";
			CUR_ACC[i].printAccountInfo();
		}
	}
}

void Bank::deposit() {		//�Ա�
	int selection = 0;
	LL input;
	while (selection != -1) {
		checkAccount();
		cout << endl << "�Ա� ���� ���� ���� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> selection;
		if (selection <= CUR_ACC.size()) {
			cout << selection << "�� ���°� ���õǾ����ϴ�." << endl;
			selection--;
			break;
		}
		else if(selection == -1) {
			cout << "* �Ա� ��� *" << endl;
			return;
		}
		else {
			cout << "* �߸��� ���� �Է� *" << endl;
			cout << "- �ٽ� �Է����ּ���. -" << endl;
		}
	}
	while (1) {
		cout << endl << "�Ա��� �ݾ� �Է� (-1 : ���) : " << endl;
		cout << ">> ";
		cin >> input;

		try {
			if (input == -1) {
				cout << "* �Ա� ��� *" << endl;
				return;
			}
			if (input > 0) {
				break;
			}
			else {
				throw 1;
			}
		}
		catch (int n) { cout << "- ���� ������ �Է����ּ���. -" << endl; }
	}

	if (CUR_ACC[selection].addBalance(input)) {// �Ա� 
		cout << "* �Ա� ���� *" << endl;
	}
	else {
		cout << "* �Ա� ���� *" << endl;
	}
}

void Bank::withdraw() {	//���
	int selection = 0;
	LL output;
	string pw = "";
	while (selection != -1) {
		checkAccount();
		cout << endl << "����� ���� ���� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> selection;
		if (selection == -1) {
			cout << "* ��� ��� *" << endl;
			return;
		}
		else if (selection <= CUR_ACC.size()) {
			cout << selection << "�� ���°� ���õǾ����ϴ�." << endl;
			selection--;
			break;
		}
		else {
			cout << "* �߸��� ���� �Է� *" << endl;
			cout << "- �ٽ� �Է����ּ���. -" << endl;
		}
	}

	while (1) {
		cout << endl << "���� ��й�ȣ �Է� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> pw;
		if (pw == "-1") {
			cout << "* ��� ��� *" << endl;
			return;
		}
		else if (CUR_ACC[selection].getPw() == pw) {
			break;
		}
		else {
			cout << "* �߸��� ��й�ȣ *" << endl;
			cout << "- �ٽ� �Է����ּ���. -" << endl;
		}
	}

	while (1) {
		cout << endl << "����� �ݾ� �Է� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> output;
		if (output == -1) {
			cout << "* ��� ��� *" << endl;
			return;
		}
		if (output > 0) {
			break;
		}
		else {
			cout << "- ���� ������ �Է����ּ���. -" << endl;
		}
	}

	if (CUR_ACC[selection].subBalance(output)) {// �Ա� 
		cout << "* ��� ���� *" << endl;
		cout << "- ���� �ܾ� : " << CUR_ACC[selection].getBalance() << "�� -" << endl;
	}
	else {
		cout << "* ��� ���� *" << endl;
	}
}

void Bank::sendMoney() {
	int selection = 0;
	LL dest, money;
	string pw;
	while (selection != -1) {
		checkAccount();
		cout << endl << "��ü�� ���� ���� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> selection;
		if (selection <= CUR_ACC.size()) {
			cout << selection << "�� ���°� ���õǾ����ϴ�." << endl;
			selection--;
			break;
		}
		else if (selection == -1) {
			cout << "* ��ü ��� *" << endl;
			return;
		}
		else {
			cout << "* �߸��� ���� �Է� *" << endl;
			cout << "- �ٽ� �Է����ּ���. -" << endl;
		}
	}

	while (1) {
		cout << endl << "��й�ȣ �Է� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> pw;
		if (pw == "-1") {
			cout << "* ��ü ��� *" << endl;
			return;
		}
		else if (CUR_ACC[selection].getPw() == pw) {
			break;
		}
		else {
			cout << "* �߸��� ��й�ȣ *" << endl;
			cout << "- �ٽ� �Է����ּ���. -" << endl;
		}
	}

	while (1) {
		cout << endl << "��ü ���� ���¹�ȣ �Է� (14�ڸ�) (-1 : ���)" << endl;
		cout << ">> ";
		cin >> dest;
		if (dest == -1) {
			cout << "* ��ü ��� *" << endl;
			return;
		}
		if (dest < 10000000000000 || dest >= 100000000000000) {
			cout << "* �߸��� ���¹�ȣ ���� *" << endl;
			cout << "- 14�ڸ��� ���¹�ȣ�� �Է��� �ֽʽÿ�. -" << endl << endl;
		}
		else if(idToAccPtr.find(dest) == idToAccPtr.end()) {
			cout << "* �������� �ʴ� ���� *" << endl;
			cout << "- �ٽ� �Է����ּ���. -" << endl << endl;
		}
		else {
			break;
		}
	}
	while (1) {
		cout << endl << "��ü�� �ݾ� �Է� (-1 : ���)" << endl;
		cout << ">> ";
		cin >> money;
		if (money == -1) {
			cout << "* ��ü ��� *" << endl;
			return;
		}
		if (money <= 0) {
			cout << "* �ݾ� ���� ���� *" << endl;
			cout << "���� ������ �Է��� �ֽʽÿ�." << endl << endl;
		}
		else if (money > CUR_ACC[selection].getBalance()) {
			cout << "* �ܾ��� �ʰ��Ͽ� ��ü�� �� �����ϴ�. *" << endl;
			cout << "���� �ܾ� : " << CUR_ACC[selection].getBalance() << endl << endl;
		}
		else {
			break;
		}
	}
	CUR_ACC[selection].subBalance(money);
	(*idToAccPtr[dest]).addBalance(money);
	cout << endl << "���¹�ȣ " << dest << "�� ��ü�� �Ϸ�Ǿ����ϴ�." << endl;
	cout << "���� �ܾ� : " << CUR_ACC[selection].getBalance() << endl << endl;
	return;
}
