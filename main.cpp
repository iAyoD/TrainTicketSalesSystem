#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<time.h>
#include<string>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include"users.h"

using namespace std;

void showMainMenu();
void showRegisterLoginMenu();
string showTime();
void Register();
void Login();
void userManage();
void ticketInfoManage();
void searchTicketInfo();
void buyAndRefundTicket();

vector<Normal> normal_users;
vector<Admin> admins;
User *p = new User;
Normal A;
Admin B;
bool isNormal = false;
bool isAdmin = false;

int main()
{
	while (true) {
		showRegisterLoginMenu();
		if (isNormal || isAdmin) {
			showMainMenu();
		}
	}
	return 0;
}

void showMainMenu()
{
	bool mainFlag = true;
	do {
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		if (isNormal) {
			cout << "                                   ���ã�" << p->username << "!" << endl;
		}
		else {
			cout << "                                   ���ã�����Ա��" << endl;
		}
		cout << endl;
		cout << "                                   1.�û�����" << endl;
		cout << "                                   2.��Ʊ��Ϣ����" << endl;
		cout << "                                   3.�����������ҳ�Ʊ��Ϣ" << endl;
		cout << "                                   4.��Ʊ����Ʊ����" << endl;
		cout << "                                   5.������ͳ����Ʊ����" << endl;
		cout << "                                   6.�����β�ѯ��Ʊ����" << endl;
		cout << "                                   7.���복Ʊ��Ϣ" << endl;
		cout << "                                   8.������Ʊ��Ϣ" << endl;
		cout << "                                   9.�˳���¼" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		char command;
		cin >> command;
		switch (command) {
		case '1': {
			system("cls");
			userManage();
			break;
		}
		case '2': {
			system("cls");
			ticketInfoManage();
			break;
		}
		case '3': {
			system("cls");
			searchTicketInfo();
			break;
		}
		case '4': {
			system("cls");
			buyAndRefundTicket();
			break;
		}
		case '5': {
			system("cls");
			p->calSaleNumByTrain();
			break;
		}
		case '6': {
			system("cls");
			p->calRemainNumByTrain();
			break;
		}
		case '7': {
			system("cls");
			if (isNormal) {
				cout << setfill('=') << setw(100) << "=" << endl;
				cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
				cout << "                                   ���ã�" << p->username << "!" << endl;
				cout << "                             ����ʱ�䣺" << showTime() << endl;
				cout << "                                   ��Ǹ������Ҫʹ�ù���ԱȨ�޷��ʴ˽��棡" << endl;
				cout << setfill('=') << setw(100) << "=" << endl;
				system("pause");
			}
			else {
				p->insertTickets();
			}
			break;
		}
		case '8': {
			system("cls");
			if (isNormal) {
				cout << setfill('=') << setw(100) << "=" << endl;
				cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
				cout << "                                   ���ã�" << p->username << "!" << endl;
				cout << "                             ����ʱ�䣺" << showTime() << endl;
				cout << "                                   ��Ǹ������Ҫʹ�ù���ԱȨ�޷��ʴ˽��棡" << endl;
				cout << setfill('=') << setw(100) << "=" << endl;
				system("pause");
			}
			else {
				p->exportTickets();
			}
			break;
		}
		case '9': {
			system("cls");
			mainFlag = false;
			isAdmin = false;
			isNormal = false;
			break;
		}
		default:
			cout << "��������ȷ�����֣�" << endl;
		}
	} while (mainFlag);
}

string showTime()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int year, month, day, h, m, s;
	year = 1900 + ltm->tm_year;
	month = 1 + ltm->tm_mon;
	day = ltm->tm_mday;
	h = ltm->tm_hour;
	m = ltm->tm_min;
	s = ltm->tm_sec;
	string t;
	t = to_string(year) + "��" + to_string(month) + "��" + to_string(day) + "��" + to_string(h) + ":" + to_string(m) + ":"
		+ to_string(s);
	return t;
}

void Register()
{
	p->Register();
}

void Login()
{
	bool isLogin;
	isLogin = p->Login();
	if (isLogin) {
		if (p->username == "admin") {
			isAdmin = true;
		}
		else {
			isNormal = true;
		}
	}
}

void showRegisterLoginMenu()
{
	p->initialize();
	do {
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                                   ����Ա�û���Ϊadmin��Ĭ������Ϊadmin" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		cout << endl;
		cout << "                                   1.ע���˺�" << endl;
		cout << "                                   2.��½�˺�" << endl;
		cout << "                                   3.�˳�" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		char command;
		cin >> command;
		switch (command)
		{
		case '1':
			system("cls");
			Register();
			break;
		case '2':
			system("cls");
			Login();
			break;
		case '3':
			cout << "��л��ʹ�ñ�ϵͳ��" << endl;
			exit(1);
			system("pause");
			break;
		default:
			cout << "��������ȷ�����֣�" << endl;
			break;
		}
	} while (!(isAdmin||isNormal));
}

