#pragma once
using namespace std;
#include <iostream>

class User
{
private:
	string UserName, Password, Type;
	User* next;
	User* prev;

public:
	User();
	User(string UserName, string Password, string Type);
	void setNext(User* next);
	void setPrev(User* prev);
	User* getNext();
	User* getPrev();
	string getUsername();
	string getPassword();
	string getType();
};
