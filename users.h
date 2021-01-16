#pragma once
#include<string>
#include<vector>

using namespace std;

class User
{
public:
	string username;
	string password;
	int tickets;

	User(string a = "\0", string b = "\0", int c = 0):username(a), password(b), tickets(c) {}
	void searchByTrain();
	void searchByOrigin();
	void searchByDestination();
	void searchByTickets();
	void loadTickets();
	void loadUsers();
	void loadBuyTickets();
	void Register();
	bool Login();
	void initialize();
	void passwordModify();
	void insert();
	void modify();
	void erase();
	void deleteUser();
	void buy();
	void refund();
	void showBuyTicket();
	void calSaleNumByTrain();
	void calRemainNumByTrain();
	void insertTickets();
	void exportTickets();
};

class Normal :public User {
public:
	Normal(string a = "\0", string b = "\0", int c = 0) : User(a, b, c) {}
	~Normal() {}
};

class Admin :public User {
public:
	Admin(string a = "admin", string b = "admin", int c = 0): User(a, b, c) {}
	~Admin() {}
};