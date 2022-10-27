#include "Reader.h"
#include "Book.h"
#include <fstream>
#include <iostream>
#include"DateCounter.h"

Datecounter date;//needed to call getDate() function

Reader::Reader() {
	head = NULL;
	current = NULL;
	tail = NULL;
	Uhead = NULL;
	Ucurrent = NULL;
	Utail = NULL;
}

void Reader::borrowBooks(int ID) {

	moveToHead();//resets pointer so it starts search from the top
	while (current->getID() != ID)//will keep moving down the library list until it finds a mtach or reaches the end
	{
		if (current->getNext() == NULL)//breaks out of loop once it reaches the last book on the library list
			break;
		current = current->getNext();//moving to next until it matches the ID
	}
	if (current->getavailability() == "AVAILABLE")//checks availablity before it lets you borrow the book
	{
		if (current->getID() == ID)//checks again to see if ID entered in search matches ID of the book
		{
			cout << "\nResults" << endl << endl;
			current->print();
			current->setReader(Ucurrent->getUsername());//changed reader of the book to username of the current user
			current->setAvailability("NOT AVAILABLE");//changes so book is no longer available
			cout << endl << "Book borrowed\n" << endl << endl;
			current->setBorrow(date.getDate());//gets the date and sets it in borrow date
			current->print();
			cout << "Borrowed at:" << endl << endl;
			cout << "Day " << current->getBorrow() << endl << endl;
			current->setExpire(current->getBorrow() + 30);//expire date is 30 days after the date it was borrowed
			cout << "Please Return by" << endl << endl;
			cout << "Day " << current->getBorrow() + 30 << endl;

		}
		else
			cout << "No results" << endl;
	}
	else
		cout << "Sorry this Book is Taken" << endl;
	moveToHead();//resets pointer again just in case

}

void Reader::reservebook(int ID, string username) {

	moveToHead();//resets pointer so it starts search from the top
	while (current->getID() != ID)//will keep moving down the library list until it finds a mtach or reaches the end
	{
		if (current->getNext() == NULL)//breaks out of loop once it reaches the last book on the library list
			break;
		current = current->getNext();//moving to next until it matches the ID
	}
	if (current->getReader() != "NONE")//if the book is taken you can reserve it
	{
		if (current->getReader() != username)
		{
			if (current->getReserve() == "0")
			{
				if (current->getID() == ID)//checks again to see if ID entered in search matches ID of the book
				{
					cout << "\nResults" << endl << endl;
					current->print();
					current->setReserve(Ucurrent->getUsername());//put the username of seracher into reserve category
					cout << endl << "Book Reserved\n" << endl << endl;
					current->print();
				}
				else
					cout << "No results" << endl;
			}
			else
				cout << "Sorry this book has already been reserved" << endl;
		}
		else
			cout << "You already own this book" << endl;

	}
	else
		cout << "This Book is available, you can Borrow it instead of reserving" << endl;
	moveToHead();//resets pointer again just in case

}


void Reader::returnBooks(int ID, string username) {

	moveToHead();//resets pointer
	do//do while loop so it checks if its the last item in the library AFTER it has checked if 
	{ //it is the book the user wants to return
		if (current->getReader() == username)//checks if the reader of the book is the same as the person who wants to return the book
		{
			if (current->getID() == ID)//checks if ID of book matches ID of the book that needs to be returned
			{
				current->print();
				current->setAvailability("AVAILABLE");//make book available again
				current->setReader("NONE");//set the reader to no one
				current->setBorrow(0);//reset borrow and expiration date
				current->setExpire(0);
				cout << "Book Returned" << endl;
				current->print();
				return;//if it has returned the book, return because function operation is done
			}
		}
		current = current->getNext();
	} while (current != tail);//do this until it reaches the last item on the list
	cout << "You have not checked out any Books with that ID number" << endl;//if it gets to this point it is becasue there is no result
}

void Reader::moveToNext()
{
	if (current->getNext() != NULL)
	{
		current = current->getNext();
	}
}

