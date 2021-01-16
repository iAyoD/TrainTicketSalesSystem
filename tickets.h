#pragma once
#include<string>

using namespace std;

class Ticket {
public:
	string number;
	string origin;
	string destination;
	string startTime;
	string endTime;
	int tickets;
	int ticketsSale;
	Ticket(string a, string b, string c, string d, string e, int f, int g = 0) :
		number(a), origin(b), destination(c), startTime(d), endTime(e), tickets(f), ticketsSale(g) {}
};