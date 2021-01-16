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
	cout << "�������û�����";
	cin >> username;
	bool isExist = false;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == username) {
			cout << "�û��Ѵ��ڣ����¼��" << endl;
			isExist = true;
			break;
		}
	}
	if (!isExist) {
		cout << "���������룺";
		cin >> password;
		user << username << "\t" << password << "\t" << tickets << "\t" << "\n";
		cout << "ע��ɹ���" << endl;
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
	cout << "�������û�����";
	cin >> thisUsername;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == thisUsername) {
			usernameExist = true;
			break;
		}
	}
	if (!usernameExist) {
		cout << "�û������ڣ���ע�ᣡ" << endl;
		return false;
	}
	else {
		cout << "���������룺";
		cin >> thisPassword;
		for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
			if (i->username == thisUsername) {
				if (i->password == thisPassword) {
					username = thisUsername;
					password = thisPassword;
					cout << "��¼�ɹ���" << endl;
					return true;
				}
				else {
					cout << "������������ԣ�" << endl;
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
	cout << "������ԭʼ���룺";
	cin >> originPassword;
	for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
		if (i->username == username) {
			if (i->password == originPassword) {
				cout << "�������޸ĺ�����룺";
				cin >> modifiedPassword;
				i->password = modifiedPassword;
				modified = true;
			}
			else {
				cout << "������������ԣ�" << endl;
			}
			break;
		}
	}
	if (modified) {
		ofstream ousers("users.txt");
		for (auto i = allUsers.begin(); i != allUsers.end() - 1; ++i) {
			ousers << i->username << "\t" << i->password << "\t" << i->tickets << "\t" << "\n";
		}
		cout << "�޸ĳɹ���" << endl;
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
		cout << "������Ҫɾ�����û�����";
		cin >> eraseUsername;
		if (eraseUsername == "admin") {
			isExist = false;
			isadmin = true;
			cout << "����Ա�û�����ɾ����" << endl;
		}
		for (auto i = allUsers.begin(); i != allUsers.end(); ++i) {
			if (i->username == eraseUsername) {
				isExist = false;
			}
		}
		if (isExist) {
			cout << "�û������ڣ����������룡" << endl;
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
		cout << "ɾ���ɹ���" << endl;
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
	cout << "�����복�Σ�";
	cin >> number;
	cout << "������ʼ���أ�";
	cin >> origin;
	cout << "�������յ㣺";
	cin >> destination;
	cout << "������ʼ��ʱ�䣺";
	cin >> startTime;
	cout << "�����뵽��ʱ�䣺";
	cin >> endTime;
	cout << "�����복Ʊ������";
	cin >> tickets;
	ticket << number << "\t" << origin << "\t" << destination << "\t" << startTime << "\t" << endTime << "\t" << tickets << "\t" << 0 << "\n";
	cout << "����ɹ���" << endl;
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
	cout << "������Ҫ�޸ĵĳ��Σ�" << endl;
	cin >> number;
	for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
		if (i->number == number) {
			numberFlag = false;
		}
	}
	if (numberFlag) {
		cout << "δ�ҵ���Ӧ���Σ����������룡" << endl;
	}
	} while (numberFlag);
	bool modifiedInfoFlag = true;
	do 
	{
	cout << "������Ҫ�޸ĵ���Ϣ��ʼ����/�յ�/ʼ��ʱ��/����ʱ��/��Ʊ��������";
	cin >> option;
	if (option == "ʼ����") {
		o = true;
		modifiedInfoFlag = false;
	}
	else if (option == "�յ�") {
		d = true;
		modifiedInfoFlag = false;
	}
	else if (option == "ʼ��ʱ��") {
		st = true;
		modifiedInfoFlag = false;
	}
	else if (option == "����ʱ��") {
		et = true;
		modifiedInfoFlag = false;
	}
	else if (option == "��Ʊ����") {
		t = true;
		modifiedInfoFlag = false;
	}
	else {
		cout << "��������ȷ��Ҫ�޸���Ϣ��" << endl;
	}
	} while (modifiedInfoFlag);
	string sval;
	int ival;
	cout << "�������޸ĺ��ֵ��";
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
	cout << "�޸ĳɹ���" << endl;
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
		cout << "������Ҫɾ���ĳ��Σ�" << endl;
		cin >> number;
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				numberFlag = false;
			}
		}
		if (numberFlag) {
			cout << "δ�ҵ���Ӧ���Σ����������룡" << endl;
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
	cout << "ɾ���ɹ���" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}