void Reader::movetoUNext()
{
	if (Ucurrent->getNext() != NULL)
	{
		Ucurrent = Ucurrent->getNext();
		cout << "Moved" << endl;
	}
	else
		cout << "There's no Book next to it!" << endl;
}

void Reader::addLibrary(Book* Book)
{
	if (head == NULL)
		head = current = tail = Book;
	else
	{
		tail->setNext(Book);//--> SETS NEXT
		tail->getNext()->setPrev(tail);//gets next book, then SETS PREV to the current tail
		tail = tail->getNext();//MOVES TAIL
	}

}

void Reader::addUsers(User* User)
{
	if (Uhead == NULL)
		Uhead = Ucurrent = Utail = User;
	else
	{
		Utail->setNext(User);//--> SETS NEXT
		Utail->getNext()->setPrev(Utail);//gets next book, then SETS PREV to the current tail
		Utail = Utail->getNext();//MOVES TAIL
	}

}

void Reader::AddBook()
{
	string Title, Author, Category, Reader, ISBN, Username, Password, Type, Reserve;
	int ID, Borrow, Copies, Expire;
	string availability;
	cout << "Enter the information of the book you want to add in the following order" << endl;
	cout << "Title, Author, Category, ISBN, ID" << endl;
	cin >> Title >> Author >> Category >> ISBN >> ID;
	addLibrary(new Book(Title, Author, Category, "NONE", ISBN, ID, 0, "0", 0, "AVAILABLE", 5));
	tail->print();//output new book

}

void Reader::AddUser()
{
	string username, password, type;
	cout << "Enter the information of the new user in the following order(type must be in all caps)" << endl;
	cout << "Username, Password, Type(STUDENT, LIBRARIAN, TEACHER)" << endl;
	cin >> username >> password >> type;
	addUsers(new User(username, password, type));
	cout << Utail->getUsername() << "  " << Utail->getPassword() << "   " << Utail->getType();//output new user

}

void Reader::DeleteBook()
{
	int ID;
	cout << "Type the ID of the Book to delete: " << endl;
	cin >> ID;
	moveToHead();//resets pointer so it starts search from the top
	while (current->getID() != ID)//will keep moving down the library list until it finds a mtach or reaches the end
	{
		if (current->getNext() == NULL)//breaks out of loop once it reaches the last book on the library list
			break;
		current = current->getNext();//moving to next until it matches the ID
	}
	if (current->getID() == ID) {
		if (current->getReader() == "NONE")//if the book is not taken you can delete it
		{
			if (current == head)
			{
				Book* temp = head; //creating a temporary node
				head = head->getNext(); //deleting the original head by setting head to the next node
				current = head;//setting current to head
				if (temp->getReserve() != "0")//Removing reservations
					temp->setReserve("0");
				delete temp; //
			}
			else
			{
				Book* prevtemp = current->getPrev();//creating a temporary variable that is set to the node before the one to be deleted
				current = current->getNext();//setting the current to the next node
				if (prevtemp != NULL)
					current->setPrev(prevtemp);//setting the previous pointer of current to the node before the node to be deleted
				if (current != NULL)
					prevtemp->setNext(current); //setting the next pointer of the temporary variable to current
			}
		}
		else
			cout << "The Book is loaned out. You cannot delete it." << endl; //A User has the book so it can not be deleted
	}
	else
	{
		cout << "There is no Book with that ID." << endl;
	}
}

