#include "Book.h"
#include "Reader.h"
#include<iostream>
#include "DateCounter.h"
using namespace std;


void SearchPanel(istream& in, Reader s1);
void controlPanel(istream& in, Reader& s1, string userattempt, string passattempt); //function to call the library menu and run the switch statement
void MainMenu(istream& in, Reader& s1, string userattempt, string passattempt);//fucntion to be called after the first log in, that way s1.loadAll() isnt called 
																				//again and the library isnt reset
int main() {
	Reader s1;
	s1.loadAll();//loads all the books and student log in info into the program
	string userattempt, passattempt;
	cout << "Please Login" << endl;
	cout << "Username: " << endl;
	cin >> userattempt;
	cout << "Password: " << endl;
	cin >> passattempt;
	if (s1.Login(userattempt, passattempt))//if username and password inputs match, the library menu is called
		controlPanel(cin, s1, userattempt, passattempt); //displaying the library menu starting the second switch statement
	else//if the username and password dont match, it will ask you try again and send you to the MainMenu function
	{
		cout << "Incorrect Username or Password, try again" << endl;
		MainMenu(cin, s1, userattempt, passattempt);//This function is nearly a carbon copy of the int Main() fucntion but without the
	}                                               //loadAll() fucntion call in the beggining, that way if you log out/get the log in 
	system("pause");                                //information wrong, all changes maid to the library arent reset. 
	return 0;
}

void MainMenu(istream& in, Reader& s1, string userattempt, string passattempt)//copy of the main function to be called after the library and student file have already
{                                                                              //been loaded
	cout << "Please Login" << endl;
	cout << "Username: " << endl;
	cin >> userattempt;
	cout << "Password: " << endl;
	cin >> passattempt;
	if (s1.Login(userattempt, passattempt))
		controlPanel(cin, s1, userattempt, passattempt); //displaying the library menu starting the second switch statement
	else
	{
		{
			cout << "Incorrect Username or Password, try again" << endl;
			MainMenu(cin, s1, userattempt, passattempt);
		}
	}

}

void SearchPanel(istream& in, Reader s1)
{
	cout << "-----------------------------------------------------" << endl
		<< "-\t\tWays to Search\t\t-" << endl
		<< "-----------------------------------------------------" << endl;
	cout << endl << "Please choose: " << endl;
	cout << "\n\t1 -- ISBN" << endl;
	cout << "\t2 -- ID" << endl;
	cout << "\t3 -- Title" << endl;
	cout << "\t4 -- Author" << endl;
	cout << "\t5 -- Category" << endl;
	cout << "Enter an option: ";
	char co = 'q';
	cin >> co;
	switch (co) {
	case '1':
		s1.SearchbyISBN();
		break;
	case '2':
		s1.SearchbyID();
		break;
	case '3':
		s1.SearchbyTitle();
		break;
	case '4':
		s1.SearchbyAuthor();
		break;
	case '5':
		s1.SearchbyCategory();
		break;
	}
}

