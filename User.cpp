#include "User.h"

User::User() {}
User::User(string Username, string password, string Type)
{
	this->UserName = Username;
	this->Password = password;
	this->Type = Type;
}

User* User::getNext()
{
	return next;
}

User* User::getPrev()
{
	return prev;
}

void User::setNext(User* next)
{
	this->next = next;
}

void User::setPrev(User* prev)
{
	this->prev = prev;
}

string User::getUsername() {
	return UserName;
}

string User::getPassword() {
	return Password;
}

string User::getType() {
	return Type;
}