void Reader::DeleteUser()
{
	string Username;
	cout << "Type the Username of the User to delete: " << endl;
	cin >> Username;
	moveToHead();//resets pointer so it starts search from the top
	moveToUhead();
	while (Ucurrent->getUsername() != Username)//will keep moving down the user list until it finds a match or reaches the end
	{
		if (Ucurrent->getNext() == NULL)//breaks out of loop once it reaches the last user on the library list
			break;
		Ucurrent = Ucurrent->getNext();//moving to next until it matches the username
	}
	while (current->getReader() != Username)//will keep moving down the library list until it finds a mtach or reaches the end
	{
		if (current->getNext() == NULL)//breaks out of loop once it reaches the last book on the library list
			break;
		current = current->getNext();//moving to next until it matches the username
	}
	Book* reserve = head;
	while (reserve->getReserve() != Username)//will keep moving down the library list until it finds a mtach or reaches the end
	{
		if (reserve->getNext() == NULL)//breaks out of loop once it reaches the last book on the library list
			break;
		reserve = reserve->getNext();//moving to next until it matches the username
	}
	if (Ucurrent->getUsername() == Username)
	{
		if (current->getReader() != Username)//if the book is not taken you can delete it
		{
			if (Ucurrent == Uhead)
			{
				User* temp = Uhead; //creating a temporary node
				Uhead = Uhead->getNext(); //deleting the original head by setting head to the next node
				Ucurrent = Uhead; //setting current to head
				if (reserve->getReserve() == Username) //Removing reservations
					reserve->setReserve("0");
				delete temp;
			}
			else
			{
				User* prevtemp = Ucurrent->getPrev(); //creating a temporary variable that is set to the node before the one to be deleted
				Ucurrent = Ucurrent->getNext(); //setting the current to the next node
				if (prevtemp != NULL)
					Ucurrent->setPrev(prevtemp); //setting the previous pointer of current to the node before the node to be deleted
				if (Ucurrent != NULL)
					prevtemp->setNext(Ucurrent); //setting the next pointer of the temporary variable to current
			}
		}
		else
			cout << "The User has been loaned out a book. You cannot delete them." << endl;
	}
	else
	{
		cout << "There is no User with that Username." << endl;
	}
}


void Reader::loadAll() {
	ifstream MyFile, MySFile;
	string Title, Author, Category, Reader, ISBN, Username, Password, Type, Reserve;
	int ID, Borrow, Copies, Expire;
	string availability;

	MyFile.open("Library.txt");
	if (MyFile.fail())
	{
		cerr << "Error Opening Library File" << endl;
		exit(1);
	}
	while (!MyFile.eof())
	{
		MyFile >> Title >> Author >> Category >> Reader >> ISBN >> ID >> Borrow >> Reserve >> Expire >> availability >> Copies;
		addLibrary(new Book(Title, Author, Category, Reader, ISBN, ID, Borrow, Reserve, Expire, availability, Copies));
		current->print();//outputs all available library books for user facilitation
		moveToNext();
	}
	cout << "\nLibrary has been loaded\n" << endl;

	MySFile.open("Student.txt");
	if (MySFile.fail()) {
		cerr << "Error Opening Student File" << endl;
		exit(1);
	}
	while (!MySFile.eof()) {
		MySFile >> Username >> Password >> Type;
		addUsers(new User(Username, Password, Type));
	}
	cout << "\nStudent File has been loaded\n" << endl;

}

Book* Reader::getCurrent()
{
	return current;
}

User* Reader::getUcurrent()
{
	return Ucurrent;
}


string Reader::getUsername() {
	return username;
}

string Reader::getPassword() {
	return password;
}

void Reader::setUsername(string username) {
	this->username = username;
}

void Reader::setPassword(string password) {
	this->password = password;
}

bool Reader::Login(string Usertry, string Passtry) {

	moveToUhead();//resets pointer of user info data
	while (!(Ucurrent->getUsername() == Usertry && Ucurrent->getPassword() == Passtry))//repeats loop until match is found or last item is reached
	{

		Ucurrent = Ucurrent->getNext();//moving to next until it matches the ID
		if (Ucurrent->getNext() == NULL)//if last item on user info list is reached, break out of loop
			break;
	}
	if (Ucurrent->getUsername() == Usertry && Ucurrent->getPassword() == Passtry)//after loop is broken, confirms if the item the pointer is
	{                                                                            //currently on matches the Log information that was inputed
		return true;//if it does return true

	}
	else
		return false;//if not return false
	moveToUhead();//reset pointer again just in case

}

void Reader::moveToHead()
{
	if (head != NULL)
	{
		current = head;
	}
}

void Reader::moveToUhead()
{
	if (Uhead != NULL)
	{
		Ucurrent = Uhead;
	}
}