void controlPanel(istream& in, Reader& s1, string userattempt, string passattempt) {

	if (s1.getRtype(userattempt) == "STUDENT")
	{
		cout << "--------------------------------------------------" << endl
			<< "-\t\tWelcome to my Library\t\t-" << endl
			<< "---------------------------------------------------" << endl;
		cout << endl << "Welcome back, Student" << endl;
		cout << endl << "Please choose: " << endl;
		cout << "\n\t0 -- Log Out" << endl;
		cout << "\t1 -- Reserve Book" << endl;
		cout << "\t2 -- Borrow Books" << endl;
		cout << "\t3 -- Return Books" << endl;
		cout << "\t4 -- Cancel Reservation" << endl;
		cout << "\t5 -- Search Books" << endl;
		cout << "\t8 -- My Information" << endl;
		char ch = 'q';
		int ID;
		while (ch != '0') {
			cout << "\nEnter an option: ";
			cin >> ch;
			switch (ch) {
			case '2':
				if (!(s1.checkforFullStudent(userattempt)))//checks to see if you have checked out the maximum amount of books before you borrow one
				{                               //sends the username to  be able to sort through books owned by the person with that username
					if (!(s1.checkforLateStudent(userattempt)))//checks to see if you have any overdue books before you borrow one
					{                             //both those functions have to return false in order for borrow books to be allowed
						cout << "Enter the ID of the book you want to borrow" << endl;
						cin >> ID;
						s1.borrowBooks(ID);
					}
				}
				break;
			case '3':
				cout << "Enter the ID of the book you want to return" << endl;
				cin >> ID;
				s1.returnBooks(ID, userattempt);//sends the ID of the book you want to return AND username to be able to find out if you own the book you want to return
				break;//Running the return books function
			case '0':
				MainMenu(cin, s1, userattempt, passattempt);//if you log out, return to main menu without reloading the library
				break;
			case '1':
				cout << "Enter the ID of the book you want to reserve" << endl;
				cin >> ID;
				s1.reservebook(ID, userattempt);//sends the ID of the book you want to return AND username to be able to find out if you own the book you want to return
				break;//Running the return books function
			case '4':
				cout << "Enter the ID of the book whose reservation you want to cancel" << endl;
				cin >> ID;
				s1.cancelreserve(ID, userattempt);//sends the ID of the book you want to return AND username to be able to find out if you own the book you want to return
				break;//Running the return books function
			case '5':
				SearchPanel(cin, s1); //calls the SearchPanel function to show the menu of options for searching
				break;
			case '8':
				s1.Myinformation(userattempt);
				break;
			}
		}
	}

	if (s1.getRtype(userattempt) == "TEACHER")
	{
		cout << "--------------------------------------------------" << endl
			<< "-\t\tWelcome to my Library\t\t-" << endl
			<< "---------------------------------------------------" << endl;
		cout << endl << "Welcome back, Teacher" << endl;
		cout << endl << "Please choose: " << endl;
		cout << "\n\t1 -- Reserve Book" << endl;
		cout << "\t2 -- Borrow Books" << endl;
		cout << "\t3 -- Return Books" << endl;
		cout << "\t4 -- Cancel Reservation" << endl;
		cout << "\t5 -- Search Books" << endl;
		cout << "\t8 -- My Information" << endl;
		cout << "\t0 -- Log Out" << endl;
		char ch = 'q';
		int ID;
		while (ch != '0') {
			cout << "\nEnter an option: ";
			cin >> ch;
			switch (ch) {
			case '2':
				if (!(s1.checkforFullTeacher(userattempt)))//checks to see if you have checked out the maximum amount of books before you borrow one
				{                               //sends the username to  be able to sort through books owned by the person with that username
					if (!(s1.checkforLateTeacher(userattempt)))//checks to see if you have any overdue books before you borrow one
					{                             //both those functions have to return false in order for borrow books to be allowed
						cout << "Enter the ID of the book you want to borrow" << endl;
						cin >> ID;
						s1.borrowBooks(ID);
					}
				}
				break;
			case '3':
				cout << "Enter the ID of the book you want to return" << endl;
				cin >> ID;
				s1.returnBooks(ID, userattempt);//sends the ID of the book you want to return AND username to be able to find out if you own the book you want to return
				break;//Running the return books function
			case '0':
				MainMenu(cin, s1, userattempt, passattempt);//if you log out, return to main menu without reloading the library
				break;
			case '1':
				cout << "Enter the ID of the book you want to reserve" << endl;
				cin >> ID;
				s1.reservebook(ID, userattempt);//sends the ID of the book you want to return AND username to be able to find out if you own the book you want to return
				break;//Running the return books function
			case '4':
				cout << "Enter the ID of the book whose reservation you want to cancel" << endl;
				cin >> ID;
				s1.cancelreserve(ID, userattempt);//sends the ID of the book you want to return AND username to be able to find out if you own the book you want to return
				break;//Running the return books function
			case '5':
				SearchPanel(cin, s1); //calls the SearchPanel function to show the menu of options for searching
				break;
			case '8':
				s1.Myinformation(userattempt);
				break;
			}
		}
	}

	if (s1.getRtype(userattempt) == "LIBRARIAN")
	{
		cout << "--------------------------------------------------" << endl
			<< "-\t\tWelcome to my Library\t\t-" << endl
			<< "---------------------------------------------------" << endl;
		cout << endl << "Welcome back, Librarian" << endl;
		cout << endl << "Please choose: " << endl;
		cout << "\n\t0 -- Log Out" << endl;
		cout << "\t1 -- Search Books" << endl;
		cout << "\t2 -- Add Books" << endl;
		cout << "\t3 -- Delete Books" << endl;
		cout << "\t4 -- Search Users" << endl;
		cout << "\t5 -- Add User" << endl;
		cout << "\t6 -- Delete User" << endl;
		cout << "\t7 -- My Information" << endl;
		char ch = 'q';
		int ID;
		while (ch != '0') {
			cout << "\nEnter an option: ";
			cin >> ch;
			switch (ch) {
			case '2':
				s1.AddBook();
				break;
			case '3':
				s1.DeleteBook();
				break;
			case '0':
				MainMenu(cin, s1, userattempt, passattempt);//if you log out, return to main menu without reloading the library
				break;
			case '1':
				SearchPanel(cin, s1); //calls the SearchPanel function to show the menu of options for searching
				break;
			case '4':
				s1.SearchUsers();
				break;
			case '5':
				s1.AddUser();
				break;
			case '6':
				s1.DeleteUser();
				break;
			case '7':
				s1.Myinformation(userattempt);
				break;
			}
		}
	}
}
