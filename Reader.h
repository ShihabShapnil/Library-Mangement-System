#pragma once
#include<iostream>
#include "Book.h"
#include "User.h"
using namespace std;

class Reader {
private:
	typedef Book* Bookptr;
	typedef User* Userptr;
	Userptr Uhead, Utail, Ucurrent;//two different pointers to be able to load and search through the library and user info in
	Bookptr head, tail, current;   // Student.txt file and Library.txt file
	string username, password;
public:
	Reader();
	void addUsers(User* User);//used to load user log in info from Student.txt into program
	void loadAll();//functions loads the default library data into program
	void addLibrary(Book* Book);//used to add all books from Library.txt into program
	void moveToNext();
	void movetoUNext();
	User* getUcurrent();
	void moveToHead();
	void moveToUhead();
	void borrowBooks(int ID);
	void returnBooks(int ID, string username);
	Book* getCurrent();
	string getUsername();
	string getRtype(string username);
	string getPassword();
	void setUsername(string username);
	void AddBook();
	void AddUser();
	void DeleteBook();
	void DeleteUser();
	void Myinformation(string username);
	void reservebook(int ID, string username);
	void cancelreserve(int ID, string username);
	void renew(int ID, string username);
	void setPassword(string password);
	bool Login(string Username, string password);
	bool checkforFullStudent(string username);
	bool checkforLateStudent(string username);
	bool checkforFullTeacher(string username);
	bool checkforLateTeacher(string username);
	void SearchbyISBN();
	void SearchbyID();
	void SearchbyTitle();
	void SearchbyAuthor();
	void SearchbyCategory();
	void SearchUsers();
};


