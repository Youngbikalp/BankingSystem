#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// structure to simulate each transaction(deposit, withdraw, send, receive, loan)
struct Transaction{
	int type;
	int amount;
	int to_from_type;
	Transaction(int, int, int);
};

// structure that contains the information of each account
struct Account{
	int amount;
	int credit;
	string name;
	string mobile_no;
	vector <Transaction> transactions;
	Account(string, string, int, int, vector <Transaction>);
};

// structure that contains the information of each loans
struct Loan{
	int account_no;
	int loan_type;
	Loan(int, int);
};

// check that the given string has digit characters
bool contains_digit(string s);

// check that the given string has alphabet characters
bool contains_alpha(string s);

// clear the console screen and print the title
void clear();

// confirm the result for chosen operation and then return to the main menu
void confirm();

// implement to open a new account
// account no is given automatically
// input name and mobile number and then show the result
void open_account();

// implement to deposit amount
// input an existing account no and deposit amount
void deposit();

// implement to withdraw
// input an existing account no and valid withdraw amount
void withdraw();

// display account no and the deposit amount for each accounts
void display();

// implement to delete an exsiting account
void delete_account();

// implement to give loan
// input account no, loan amount, period
void _Loan();

// search an account with given number and display all information
void search();

// transfer money to another account
void transfer();

// display transactions for an account
void display_transation();

// begin the simulation
// input account information from data file
void begin();

// finish the simulation
// output account information to data file
void finish();

// print the main menu
void main_menu();