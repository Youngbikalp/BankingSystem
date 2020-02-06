#include "banking.h"

int account_no;
int loan_no;

// structure to simulate each transaction(deposit, withdraw, send, receive, loan)
Transaction :: Transaction(int type=0, int amount=0, int etc=0){
	this->type=type;
	this->amount=amount;
	this->to_from_type=etc;
}

// structure that contains the information of each account
Account :: Account(string name="", string mobile_no="", int amount=0, int credit=rand()%400+450, vector <Transaction> transaction=vector <Transaction> (0)){
	this->name=name,
	this->mobile_no=mobile_no,
	this->amount=amount,
	this->credit=credit;
	this->transactions=transaction;
}

// structure that contains the information of each loans
Loan :: Loan(int no=0, int type=0){
	this->account_no=no,
	this->loan_type=type;
};

// store all accounts by account number
map <int, Account> Accounts;

// store all loans by loan no
map <int, Loan> Loans;

// check that the given string has digit characters
bool contains_digit(string s){
	for(int i=0; i<s.length(); i++){
		if(isdigit(s[i])) return true;
	}
	return false;
}

// check that the given string has alphabet characters
bool contains_alpha(string s){
	for(int i=0; i<s.length(); i++){
		if(isalpha(s[i])) return true;
	}
	return false;
}

// clear the console screen and print the title
void clear(){
	system("cls");
	cout << "======================" << endl;
	cout << "BANK MANAGEMENT SYSTEM" << endl;
	cout << "======================" << endl;
}

// confirm the result for chosen operation and then return to the main menu
void confirm(){
	getchar();
	while(!getchar());
	return main_menu();
}

// implement to open a new account
// account no is given automatically
// input name and mobile number and then show the result
void open_account(){
	clear();
	cout << "::Open A New Account::" << endl;
	Account account;
	account_no++;
	cout << "Account no : " << account_no << endl;
	cout << "Name       : ";
	cin >> account.name;
	if(contains_digit(account.name)){
		cout << "Name should consists of alphabets" << endl;
		account_no--;
		return confirm();
	}
	cout << "Mobile no  : ";
	cin >> account.mobile_no;
	if(contains_alpha(account.mobile_no) || account.mobile_no.length()!=10){
		cout << "Mobile number should consists of 10 digits" << endl;
		account_no--;
		return confirm();
	}
	cout << "Account " << account_no << " is opened successfully" << endl;
	Accounts[account_no]=account;
	
	confirm();
}