bool Reader::checkforFullStudent(string username)
{
	int booksborrowed = 0;
	moveToHead();
	do//do this loop until it reaches the end of the library list
	{
		if (current->getReader() == username)//increment number of borrow books if it finds a book where the reader matches the
			booksborrowed++;         //username of the current user
		current = current->getNext();//moves to next item on list
	} while (current != tail);

	if (booksborrowed >= 5)//the maximum amount of books you can borrow is 5
	{
		cout << "Sorry you have already checked out the maximum amount of books" << endl;
		return true;
	}
	else
		return false;
	moveToHead();
}
bool Reader::checkforLateStudent(string username)
{
	moveToHead();
	int timepassed = date.getDate();//gets the current time as soon as the checkforLate fucntion is called
	int latebooks = 0;
	do//loop until it reaches the last item on the list
	{
		if (current->getReader() == username)
		{
			if ((current->getBorrow() + timepassed) >= (current->getBorrow() + 30))
				latebooks++;//if the book the user is borrowing is expired, increment number of late books
		}
		moveToNext();
	} while (current != tail);
	if (latebooks >= 1)//if you have any late books return, true
	{
		cout << "Sorry you have " << latebooks << " overdue books" << endl;
		return true;
	}
	else
		return false;


	moveToHead();

}


bool Reader::checkforFullTeacher(string username)
{
	int booksborrowed = 0;
	moveToHead();
	do//do this loop until it reaches the end of the library list
	{
		if (current->getReader() == username)//increment number of borrow books if it finds a book where the reader matches the
			booksborrowed++;         //username of the current user
		current = current->getNext();//moves to next item on list
	} while (current != tail);

	if (booksborrowed >= 10)//the maximum amount of books you can borrow is 10
	{
		cout << "Sorry you have already checked out the maximum amount of books" << endl;
		return true;
	}
	else
		return false;
	moveToHead();
}
bool Reader::checkforLateTeacher(string username)
{
	moveToHead();
	int timepassed = date.getDate();//gets the current time as soon as the checkforLate fucntion is called
	int latebooks = 0;
	do//loop until it reaches the last item on the list
	{
		if (current->getReader() == username)
		{
			if ((current->getBorrow() + timepassed) >= (current->getBorrow() + 50))
				latebooks++;//if the book the user is borrowing is expired, increment number of late books
		}
		moveToNext();
	} while (current != tail);
	if (latebooks >= 1)//if you have any late books return, true
	{
		cout << "Sorry you have " << latebooks << " overdue books" << endl;
		return true;
	}
	else
		return false;


	moveToHead();

}

void Reader::SearchbyISBN()
{
	string ISBN;
	cout << "Type the ISBN of the Book you want to search: " << endl;
	cin >> ISBN;
	moveToHead();// resetting the pointer to the beginning
	while (current != NULL)//it will search through the list of books until the end
	{
		if (current->getISBN() == ISBN)//if it finds a match, it prints it out
			current->print();
		current = current->getNext();
	}
}

void Reader::SearchbyID()
{
	int ID;
	cout << "Type the ID of the Book you want to search: " << endl;
	cin >> ID;
	moveToHead();// resetting the pointer to the beginning
	while (current != NULL)//it will search through the list of books until the end
	{
		if (current->getID() == ID)//if it finds a match, it prints it out
			current->print();
		current = current->getNext();
	}
}

void Reader::SearchbyTitle()
{
	string Title;
	cout << "Type the Title of the Book you want to search: " << endl;
	cin >> Title;
	moveToHead(); // resetting the pointer to the beginning
	while (current != NULL)//it will search through the list of books until the end
	{
		if (current->getTitle() == Title)//if it finds a match, it prints it out
			current->print();
		current = current->getNext();
	}
}

void Reader::SearchbyAuthor()
{
	string Author;
	cout << "Type the Author of the Book you want to search: " << endl;
	cin >> Author;
	moveToHead(); //resetting the pointer to the beginning
	while (current != NULL)//it will search through the list of books until the end
	{
		if (current->getAuthor() == Author)//if it finds a match, it prints it out
			current->print();
		current = current->getNext();
	}
}