void User::searchByTrain()
{
	loadTickets();
	string a;
	cout << "������Ҫ��ѯ�ĳ��Σ�";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
		if (i->number == a) {
			isExist = true;
			if (first) {
				cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << "\t��Ʊ����" << "\t��Ʊ������" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "δ��ѯ����س�����Ϣ��" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::searchByOrigin()
{
	loadTickets();
	string a;
	cout << "������Ҫ��ѯ����ʼ�أ�";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->origin == a) {
			isExist = true;
			if (first) {
				cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << "\t��Ʊ����" << "\t��Ʊ������" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "δ��ѯ����س�����Ϣ��" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::searchByDestination()
{
	loadTickets();
	string a;
	cout << "������Ҫ��ѯ��Ŀ�ĵأ�";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->destination == a) {
			isExist = true;
			if (first) {
				cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << "\t��Ʊ����" << "\t��Ʊ������" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "δ��ѯ����س�����Ϣ��" << endl;
	}
	vector <Ticket>().swap(allTickets);
}

void User::searchByTickets()
{
	loadTickets();
	int a;
	cout << "������Ҫ��ѯ�ĳ�Ʊ�������ڵ��ڣ�";
	cin >> a;
	bool isExist = false;
	bool first = true;
	for (auto i = allTickets.begin(); i != allTickets.end()-1; ++i) {
		if (i->tickets >= a) {
			isExist = true;
			if (first) {
				cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << "\t��Ʊ����" << "\t��Ʊ������" << endl;
				first = false;
			}
			cout << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << endl;
		}
	}
	if (!isExist) {
		cout << "δ��ѯ����س�����Ϣ��" << endl;
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
		cout << "������Ҫ����ĳ��Σ�" << endl;
		cin >> number;
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				if (i->tickets == i->ticketsSale) {
					cout << "��Ǹ����Ʊ��������" << endl;
				}
				else {
					isExist = false;
					cout << "����ɹ���" << endl;
					++(i->ticketsSale);
					--(i->tickets);
				}
				break;
			}
		}
		if (isExist) {
			cout << "δ��ѯ����س�����Ϣ�����������룡" << endl;
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
	cout << "������Ҫ��Ʊ�ĳ��Σ�";
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
		cout << "��Ʊ�ɹ���" << endl;
		obuyTickets.close();
	}
	else {
		cout << "��δ����ó��γ�Ʊ��" << endl;
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
						cout << "����" << "\tʼ����" << "\tĿ�ĵ�" << "\tʼ��ʱ��" << "\t����ʱ��" << endl;
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
	cout << "������Ҫ��ѯ�ĳ��Σ�";
	cin >> number;
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		if (i->number == number) {
			isExist = true;
		}
	}
	if (!isExist) {
		cout << "δ��ѯ����س�����Ϣ��" << endl;
	}
	else {
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				cout << i->number << "������Ʊ����Ϊ" << i->ticketsSale << endl;
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
	cout << "������Ҫ��ѯ�ĳ��Σ�";
	cin >> number;
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		if (i->number == number) {
			isExist = true;
		}
	}
	if (!isExist) {
		cout << "δ��ѯ����س�����Ϣ��" << endl;
	}
	else {
		for (auto i = allTickets.begin(); i != allTickets.end(); ++i) {
			if (i->number == number) {
				cout << i->number << "���γ�Ʊ����Ϊ" << (i->tickets) - (i->ticketsSale) << endl;
				break;
			}
		}
	}
	vector <Ticket>().swap(allTickets);
}

void User::insertTickets()
{
	string filename;
	cout << "�����뵼����ļ�����";
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
	cout << "����ɹ���" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}

void User::exportTickets()
{
	loadTickets();
	cout << "������Ҫ�������ļ�����";
	string filename;
	cin >> filename;
	ofstream otickets(filename);
	for (auto i = allTickets.begin(); i != allTickets.end() - 1; ++i) {
		otickets << i->number << "\t" << i->origin << "\t" << i->destination << "\t" << i->startTime << "\t" << i->endTime << "\t" << i->tickets << "\t" << i->ticketsSale << "\n";
	}
	cout << "�����ɹ���" << endl;
	otickets.close();
	vector <Ticket>().swap(allTickets);
}