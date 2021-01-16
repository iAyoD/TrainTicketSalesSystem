#pragma once
#include "users.h"
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<vector>
#include"tickets.h"
#include "userticket.h"

using namespace std;

vector<Ticket> allTickets;
vector<User> allUsers;
vector<Buyticket> allBuyTickets;

void User::loadBuyTickets()
{
	ifstream loadbuytickets("buytickets.txt");
	string nameuser;
	string numbertrain;
	while (!loadbuytickets.eof()) {
		loadbuytickets >> nameuser >> numbertrain;
		Buyticket a(nameuser, numbertrain);
		allBuyTickets.push_back(a);
	}
	loadbuytickets.close();
}

void User::loadUsers()
{
	ifstream loaduser("users.txt");
	string username;
	string password;
	int ticket;
	while (!loaduser.eof()) {
		loaduser >> username >> password >> ticket;
		User a(username, password, ticket);
		allUsers.push_back(a);
	}
	loaduser.close();
}

void User::loadTickets()
{
	ifstream loadticket("tickets.txt");
	string number;
	string origin;
	string destination;
	string startTime;
	string endTime;
	int tickets;
	int ticketsSales;
	while (!loadticket.eof()) {
		loadticket >> number >> origin >> destination >> startTime >> endTime >> tickets >> ticketsSales;
		Ticket a(number, origin, destination, startTime, endTime, tickets, ticketsSales);
		allTickets.push_back(a);
	}
	loadticket.close();
}

void User::initialize()
{
	loadUsers();
	bool isAdminExist = false;
	ofstream ouser;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == "admin") {
			isAdminExist = true;
			break;
		}
	}
	if (!isAdminExist) {
		ouser.open("users.txt", ios::app);
		ouser << "admin" << "\t" << "admin" << "\t" << tickets << "\t" << "\n";
	}
	ouser.close();
	vector <User>().swap(allUsers);
}

void User::Register()
{
	initialize();
	loadUsers();
	string username;
	string password;
	ofstream user;
	user.open("users.txt", ios::app);
	cout << "请输入用户名：";
	cin >> username;
	bool isExist = false;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == username) {
			cout << "用户已存在，请登录！" << endl;
			isExist = true;
			break;
		}
	}
	if (!isExist) {
		cout << "请输入密码：";
		cin >> password;
		user << username << "\t" << password << "\t" << tickets << "\t" << "\n";
		cout << "注册成功！" << endl;
	}
	user.close();
	vector <User>().swap(allUsers);
}

bool User::Login()
{
	initialize();
	loadUsers();
	string thisUsername;
	string thisPassword;
	bool usernameExist = false;
	cout << "请输入用户名：";
	cin >> thisUsername;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == thisUsername) {
			usernameExist = true;
			break;
		}
	}
	if (!usernameExist) {
		cout << "用户不存在，请注册！" << endl;
		return false;
	}
	else {
		cout << "请输入密码：";
		cin >> thisPassword;
		for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
			if (i->username == thisUsername) {
				if (i->password == thisPassword) {
					username = thisUsername;
					password = thisPassword;
					cout << "登录成功！" << endl;
					return true;
				}
				else {
					cout << "密码错误，请重试！" << endl;
					return false;
				}
				break;
			}
		}
	}
	vector <User>().swap(allUsers);
}

void User::passwordModify()
{
	vector <User>().swap(allUsers);
	loadUsers();
	string originPassword;
	string modifiedPassword;
	bool modified = false;
	cout << "请输入原始密码：";
	cin >> originPassword;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == username) {
			if (i->password == originPassword) {
				cout << "请输入修改后的密码：";
				cin >> modifiedPassword;
				i->password = modifiedPassword;
				modified = true;
			}
			else {
				cout << "密码错误，请重试！" << endl;
			}
			break;
		}
	}
	if (modified) {
		ofstream ousers("users.txt");
		for (auto i = allUsers.begin(); i != allUsers.end() - 1; ++i) {
			ousers << i->username << "\t" << i->password << "\t" << i->tickets << "\t" << "\n";
		}
		cout << "修改成功！" << endl;
		ousers.close();
	}
	vector <User>().swap(allUsers);
}

void User::deleteUser()
{
	loadUsers();
	string eraseUsername;
	bool isExist = true;
	bool isadmin = false;
	do
	{
		cout << "请输入要删除的用户名：";
		cin >> eraseUsername;
		if (eraseUsername == "admin") {
			isExist = false;
			isadmin = true;
			cout << "管理员用户不可删除！" << endl;
		}
		for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
			if (i->username == eraseUsername) {
				isExist = false;
			}
		}
		if (isExist) {
			cout << "用户不存在！请重新输入！" << endl;
		}
	} while (isExist);
	vector <User>().swap(allUsers);
	loadUsers();
	if (!isadmin) {
		ofstream ousers("users.txt");
		for (auto i = allUsers.begin(); i != allUsers.end() - 1; ++i) {
			if (i->username == eraseUsername) {
				continue;
			}
			else {
				ousers << i->username << "\t" << i->password << "\t" << i->tickets << "\t" << "\n";
			}
		}
		cout << "删除成功！" << endl;
		ousers.close();
	}
	vector <User>().swap(allUsers);
}