void Reader::SearchbyCategory()
{
	string Category;
	cout << "Type the Category of the Book you want to search: " << endl;
	cin >> Category;
	moveToHead(); //resetting the pointer to the beginning
	while (current != NULL) //it will search through the list of books until the end
	{
		if (current->getCategory() == Category) //if it finds a match, it prints it out
			current->print();
		current = current->getNext();
	}
}

void Reader::SearchUsers()
{
	string username;
	moveToUhead();
	cout << "Type the Username of the User you want to Search: " << endl; //Asks for an input
	cin >> username;
	while (Ucurrent != NULL) //It will go through the list of users until the end
	{
		if (Ucurrent->getUsername() == username)
			if (Ucurrent->getType() == "LIBRARIAN") //If the user is a librarian, only the username and password are shown
			{
				cout << endl << "Username: " << Ucurrent->getUsername() << endl << "Password: " << Ucurrent->getPassword() << endl;
				break;
			}
			else //Else it is a teacher or student and their username, password, and Type is shown
			{
				cout << "Username: " << Ucurrent->getUsername() << endl << "Password: " << Ucurrent->getPassword();
				cout << endl << Ucurrent->getType() << endl;
				break;
			}
	}

}

string Reader::getRtype(string username)
{
	moveToUhead();//resets pointer of user info data
	while (!(Ucurrent->getUsername() == username))//repeats loop until match is found or last item is reached
	{

		Ucurrent = Ucurrent->getNext();//moving to next until it matches the ID
		if (Ucurrent->getNext() == NULL)//if last item on user info list is reached, break out of loop
			break;
	}
	if (Ucurrent->getUsername() == username)//after loop is broken, confirms if the item the pointer is
	{                                       //currently on matches the Log information that was inputed
		return Ucurrent->getType();

	}

	moveToUhead();//reset pointer again just in case
}

void Reader::cancelreserve(int ID, string username)
{
	moveToHead();//resets pointer so it starts search from the top
	while (current->getID() != ID)//will keep moving down the library list until it finds a mtach or reaches the end
	{
		if (current->getNext() == NULL)//breaks out of loop once it reaches the last book on the library list
			break;
		current = current->getNext();//moving to next until it matches the ID
	}
	if (current->getReserve() == username)//only allowed to cancel reserves that you have placed
	{
		if (current->getID() == ID)//checks again to see if ID entered in search matches ID of the book
		{
			cout << "\nResults" << endl << endl;
			current->print();
			current->setReserve("0");//take users name off reserve category
			cout << endl << "Reservation Cancelled\n" << endl << endl;
			current->print();
		}
		else
			cout << "No results" << endl;
	}
	else
		cout << "You have not reserved this book" << endl;
	moveToHead();//resets pointer again just in case
}

void Reader::renew(int ID, string username)
{
	moveToHead();//resets pointer
	do//do while loop so it checks if its the last item in the library AFTER it has checked if 
	{ //it is the book the user wants to return
		if (current->getReader() == username)//checks if the reader of the book is the same as the person who wants to renew the book
		{
			if (current->getReserve() != "0")
			{
				if (current->getID() == ID)//checks if ID of book matches ID of the book that needs to be renewed
				{
					current->print();
					current->setExpire(current->getExpire() + 30);
					cout << "Book Renewed" << endl;
					current->print();
					return;//if it has returned the book, return because function operation is done
				}
			}
			else
			{
				cout << "Sorry this book has been reserved, it cannot be renewed" << endl;
			}
		}
		current = current->getNext();
	} while (current != tail);//do this until it reaches the last item on the list
	cout << "You have not checked out any Books with that ID number" << endl;
}

void Reader::Myinformation(string username)
{
	cout << "Username: " << username << endl;
	cout << "Books Borrowed: " << endl;
	do//loop until it reaches the last item on the list
	{
		if (current->getReader() == username)
		{
			current->print();
		}
		moveToNext();
	} while (current != tail);
	moveToHead();
	cout << "Books Reserved" << endl;
	do//loop until it reaches the last item on the list
	{
		if (current->getReserve() == username)
		{
			current->print();
		}
		moveToNext();
	} while (current != tail);
}
