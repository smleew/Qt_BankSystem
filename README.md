# 한화은행 계좌 관리 시스템
Qt와 C++을 이용하여 회원가입, 로그인, 계좌 개설, 조회, 입출금, 이체 기능을 구현한 프로그램입니다.

## 메뉴얼
* 한국어 메뉴얼과 영어 메뉴얼을 선택해서 볼 수 있습니다.

* 단, 파일 입출력을 요하기에 절대경로 지정이 필요합니다. 절대경로는 fileManager.cpp파일에서 수정할 수 있습니다.

![image](https://github.com/user-attachments/assets/0871cc18-d99a-4ab4-a3e6-01dc6194c460)
![image](https://github.com/user-attachments/assets/d6f95f5c-46ce-4648-ae95-86708cedf4bc)
![image](https://github.com/user-attachments/assets/93d1d17c-f5dd-4139-b2d4-663ba3b5637b)


## 로그인
* 아이디와 사용자암호를 입력하여 로그인을 진행합니다.

* 회원가입 버튼 : 회원가입 메뉴로 이동합니다.

![image](https://github.com/user-attachments/assets/b7885225-e4cc-49b9-b683-c7b54b45dbdc)


## 회원가입
* 아이디와 사용자암호를 입력하여 회원가입을 진행합니다.

* 뒤로가기 버튼 : 로그인 메뉴로 돌아갑니다.

![image](https://github.com/user-attachments/assets/f86890b4-ba99-4418-8a46-4d3fcc8b3996)


## 계좌개설
* 초기 입금액과 계좌 비밀번호를 입력하여 개좌를 개설합니다.

* 계좌 개설 완료시 계좌번호, 잔액, 비밀번호를 출력합니다.

![image](https://github.com/user-attachments/assets/ff61d355-146f-4347-ad82-c195d9e0739f)


## 계좌조회
* 현재 개설된 계좌를 조회합니다.

* 계좌 조회 버튼을 누르면 계좌번호와 잔액이 표시됩니다.

![image](https://github.com/user-attachments/assets/789beff5-e4ef-455d-ae6c-18389466d219)


## 입금
* 계좌조회 버튼을 눌러 계좌를 조회합니다.

* 입금받을 계좌의 순번과 입금하실 금액을 입력합니다.

* 입금에 성공한 경우 입금 계좌, 입금 금액, 현재 잔액을 표시합니다.

![image](https://github.com/user-attachments/assets/f94f8c7d-4b7f-4f68-9784-401ff0c80aba)
![image](https://github.com/user-attachments/assets/9c60c845-4364-4f5d-9826-e7c65da9f1cb)



## 출금
* 계좌조회 버튼을 눌러 계좌를 조회합니다.

* 출금할 계좌의 순번, 출금하실 금액, 계좌 비밀번호를 입력합니다.

* 출금에 성공한 경우 출금 계좌, 출금 금액, 현재 잔액을 표시합니다.

![image](https://github.com/user-attachments/assets/4d6c1431-7461-4284-974c-34b21a620072)
![image](https://github.com/user-attachments/assets/364bd843-13de-45cb-a27f-74ddafd07686)



## 이체
* 계좌조회 버튼을 눌러 계좌를 조회합니다.

* 이체할 계좌의 순번, 계좌 비밀번호, 이체할 금액, 이체 받을 계좌번호 (14자리)를 입력합니다.

* 이체에 성공한 경우 이체받은 계좌번호와 현재 잔액을 표시합니다.

![image](https://github.com/user-attachments/assets/0569b986-f490-4cf4-864c-5813d8a33c3a)
![image](https://github.com/user-attachments/assets/1a5b9b75-831d-4292-8e5d-63914f7769d7)

