#pragma once
using namespace std;
#include <iostream>

class Book
{
private:
	string Title, Author, Category, Reader, ISBN, Reserve;
	int ID, Borrow, Expire, Copies;
	string availability;
	Book* next;
	Book* prev;

public:
	Book();
	Book(string Title, string Author, string Category,
		string Reader, string ISBN, int ID, int Borrow, string Reserve, int Expire, string availability, int copies);
	void setNext(Book* next);
	void setPrev(Book* prev);
	Book* getNext();
	Book* getPrev();
	string getTitle();
	string getAuthor();
	string getCategory();
	string getReader();
	string getISBN();
	int getCopies();
	void setCopies(int copies);
	void setReader(string name);
	void setAvailability(string availability);
	int getID();
	int getBorrow();
	string getReserve();
	int getExpire();
	string getavailability();
	void print();
	void setReserve(string Reserve);
	void setExpire(int Expire);
	void setBorrow(int Borrow);
};