void userManage()
{
	if (isNormal) {
		bool normalFlag = true;
		do 
		{
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                                   ���ã�" << p->username << "!" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		cout << "                                   1.�޸�����" << endl;
		cout << "                                   2.����" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		char command;
		cin >> command;
		switch (command) {
		case '1': {
			system("cls");
			p->passwordModify();
			break;
		}
		case '2': {
			system("cls");
			normalFlag = false;
			break;
		}
		default:
			cout << "��������ȷ�����֣�" << endl;
			system("cls");
			system("pause");
			break;
		}
		} while (normalFlag);
	}
	else {
		bool adminFlag = true;
		do 
		{
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                                   ���ã�����Ա!" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		cout << "                                   1.�޸�����" << endl;
		cout << "                                   2.��ʾ�����û��������빺Ʊ����" << endl;
		cout << "                                   3.ɾ���û�" << endl;
		cout << "                                   4.����" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		char command;
		cin >> command;
		switch (command) {
		case '1': {
			system("cls");
			p->passwordModify();
			break;
		}
		case '2': {
			system("cls");
			cout << "�û���" << "\t����" << "\t��Ʊ����" << endl;
			ifstream alluser("users.txt");
			string readLine;
			while (!alluser.eof()) {
				getline(alluser, readLine);
				if (readLine[0] == '\0') {
					continue;
				}
				else {
					cout << readLine << endl;
				}
			}
			break;
		}
		case '3': {
			system("cls");
			p->deleteUser();
			break;
		}
		case '4': {
			system("cls");
			system("pause");
			adminFlag = false;
			break;
		}
		default:
			cout << "��������ȷ�����֣�" << endl;
			system("pause");
			system("cls");
			break;
		}
		} while (adminFlag);
	}
}

void ticketInfoManage()
{
	if (isNormal) {
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                                   ���ã�" << p->username << "!" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		cout << "                                   ��Ǹ������Ҫʹ�ù���ԱȨ�޷��ʴ˽��棡" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		system("pause");
	}
	else {
		bool flag = true;
		do 
		{
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                                   ���ã�����Ա!" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		cout << "                                   1.¼�복Ʊ��Ϣ" << endl;
		cout << "                                   2.��ʾ��Ʊ��Ϣ" << endl;
		cout << "                                   3.�޸ĳ�Ʊ��Ϣ" << endl;
		cout << "                                   4.ɾ����Ʊ��Ϣ" << endl;
		cout << "                                   5.����" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		char command;
		cin >> command;
		switch (command) {
		case '1': {
			system("cls");
			p->insert();
			break;
		}
		case '2': {
			system("cls");
			cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << "\t��Ʊ����" << "\t��Ʊ������" << endl;
			ifstream alltickets("tickets.txt");
			string readLine;
			while (!alltickets.eof()) {
				getline(alltickets, readLine);
				if (readLine[0] == '\0') {
					continue;
				}
				else {
					cout << readLine << endl;
				}
			}
			break;
		}
		case '3': {
			system("cls");
			p->modify();
			break;
		}
		case '4': {
			system("cls");
			p->erase();
			break;
		}
		case '5': {
			system("cls");
			flag = false;
			system("pause");
			break;
		}
		default:
			cout << "��������ȷ�����֣�" << endl;
			system("pause");
			system("cls");
			break;
		}
		} while (flag);
	}
}

void searchTicketInfo()
{
	bool searchFlag = true;
	do
	{
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		if (isNormal) {
			cout << "                                   ���ã�" << p->username << "!" << endl;
		}
		else {
			cout << "                                   ���ã�����Ա��" << endl;
		}
		cout << endl;
		cout << "                                   1.���ݳ�������" << endl;
		cout << "                                   2.����ʼ��������" << endl;
		cout << "                                   3.����Ŀ�ĵ�����" << endl;
		cout << "                                   4.���ݳ�Ʊ��������" << endl;
		cout << "                                   5.����" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		char command;
		cin >> command;
		switch (command) {
		case '1': {
			system("cls");
			p->searchByTrain();
			break;
		}
		case '2': {
			system("cls");
			p->searchByOrigin();
			break;
		}
		case '3': {
			system("cls");
			p->searchByDestination();
			break;
		}
		case '4': {
			system("cls");
			p->searchByTickets();
			break;
		}
		case '5': {
			system("pause");
			system("cls");
			searchFlag = false;
			break;
		}
		default:
			cout << "��������ȷ�����֣�" << endl;
			system("pause");
			system("cls");
			break;
		}
	} while (searchFlag);
}

void buyAndRefundTicket()
{
	if (isAdmin) {
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
		cout << "                                   ���ã�����Ա!" << endl;
		cout << "                             ����ʱ�䣺" << showTime() << endl;
		cout << "                                   ��Ǹ������Ҫʹ����ͨ�û�Ȩ�޷��ʴ˽��棡" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		system("pause");
	}
	else {
		bool buyFlag = true;
		do 
		{
			cout << setfill('=') << setw(100) << "=" << endl;
			cout << "                                ��ӭ���ʻ�Ʊ��Ʊϵͳ��" << endl;
			cout << "                                   ���ã�" << p->username << "!" << endl;
			cout << "                             ����ʱ�䣺" << showTime() << endl;
			cout << "                                   1.��ʾ��Ʊ��Ϣ" << endl;
			cout << "                                   2.��Ʊ" << endl;
			cout << "                                   3.��Ʊ" << endl;
			cout << "                                   4.��ѯ�ѹ���Ʊ" << endl;
			cout << "                                   5.����" << endl;
			cout << setfill('=') << setw(100) << "=" << endl;
			char command;
			cin >> command;
			switch (command)
			{
			case '1': {
				system("cls");
				cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << "\t��Ʊ����" << "\t��Ʊ������" << endl;
				ifstream alltickets("tickets.txt");
				string readLine;
				while (!alltickets.eof()) {
					getline(alltickets, readLine);
					if (readLine[0] == '\0') {
						continue;
					}
					else {
						cout << readLine << endl;
					}
				}
				break;
			}
			case '2': {
				system("cls");
				p->buy();
				break;
			}
			case '3': {
				system("cls");
				p->refund();
				break;
			}
			case '4': {
				system("cls");
				p->showBuyTicket();
				break;
			}
			case '5': {
				system("pause");
				system("cls");
				buyFlag = false;
				//system("cls");
				break;
			}
			default:
				cout << "��������ȷ�����֣�" << endl;
				system("pause");
				system("cls");
				break;
			}
		} while (buyFlag);
	}
}