void User::insert()
{
	string number;
	string origin;
	string destination;
	string startTime;
	string endTime;
	int tickets;
	ofstream ticket;
	ticket.open("tickets.txt", ios::app);
	cout << "请输入车次：";
	cin >> number;
	cout << "请输入始发地：";
	cin >> origin;
	cout << "请输入终点：";
	cin >> destination;
	cout << "请输入始发时间：";
	cin >> startTime;
	cout << "请输入到达时间：";
	cin >> endTime;
	cout << "请输入车票总量：";
	cin >> tickets;
	ticket << number << "\t" << origin << "\t" << destination << "\t" << startTime << "\t" << endTime << "\t" << tickets << "\t" << 0 << "\n";
	cout << "插入成功！" << endl;
	ticket.close();
}

void User::modify()
{
	loadTickets();
	string number;
	string option;
	bool o = false;
	bool d = false;
	bool st = false;
	bool et = false;
	bool t = false;
	bool numberFlag = true;
	do 
	{
	cout << "请输入要修改的车次：" << endl;
	cin >> number;
	for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
		if (i->number == number) {
			numberFlag = false;
		}
	}
	if (numberFlag) {
		cout << "未找到相应车次！请重新输入！" << endl;
	}
	} while (numberFlag);
	bool modifiedInfoFlag = true;
	do 
	{
	cout << "请输入要修改的信息（始发地/终点/始发时间/到达时间/车票总量）：";
	cin >> option;
	if (option == "始发地") {
		o = true;
		modifiedInfoFlag = false;
	}
	else if (option == "终点") {
		d = true;
		modifiedInfoFlag = false;
	}
	else if (option == "始发时间") {
		st = true;
		modifiedInfoFlag = false;
	}
	else if (option == "到达时间") {
		et = true;
		modifiedInfoFlag = false;
	}
	else if (option == "车票总量") {
		t = true;
		modifiedInfoFlag = false;
	}
	else {
		cout << "请输入正确的要修改信息！" << endl;
	}
	} while (modifiedInfoFlag);
	string sval;
	int ival;
	cout << "请输入修改后的值：";
	if (t) {
		cin >> ival;
	}
	else {
		cin >> sval;
	}
	for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
		if (i->number == number) {
			if (o) {
				i->origin = sval;
			}
			else if (d) {
				i->destination = sval;
			}
			else if (st) {
				i->startTime = sval;
			}
			else if (et) {
				i->endTime = sval;
			}
			else if (t) {
				i->tickets = ival;
			}
			break;
		}
	}
	ofstream otickets("tickets.txt");
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
	}
	cout << "修改成功！" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}

void User::erase()
{
	loadTickets();
	string number;
	bool numberFlag = true;
	do
	{
		cout << "请输入要删除的车次：" << endl;
		cin >> number;
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				numberFlag = false;
			}
		}
		if (numberFlag) {
			cout << "未找到相应车次！请重新输入！" << endl;
		}
	} while (numberFlag);
	ofstream otickets("tickets.txt");
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->number == number) {
			continue;
		}
		else {
			otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
		}
	}
	cout << "删除成功！" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}

