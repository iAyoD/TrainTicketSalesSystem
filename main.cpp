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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		if (isNormal) {
			cout << "                                   您好，" << p->username << "!" << endl;
		}
		else {
			cout << "                                   您好，管理员！" << endl;
		}
		cout << endl;
		cout << "                                   1.用户管理" << endl;
		cout << "                                   2.车票信息管理" << endl;
		cout << "                                   3.根据条件查找车票信息" << endl;
		cout << "                                   4.购票与退票服务" << endl;
		cout << "                                   5.按车次统计售票数量" << endl;
		cout << "                                   6.按车次查询车票余量" << endl;
		cout << "                                   7.导入车票信息" << endl;
		cout << "                                   8.导出车票信息" << endl;
		cout << "                                   9.退出登录" << endl;
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
				cout << "                                欢迎访问火车票售票系统！" << endl;
				cout << "                                   您好，" << p->username << "!" << endl;
				cout << "                             现在时间：" << showTime() << endl;
				cout << "                                   抱歉！您需要使用管理员权限访问此界面！" << endl;
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
				cout << "                                欢迎访问火车票售票系统！" << endl;
				cout << "                                   您好，" << p->username << "!" << endl;
				cout << "                             现在时间：" << showTime() << endl;
				cout << "                                   抱歉！您需要使用管理员权限访问此界面！" << endl;
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
			cout << "请输入正确的数字！" << endl;
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
	t = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日" + to_string(h) + ":" + to_string(m) + ":"
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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                                   管理员用户名为admin，默认密码为admin" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		cout << endl;
		cout << "                                   1.注册账号" << endl;
		cout << "                                   2.登陆账号" << endl;
		cout << "                                   3.退出" << endl;
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
			cout << "感谢您使用本系统！" << endl;
			exit(1);
			system("pause");
			break;
		default:
			cout << "请输入正确的数字！" << endl;
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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                                   您好，" << p->username << "!" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		cout << "                                   1.修改密码" << endl;
		cout << "                                   2.返回" << endl;
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
			cout << "请输入正确的数字！" << endl;
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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                                   您好，管理员!" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		cout << "                                   1.修改密码" << endl;
		cout << "                                   2.显示所有用户、密码与购票数量" << endl;
		cout << "                                   3.删除用户" << endl;
		cout << "                                   4.返回" << endl;
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
			cout << "用户名" << "\t密码" << "\t购票数量" << endl;
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
			cout << "请输入正确的数字！" << endl;
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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                                   您好，" << p->username << "!" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		cout << "                                   抱歉！您需要使用管理员权限访问此界面！" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		system("pause");
	}
	else {
		bool flag = true;
		do 
		{
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                                   您好，管理员!" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		cout << "                                   1.录入车票信息" << endl;
		cout << "                                   2.显示车票信息" << endl;
		cout << "                                   3.修改车票信息" << endl;
		cout << "                                   4.删除车票信息" << endl;
		cout << "                                   5.返回" << endl;
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
			cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << "\t车票余量" << "\t车票销售量" << endl;
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
			cout << "请输入正确的数字！" << endl;
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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		if (isNormal) {
			cout << "                                   您好，" << p->username << "!" << endl;
		}
		else {
			cout << "                                   您好，管理员！" << endl;
		}
		cout << endl;
		cout << "                                   1.根据车次搜索" << endl;
		cout << "                                   2.根据始发地搜索" << endl;
		cout << "                                   3.根据目的地搜索" << endl;
		cout << "                                   4.根据车票余量搜索" << endl;
		cout << "                                   5.返回" << endl;
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
			cout << "请输入正确的数字！" << endl;
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
		cout << "                                欢迎访问火车票售票系统！" << endl;
		cout << "                                   您好，管理员!" << endl;
		cout << "                             现在时间：" << showTime() << endl;
		cout << "                                   抱歉！您需要使用普通用户权限访问此界面！" << endl;
		cout << setfill('=') << setw(100) << "=" << endl;
		system("pause");
	}
	else {
		bool buyFlag = true;
		do 
		{
			cout << setfill('=') << setw(100) << "=" << endl;
			cout << "                                欢迎访问火车票售票系统！" << endl;
			cout << "                                   您好，" << p->username << "!" << endl;
			cout << "                             现在时间：" << showTime() << endl;
			cout << "                                   1.显示车票信息" << endl;
			cout << "                                   2.购票" << endl;
			cout << "                                   3.退票" << endl;
			cout << "                                   4.查询已购买车票" << endl;
			cout << "                                   5.返回" << endl;
			cout << setfill('=') << setw(100) << "=" << endl;
			char command;
			cin >> command;
			switch (command)
			{
			case '1': {
				system("cls");
				cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << "\t车票余量" << "\t车票销售量" << endl;
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
				cout << "请输入正确的数字！" << endl;
				system("pause");
				system("cls");
				break;
			}
		} while (buyFlag);
	}
}