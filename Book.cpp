#include "Book.h"
#include <iostream>
#include<iomanip>
using namespace std;

Book::Book() {}
Book::Book(string Title, string Author, string Category,
	string Reader, string ISBN, int ID, int Borrow, string Reserve, int Expire, string  availability, int copies)
{
	this->Title = Title;
	this->Author = Author;
	this->Category = Category;
	this->Reader = Reader;
	this->ISBN = ISBN;
	this->ID = ID;
	this->Borrow = Borrow;
	this->Reserve = Reserve;
	this->Expire = Expire;
	this->availability = availability;
	this->Copies = copies;
}

string Book::getTitle() {
	return Title;
}

string Book::getAuthor() {
	return Author;
}

string Book::getCategory() {
	return Category;
}

string Book::getReader() {
	return Reader;
}

string Book::getISBN() {
	return ISBN;
}

int Book::getID() {
	return ID;
}

int Book::getBorrow() {
	return Borrow;
}

string Book::getReserve() {
	return Reserve;
}

int Book::getExpire() {
	return Expire;
}

int Book::getCopies() {
	return Copies;
}

string Book::getavailability()
{
	return availability;
}

void Book::setNext(Book* next)
{
	this->next = next;
}

void Book::setPrev(Book* prev)
{
	this->prev = prev;
}

void Book::setReader(string Reader)
{
	this->Reader = Reader;
}

void Book::setReserve(string Reserve)
{
	this->Reserve = Reserve;
}

void Book::setExpire(int Expire)
{
	this->Expire = Expire;
}

void Book::setBorrow(int Borrow)
{
	this->Borrow = Borrow;
}

void Book::setCopies(int copies)
{
	this->Copies = copies;
}

Book* Book::getNext()
{
	return next;
}

Book* Book::getPrev()
{
	return prev;
}

void Book::print()
{
	cout << setw(20) << left << Title << setw(20) << left << Author;
	cout << setw(20) << left << Category << setw(20) << left << Reader << setw(20) << left << ID << setw(20) << left << availability << setw(20) << left << Reserve;
	cout << setw(20) << left << Copies << endl;
}

void Book::setAvailability(string availability)
{
	this->availability = availability;
}
