#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class User {
public:
	string name, surname, id_no;
	int account_num;
	double balance; 

	void create_user() {
		
		cout << "Name: ";
		cin >> name;
		cout << "Surname: ";
		cin >> surname;
		cout << "ID Number: ";
		cin >> id_no;
		cout << "Account Number: ";
		cin >> account_num;
		cout << "Balance: ";
		cin >> balance;
		cout << endl;
	}

	bool login(string id) {
		if (id != id_no){
			cout << "You entered wrong id number. Please try again!"<< endl;
			return false;
		}
		return true;
	}

	void setBalance(double b) {
		balance = b;
		cout << "Balance: " << balance << endl;
	}

	void UserDetail() {

		cout << "Name: " << name << endl;
		cout << "Surname: " << surname << endl;
		cout << "ID Number: " << id_no << endl;
		cout << "Account Number: " << account_num << endl;
		cout << "Balance: " << balance << endl;
		cout << endl;
	};
};

class BankOperations {
public:
	double put_money(User u) {
		
		double deposit;
		cout << "Amount to be Deposited: ";
		cin >> deposit;
		return u.balance + deposit;
		cout << endl;

	}
	virtual double withdraw() {
		
		cout << "Withdraw Money: ";
		return 0;
		cout << endl;
	}
	virtual double transfer() {
		
		cout << "Transfer: ";
		return 0;
		cout << endl;
	}
};

class Garanti : public BankOperations {
public:
	double withdraw(User u) {
		double w;
		cout << "Enter the amount to withdraw: ";
		cin >> w;
		if (w > u.balance) {
			cout << "You cannot withdraw more than your balance."<<endl;
			return u.balance;
		}
		else if (w > 5000) {
			cout << "You cannot withdraw money because maximum limit of Garanti bank is 5000 TL."<<endl;
			return u.balance;
		}
		return u.balance - w;
		cout << endl;
	}
	double transfer(User u) {
		double t;
		cout << "How much money will you send: ";
		cin >> t;
		if (t > u.balance) {
			cout << "The amount to be sent cannot be greater than your balance!"<<endl;
			return u.balance;
		}
		else if (t == u.balance) {
			cout << "Your balance is not enough because of commission fee."<<endl;
			return u.balance;
		}
		else
		{
			cout << "2% deduction amount is reflected in the money transfer process from Garanti bank."<< endl;
			t = u.balance - (t + ((t / 100) * 2));
			return t;
		}
		cout << endl;
	}
};

class Ziraat : public BankOperations {
public:
	double withdraw(User u) {
		double w;
		cout << "Enter the amount to withdraw: ";
		cin >> w;
		if (w > 10000) {
			cout << "You cannot withdraw money because maximum limit of Ziraat bank is 10000 TL."<<endl;
			return u.balance;
		}
		else if (w > u.balance) {
			cout << "You cannot withdraw more than your balance."<<endl;
			return u.balance;
		}
		return u.balance - w;
		cout << endl;
	}
	double transfer(User u) {
		double t;
		cout << "How much money will you send: ";
		cin >> t;
		if (t > u.balance) {
			cout << "The amount to be sent cannot be greater than your balance!"<<endl;
			return u.balance;
		}
		else if (t == u.balance)
		{
			cout << "Your balance is not enough because of commission fee."<<endl;
			return u.balance;
		}
		else
		{
			cout << "4% deduction amount is reflected in the money transfer process from Ziraat bank."<<endl;
			t = u.balance - (t + ((t / 100) * 4));
			return t;
		}
		cout << endl;
	}
};

class Menu  {
public:
	Menu(User u, Garanti g, Ziraat z) {
		int chosen;
		cout << "\t*****Bank Simulation*****\n" << endl;
		bool counter = false;
		while (counter == false){
			
			cout << "1- Create Account" << endl << "2- Login Account" << endl;
			cout << "Enter the action you want to do: ";
			cin >> chosen;
			cout << endl;

			switch (chosen){
			case 1:
				u.create_user();
				break;
			case 2:
				if ( u.id_no == "") {
					string id;
					cout << "Enter ID number: ";
					cin >> id;
					cout << "No such account found. Please sign up." << endl;
					
				}
				else {
					string id;
					cout << "ID Number: ";
					cin >> id;
					counter = u.login(id);
				}
				break;
			default:
				cout << "Please enter a valid number" << endl;
				
			}
			cout << endl;
		}
		while (true) {
			int choosen;
			cout << "1- Transfer Money" << endl;
			cout << "2- Withdraw Money" << endl;
			cout << "3- Put Money" << endl;
			cout << "4- Show User Details" << endl;
			cout << "Write '-1' to Exit" << endl;
			cout << "Enter the action you want to do: ";
			cin >> choosen;
			cout << endl;

			if (choosen == -1) {
				break;
			}
			else {
				switch (choosen) {
				case 1:
					int bank;
					cout << "Which bank do you prefer?" << endl;
					cout << "1- Garanti" << endl;
					cout << "2- Ziraat" << endl;
					cin >> bank;
					switch (bank) {
					case 1: {

						u.setBalance(g.transfer(u));
						break;
					}
					case 2: {

						u.setBalance(z.transfer(u));
						break;
					}
					}
					break;
				case 2:
					int bank2;
					cout << "Which bank do you withdraw money?" << endl;
					cout << "1- Garanti" << endl;
					cout << "2- Ziraat" << endl;
					cin >> bank2;
					switch (bank2) {
					case 1: {
						double gCek = g.withdraw(u);
						u.setBalance(gCek);
						break;
					}
					case 2: {
						double zCek = z.withdraw(u);
						u.setBalance(zCek);
						break;
					}
					}
					break;
				case 3:
					int bank3;
					cout << "Which bank do you put money?" << endl;
					cout << "1- Garanti" << endl;
					cout << "2- Ziraat" << endl;
					cin >> bank3;
					switch (bank3) {
					case 1: {
						double gYat = g.put_money(u);
						u.setBalance(gYat);
						break;
					}
					case 2: {
						double zYat = z.put_money(u);
						u.setBalance(zYat);
						break;
					}
					}
					break;
				case 4:
					u.UserDetail();
					break;
				}
			}
			cout << endl;
		}
	}
};

int main() {
	
	User u;
	Garanti g;
	Ziraat z;
	Menu menu(u,g,z);
	
	return 0;
}