// implement to deposit amount
// input an existing account no and deposit amount
void deposit(){
	clear();
	cout << "::Deposit Amount::" << endl;
	int account_no, amount;
	cout << "Account no : ";
	cin >> account_no;
	if(!Accounts.count(account_no)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	cout << "Amount     : ";
	cin >> amount;
	Accounts[account_no].amount+=amount;
	cout << "Succeeded. Current deposit amount is " << Accounts[account_no].amount << endl;
	Accounts[account_no].transactions.push_back(Transaction(0, amount));
	confirm();
}

// implement to withdraw
// input an existing account no and valid withdraw amount
void withdraw(){
	clear();
	cout << "::Withdraw Amount::" << endl;
	int account_no, amount;
	cout << "Account no : ";
	cin >> account_no;
	if(!Accounts.count(account_no)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	cout << "Current deposit amount is " << Accounts[account_no].amount << endl;
	cout << "Amount     : ";
	cin >> amount;
	while(Accounts[account_no].amount<amount){
		cout << "Failed. Please reenter" << endl;
		cout << "Amount     : ";
		cin >> amount;
	}
	Accounts[account_no].amount-=amount;
	cout << "Succeeded. Current deposit amount is " << Accounts[account_no].amount << endl;
	Accounts[account_no].transactions.push_back(Transaction(1, amount));
	confirm();
}

// display account no and the deposit amount for each accounts
void display(){
	clear();
	cout << "::Accounts Menu::" << endl;
	for(auto it : Accounts){
		cout << it.first << '\t' << it.second.amount << endl;
	}
	confirm();
}

// implement to delete an exsiting account
void delete_account(){
	clear();
	cout << "::Delete an existing account::" << endl;
	int account_no;
	cout << "Account no : ";
	cin >> account_no;
	if(!Accounts.count(account_no)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	Accounts.erase(account_no);
	cout << "Account " << account_no << " is closed successfully" << endl;
	confirm();
}

// implement to give loan
// input account no, loan amount, period
void _Loan(){
	clear();
	int account_no;
	cout << "Account no : ";
	cin >> account_no;
	if(!Accounts.count(account_no)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	Account account=Accounts[account_no];
	if(account.credit<550){
		cout << "Could not loan, because of low credit score" << endl;
		return confirm();
	}
	int amount, period, rate;
	if(account.credit<650) rate=20;
	else if(account.credit<750) rate=15;
	else rate=5;
	
	cout << "Amount     : ";
	cin >> amount;
	cout << "Period (10,20 or 30 years): " << endl;
	cin >> period;
	cout << "monthly payment is " << int(double(amount)*rate/100+0.5) << endl;
	Loans[++loan_no]=Loan(account_no, period);

	Accounts[account_no].transactions.push_back(Transaction(2, amount, period));
	confirm();
}

// search an account with given number and display all information
void search(){
	clear();
	cout << "::Search::" << endl;
	int account_no;
	cout << "Account no : ";
	cin >> account_no;
	if(!Accounts.count(account_no)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	Account account=Accounts[account_no];
	cout << "name   : " << account.name << endl;
	cout << "mobile : " << account.mobile_no << endl;
	cout << "amount : " << account.amount << endl;
	cout << "credit : " << account.credit << endl;
	confirm();
}

// transfer money to another account
void transfer(){
	clear();
	cout << "::Transfer::" << endl;
	int account_no_from, account_no_to, amount;
	cout << "Account no(From) : ";
	cin >> account_no_from;
	if(!Accounts.count(account_no_from)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	cout << "Current deposit amount is " << Accounts[account_no_from].amount << endl;
	cout << "Amount     : ";
	cin >> amount;
	while(Accounts[account_no_from].amount<amount){
		cout << "Failed. Please reenter" << endl;
		cout << "Amount     : ";
		cin >> amount;
	}
	cout << "Account no(To) : ";
	cin >> account_no_to;
	if(!Accounts.count(account_no_to)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	Accounts[account_no_from].amount-=amount;
	Accounts[account_no_to].amount+=amount;
	cout << "Succeeded" << endl;
	cout << "Current deposit of Account " << account_no_from << " is " << Accounts[account_no_from].amount << endl;
	cout << "Current deposit of Account " << account_no_to << " is " << Accounts[account_no_to].amount << endl;
	Accounts[account_no_from].transactions.push_back(Transaction(3, amount, account_no_to));
	Accounts[account_no_to].transactions.push_back(Transaction(4, amount, account_no_from));
	
	confirm();
}

// display transactions for an account
void display_transation(){
	clear();
	cout << "::Display transaction::" << endl;
	int account_no;
	cout << "Account no : ";
	cin >> account_no;
	if(!Accounts.count(account_no)){
		cout << "There is no such account" << endl;
		return confirm();
	}
	vector <Transaction> &vec=Accounts[account_no].transactions;
	for(int i=0; i<vec.size(); i++){
		switch(vec[i].type){
			case 0:
				cout << vec[i].amount << " is deposited" << endl;
				break;
			case 1:
				cout << vec[i].amount << " is withdrawn" << endl;
				break;
			case 2:
				cout << vec[i].amount << " is loaned and will be paid within " << vec[i].to_from_type << endl;
				break;
			case 3:
				cout << "Sended " << vec[i].amount << " to Account " << vec[i].to_from_type << endl;
				break;
			case 4:
				cout << "Received " << vec[i].amount << " from Accout " << vec[i].to_from_type << endl;
				break;
		}
	}
	confirm();
}

// begin the simulation
// input account information from data file
void begin(){
	ifstream fin;
	fin.open("data.txt");
	int id, amount, credit;
	string name, mobile_no;
	fin >> account_no;
	int account_cnt=0;
	fin >> account_cnt;
	for(int i=0; i<account_cnt; i++){
		fin >> id >> name >> mobile_no >> amount >> credit;
		int transaction_len=0;
		fin >> transaction_len;
		Accounts[id]=Account(name, mobile_no, amount, credit);
		for(int j=0; j<transaction_len; j++){
			int type, amount, etc;
			fin >> type >> amount >> etc;
			Accounts[id].transactions.push_back(Transaction(type, amount, etc));
		}
	}
}

// finish the simulation
// output account information to data file
void finish(){
	ofstream fout;
	fout.open("data.txt");
	fout << account_no << endl;
	fout << Accounts.size() << endl;
	for(auto it : Accounts){
		fout << it.first << ' ' << it.second.name << ' ' << it.second.mobile_no << ' ' << it.second.amount << ' ' << it.second.credit << endl;
		fout << it.second.transactions.size() << endl;
		for(auto e : it.second.transactions){
			fout << e.type << ' ' << e.amount << ' ' << e.to_from_type << endl;
		}
	}
	exit(0);
}

// print the main menu
void main_menu(){
	clear();
	cout << "    ::MAIN MENU::     " << endl;
	cout << "1. Open Account       " << endl;
	cout << "2. Deposit Amount     " << endl;
	cout << "3. Withdraw Amount    " << endl;
	cout << "4. Display all Account" << endl;
	cout << "5. Delete Account     " << endl;
	cout << "6. Loan               " << endl;
	cout << "7. Search             " << endl;
	cout << "8. Transfer money     " << endl;
	cout << "9. Display transaction" << endl;
	cout << "10. Exit              " << endl;
	
	cout << "Select Your Option (1-10): ";
	int option;
	cin >> option;
	switch(option){
		case 1:
			open_account();
			break;
		case 2:
			deposit();
			break;
		case 3:
			withdraw();
			break;
		case 4:
			display();
			break;
		case 5:
			delete_account();
			break;
		case 6:
			_Loan();
			break;
		case 7:
			search();
			break;
		case 8:
			transfer();
			break;
		case 9:
			display_transation();
			break;
		case 10:
			finish();
			break;
		default:
			main_menu();
			break;
	}
}