void User::searchByTrain()
{
	loadTickets();
	string a;
	cout << "请输入要查询的车次：";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
		if (i->number == a) {
			isExist = true;
			if (first) {
				cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << "\t车票总量" << "\t车票销售量" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "未查询到相关车次信息！" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::searchByOrigin()
{
	loadTickets();
	string a;
	cout << "请输入要查询的起始地：";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->origin == a) {
			isExist = true;
			if (first) {
				cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << "\t车票总量" << "\t车票销售量" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "未查询到相关车次信息！" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::searchByDestination()
{
	loadTickets();
	string a;
	cout << "请输入要查询的目的地：";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->destination == a) {
			isExist = true;
			if (first) {
				cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << "\t车票总量" << "\t车票销售量" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "未查询到相关车次信息！" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::searchByTickets()
{
	loadTickets();
	int a;
	cout << "请输入要查询的车票余量大于等于：";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->tickets >= a) {
			isExist = true;
			if (first) {
				cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << "\t车票总量" << "\t车票销售量" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "未查询到相关车次信息！" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::buy()
{
	loadTickets();
	string number;
	bool isExist = true;
	do 
	{
		cout << "请输入要购买的车次：" << endl;
		cin >> number;
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				if (i->tickets == i->ticketsSale) {
					cout << "抱歉，车票已售罄！" << endl;
				}
				else {
					isExist = false;
					cout << "购买成功！" << endl;
					++(i->ticketsSale);
					--(i->tickets);
				}
				break;
			}
		}
		if (isExist) {
			cout << "未查询到相关车次信息！请重新输入！" << endl;
		}
	} while (isExist);
	++tickets;
	ofstream obuyTickets;
	obuyTickets.open("buytickets.txt", ios::app);
	obuyTickets << username << "\t" << number << "\t" << "\n";
	obuyTickets.close();
	ofstream otickets("tickets.txt");
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
	}
	otickets.close();
	vector <Ticket>().swap(allTickets);
}

void User::refund()
{
	loadBuyTickets();
	loadTickets();
	string trainnumber;
	bool isExist = false;
	cout << "请输入要退票的车次：";
	cin >> trainnumber;
	for (auto i = allBuyTickets.begin(); i != allBuyTickets.end(); ++i) {
		if (i->nameuser == username) {
			if (i->numbertrain == trainnumber) {
				isExist = true;
				break;
			}
		}
	}
	if (isExist) {
		ofstream obuyTickets("buytickets.txt");
		for (auto i = allBuyTickets.begin(); i != allBuyTickets.end(); ++i) {
			if (i->nameuser == username) {
				if (i->numbertrain == trainnumber) {
					continue;
				}
				else {
					obuyTickets << i->nameuser << "\t" << i->numbertrain << "\t" << "\n";
				}
			}
			else {
				obuyTickets << i->nameuser << "\t" << i->numbertrain << "\t" << "\n";
			}
		}
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == trainnumber) {
				--(i->ticketsSale);
				++(i->tickets);
				break;
			}
		}
		--tickets;
		cout << "退票成功！" << endl;
		obuyTickets.close();
	}
	else {
		cout << "您未购买该车次车票！" << endl;
	}
	ofstream otickets("tickets.txt");
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
	}
	otickets.close();
	vector <Buyticket>().swap(allBuyTickets);
	vector <Ticket>().swap(allTickets);
}

void User::showBuyTicket()
{
	loadBuyTickets();
	loadTickets();
	bool first = true;
	for (auto i = allBuyTickets.begin(); i != allBuyTickets.end()-1; ++i) {
		if (i->nameuser == username) {
			for (auto j = allTickets.begin(); j != allTickets.end()-1; ++j) {
				if (i->numbertrain == j->number) {
					if (first) {
						cout << "车次" << "\t始发地" << "\t目的地" << "\t始发时间" << "\t到达时间" << endl;
						first = false;
					}
					cout << j->number << "\t" << j->origin << "\t" << j->destination << "\t" << j->startTime << "\t" << j->endTime << endl;
				}
			}
		}
	}
	vector <Buyticket>().swap(allBuyTickets);
	vector <Ticket>().swap(allTickets);
}

void User::calSaleNumByTrain()
{
	loadTickets();
	string number;
	bool isExist = false;
	cout << "请输入要查询的车次：";
	cin >> number;
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		if (i->number == number) {
			isExist = true;
		}
	}
	if (!isExist) {
		cout << "未查询到相关车次信息！" << endl;
	}
	else {
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				cout << i->number << "车次售票数量为" << i->ticketsSale << endl;
				break;
			}
		}
	}
	vector <Ticket>().swap(allTickets);
}

void User::calRemainNumByTrain()
{
	loadTickets();
	string number;
	bool isExist = false;
	cout << "请输入要查询的车次：";
	cin >> number;
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		if (i->number == number) {
			isExist = true;
		}
	}
	if (!isExist) {
		cout << "未查询到相关车次信息！" << endl;
	}
	else {
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				cout << i->number << "车次车票余量为" << (i->tickets) - (i->ticketsSale) << endl;
				break;
			}
		}
	}
	vector <Ticket>().swap(allTickets);
}

void User::insertTickets()
{
	string filename;
	cout << "请输入导入的文件名：";
	cin >> filename;
	ifstream iticket(filename);
	string number;
	string origin;
	string destination;
	string startTime;
	string endTime;
	int tickets;
	int ticketsSales;
	while (!iticket.eof()) {
		iticket >> number >> origin >> destination >> startTime >> endTime >> tickets >> ticketsSales;
		Ticket a(number, origin, destination, startTime, endTime, tickets, ticketsSales);
		allTickets.push_back(a);
	}
	iticket.close();
	ofstream otickets;
	otickets.open("tickets.txt", ios::app);
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
	}
	cout << "导入成功！" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}

void User::exportTickets()
{
	loadTickets();
	cout << "请输入要导出的文件名：";
	string filename;
	cin >> filename;
	ofstream otickets(filename);
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
	}
	cout << "导出成功！" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}