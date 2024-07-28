#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include "inputs.h"
#include "myLib.h"
#include "strings.h"


using namespace std;

string ClientsFileName = "clients.txt";

enum enOparations { showClients = 1, addClient = 2, deleteClient = 3, updateClient = 4, findClinet = 5, transactions = 6, manageUsers = 7, logout = 8 };
enum enManageOp{listUsers=1 , addUser=2 , deleteUser=3 , updateUser=4 , findUser=5 ,mainMenue=6};
enum enTransactions{deposit=1 , withdraw,showTotalBalances,mainMenu};
enum enPermissions{ pshowClients = 1, paddClient = 2, pdeleteClient = 4, pupdateClient = 8, pfindClinet = 16, ptransactions = 32, pmanageUsers = 64,fullAccess=-1};

struct stClient {
	string accontNumber, name, phone, pinCode;
	int accontBalance = 0;

};
struct stUser {
	string userName, password;
	int permission;
};

///////////////////////////
void goToSystem(int);
bool login();
void goToManageUsersMenue(int);


stUser convertStringToUserRecord(string str, string delim = "#//#") {
	vector <string> vRecord;
	strings::splitStringToVector(str, delim, vRecord);

	stUser user;
	user.userName = vRecord[0];
	user.password = vRecord[1];
	user.permission = stoi(vRecord[2]);
	return user;

}

vector <stUser> loadUsersDataFromFile(string fileName) {
	vector <stUser> vUsers;
	fstream myFile;
	myFile.open(fileName, ios::in);

	if (myFile.is_open()) {
		string line;
		stUser user;

		while (getline(myFile, line)) {
			user = convertStringToUserRecord(line);
			vUsers.push_back(user);
		}
		myFile.close();
	}
	return vUsers;
}

string convertUserRecordToString(stUser user, string delim = "#//#") {
	string line = "";
	line += user.userName + delim;
	line += user.password + delim;
	line += to_string(user.permission);

	return line;
}


/////////////////////
bool isFindInUsers(string userName) {
	vector <stUser> vUsers = loadUsersDataFromFile("users.txt");
	for (stUser & u : vUsers) {
		if (userName == u.userName) {
			return 1;
		}
	}
	return 0;
}

stUser readUser(stUser user , bool forUpdate=false) {
	char answer = 'n';
	if (!forUpdate) {
		cout << "Enter UserName : ";cin >> user.userName;

		while (isFindInUsers(user.userName)) {
			cout << "User With [" << user.userName << "] already exists , Enter another UserName : ";
			cin >> user.userName;
		}
	}

	cout << "Enter Password : ";cin >> user.password;
	cout << "Do you want give full access y/n ? ";cin >> answer;
	if (answer == 'y' || answer == 'Y')
		user.permission = int(enPermissions::fullAccess);
	else {
		cout << "Do you want give access to : \n\n";
		int permiss = 0;

		cout << "Show Client List y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::pshowClients);

		cout << "Add New Client y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::paddClient);

		cout << "Delete Client y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::pdeleteClient);

		cout << "Update Client y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::pupdateClient);


		cout << "Find Client y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::pfindClinet);

		cout << "Transaction Client y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::ptransactions);

		cout << "Manage Users y/n? ";cin >> answer;
		if (answer == 'y' || answer == 'Y')
			permiss |= int(enPermissions::pmanageUsers);


		user.permission = permiss;
	}
	return user;
}

stClient convertStringToRecord(string str, string delim = "#//#") {
	vector <string> vRecord;
	strings::splitStringToVector(str, delim, vRecord);

	stClient client;
	client.accontNumber = vRecord[0];
	client.pinCode = vRecord[1];
	client.name = vRecord[2];
	client.phone = vRecord[3];
	client.accontBalance = stoi(vRecord[4]);
	return client;

}

vector <stClient> loadClientsDataFromFile(string fileName) {
	vector <stClient> vClients;
	fstream myFile;
	myFile.open(fileName, ios::in);

	if (myFile.is_open()) {
		string line;
		stClient client;

		while (getline(myFile, line)) {
			client = convertStringToRecord(line);
			vClients.push_back(client);
		}
		myFile.close();
	}
	return vClients;
}

void printClientCard(stClient client) {
	cout << "\n---------------------------------------\n";
	cout << "Account number : " << client.accontNumber << endl;
	cout << "pinCode        : " << client.pinCode << endl;
	cout << "Name           : " << client.name << endl;
	cout << "phone          : " << client.phone << endl;
	cout << "Accont balance : " << client.accontBalance << endl;
	cout << "---------------------------------------\n";

}

void printClientCard(string line) {
	vector <string> vClient;
	strings::splitStringToVector(line, "#//#", vClient);

	cout << "Enter Account number : " << vClient[0] << endl;
	cout << "Enter pinCode        : " << vClient[1] << endl;
	cout << "Enter Name           : " << vClient[2] << endl;
	cout << "Enter phone          : " << vClient[3] << endl;
	cout << "Enter Accont balance : " << vClient[4] << endl; cout << endl;

}

void printClient(stClient client) {
	string accNumber = "| " + client.accontNumber;
	string pinCode = "| " + client.pinCode;
	string name = "| " + client.name;
	string phone = "| " + client.phone;
	string balance = "| " +to_string(client.accontBalance);
	
	cout << left << setw(20) << accNumber << left << setw(15) << pinCode << left << setw(40) << name << left << setw(15) <<phone<< setw(15) <<balance<< endl;

}

string convertRecordToString(stClient client, string delim = "#//#") {
	string line = "";
	line += client.accontNumber + delim;
	line += client.pinCode + delim;
	line += client.name + delim;
	line += client.phone + delim;
	line += to_string(client.accontBalance);

	return line;
}


void AddClientToFile(stClient client, string fileName) {
	string line = convertRecordToString(client, "#//#");
	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);

	if (myFile.is_open()) {
		myFile <<line<<endl;
		myFile.close();
	}
}


void loadFileToVector(string fileName, vector <string>& vLines) {
	fstream myFile;
	myFile.open(fileName, ios::in);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			vLines.push_back(line);
		}
		myFile.close();
	}
}


bool isFind(string accNumber) {
	vector <string> vLines;

	loadFileToVector(ClientsFileName, vLines);
	for (string& line : vLines) {
		stClient client = convertStringToRecord(line, "#//#");
		if (accNumber == client.accontNumber) {
			return 1;
		}
	}
	return 0;
}


void readClient(stClient& client, bool forUpdate = false) {
	if (!forUpdate)
	{
		cout << "Enter Account number : "; getline(cin >> ws, client.accontNumber);

		while (isFind(client.accontNumber)) {
			cout << "Client With [" << client.accontNumber << "] already exists , Enter another Account Number : ";

			getline(cin >> ws, client.accontNumber);
		}
	}

	cout << "Enter pinCode        : "; getline(cin >> ws, client.pinCode);
	cout << "Enter Name           : "; getline(cin, client.name);
	cout << "Enter phone          : "; getline(cin, client.phone);
	cout << "Enter Accont balance : "; cin >> client.accontBalance;  cout << endl << endl;
}


bool findClientByAccountNumber(string accontNumber, stClient& SourceClient, string fileName) {
	vector <string> vLines;

	loadFileToVector(fileName, vLines);
	for (string& line : vLines) {
		stClient client = convertStringToRecord(line, "#//#");
		if (accontNumber == client.accontNumber) {
			SourceClient = client;
			return 1;
		}
	}
	return 0;
}


void LoadVectorToFile(vector <string>& vStr, string fileName) {
	fstream myFile;
	myFile.open(fileName, ios::out);

	if (myFile.is_open()) {
		for (string& line : vStr) {
			if (line != "")
				myFile << line << endl;
		}
	}
}


void deleteClientFromFile(stClient client, string fileName) {
	string line = convertRecordToString(client, "#//#");

	vector <string> vLines; loadFileToVector(fileName, vLines);

	for (string& a : vLines) {
		if (a == line) {
			a = "";
			break;
		}
	}
	LoadVectorToFile(vLines, fileName);
}

void loadFileToVector(string fileName, vector <stClient>& vLines) {
	fstream myFile;
	myFile.open(fileName, ios::in);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			vLines.push_back(convertStringToRecord(line));
		}
		myFile.close();
	}
}

void updateClientsInVector(vector < stClient>& vClients, stClient client) {

	for (stClient& c : vClients) {
		if (c.accontNumber == client.accontNumber) {
			c.accontBalance = client.accontBalance;
			c.name = client.name;
			c.phone = client.phone;
			c.pinCode = client.pinCode;
			break;
		}
	}
}

void loadClientsToFile(vector < stClient>& vClients, string fileName) {
	vector <string> vLines;
	for (stClient & c : vClients) {
		vLines.push_back(convertRecordToString(c));
	}
	LoadVectorToFile(vLines, fileName);
}


void updateClientInFile(vector < stClient>& vClients , stClient client, string fileName) {

	for (stClient& c : vClients) {
		if (c.accontNumber == client.accontNumber)
		{
			c.accontBalance = client.accontBalance;
			break;
		}
	}
	loadClientsToFile(vClients, ::ClientsFileName);
}

void printBalance(stClient client) {
	string accNumber = "| " + client.accontNumber;
	string name = "| " + client.name;
	string balance = "| " + to_string(client.accontBalance);

	cout << left << setw(20) << accNumber << left << setw(40) << name << left << setw(40) << balance << endl;

}
////////////////////////////
void showMainMenueScreen() {
	cout << "===========================================\n";
	cout << "             Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "    [1] Show Client List.\n";
	cout << "    [2] Add New Client.\n";
	cout << "    [3] Delete Client.\n";
	cout << "    [4] Update Client Info.\n";
	cout << "    [5] Find Client.\n";
	cout << "    [6] Transactions.\n";
	cout << "    [7] Manage Users.\n";
	cout << "    [8] Logout.\n";
	cout << "===========================================\n";
}

void goToShowClients(vector < stClient>& vClients) {
	cout <<"\t\t\t\t\t" << "Client List (" << vClients.size() << ") Client(s).\n";
	cout << "\n_________________________________________________________________________________________________________\n\n";
	cout << left << setw(20) << "| Account Number " << left << setw(15) << "| Pin Code " << left << setw(40) << "| Client Name " << left << setw(15) << "| Phone " << setw(15) << "| Balance " << endl;
	cout << "_________________________________________________________________________________________________________\n\n";
	for (int i = 0; i < vClients.size(); i++) {
		printClient(vClients[i]);
	}
	cout << "_________________________________________________________________________________________________________\n";

}

void goToAddClient(vector < stClient>& vClients){

	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "       Add New Client \n";
		cout << "\n-------------------------------\n";
		cout << "Adding New Client : \n\n";
		stClient client; readClient(client);
		AddClientToFile(client, ::ClientsFileName);
		vClients.push_back(client);
	} while (myLib::isContinue("Client Added Successfully , do you want to add more clients ? yes[1] , no[0] ? "));
}

void goToDeleteClient(vector < stClient>& vClients){
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Delete Client Screen\n";
		cout << "\n-------------------------------\n\n";

		string accountNumber = inputs::readString("Please enter AccountNumber : ");
		stClient client;

		if (findClientByAccountNumber(accountNumber, client, ::ClientsFileName)) {
			printClientCard(client);
			if (myLib::isContinue("\nAre You Sure You Want Delete This Client [1]:yes , [0]:no ? ")) {
				deleteClientFromFile(client, ::ClientsFileName);
				cout << "Client deleted Successfully , ";
			}
			else {
				cout << "Ok,Not deleted .\n";
			}
		}
		else {
			cout << "\nClient with Account Number (" << accountNumber << ") Not Found!\n";
		}
		vClients.clear();
		loadFileToVector(::ClientsFileName, vClients);

	} while (myLib::isContinue("do you want to delete more clients ? yes[1] , no[0] ? "));

}

void goToUpdateClient(vector < stClient>& vClients){

	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Update Client Screen\n";
		cout << "\n-------------------------------\n\n";

		string accountNumber = inputs::readString("Please enter AccountNumber : ");
		stClient client;

		if (findClientByAccountNumber(accountNumber, client, ::ClientsFileName)) {
			cout << "The following are the client details : \n";
			printClientCard(client);
			if (myLib::isContinue("\nAre You Sure You Want Update This Client [1]:yes , [0]:no ? ")) {
				readClient(client, true);
				updateClientsInVector(vClients,client);
				loadClientsToFile(vClients, ::ClientsFileName);
				cout << "Client Updated Successfully , ";
			}
			else {
				cout << "Ok,Not Updated .\n";
			}
		}
		else {
			cout << "\nClient with Account Number (" << accountNumber << ") Not Found!\n";
		}
		vClients.clear();
		loadFileToVector(::ClientsFileName, vClients);

	} while (myLib::isContinue("do you want to Update more clients ? yes[1] , no[0] ? "));


}

void goToFindClient(vector < stClient>& vClients){
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "       Find Client Screen \n";
		cout << "\n-------------------------------\n";
		
		string accountNumber = inputs::readString("\nPlease enter AccountNumber : ");
		stClient client;
		if (findClientByAccountNumber(accountNumber, client, ::ClientsFileName)) {
			cout << "The following are the client details : \n";
			printClientCard(client);
		}
		else {
			cout << "\nClient with Account Number (" << accountNumber << ") Not Found!\n";
		}
	} while (myLib::isContinue("do you want to Search more ? yes[1] , no[0] ? "));
}

void showExitScree() {
	cout << "\n-----------------------------------------\n";
	cout << "         Program Ends :-)\n";
	cout << "-----------------------------------------\n";

}


void getDoOperation(enOparations);
void backToProgram(int permission ,bool backFromTransactionsMenue=false) {
	if (!backFromTransactionsMenue)
	{
		cout << "Press any key to go back to main Menue ...";
		system("pause>0");
	}
	goToSystem(permission);
}

void showTransactionsMenue() {
	cout << "===========================================\n";
	cout << "         Transactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "    [1] Deposit.\n";
	cout << "    [2] Withdraw.\n";
	cout << "    [3] Show Total Balances.\n";
	cout << "    [4] Main Menue.\n";
	cout << "===========================================\n";
}

void goToTransactionsMenue(vector<stClient>&vClients);

void backToTransactionsMenu(vector < stClient>& vClients) {
	cout << "Press any key to go back to main Menue ...";
	system("pause>0");
	system("cls");
	goToTransactionsMenue(vClients);
}


void goToDeposit(vector < stClient>& vClients) {

	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Deposit Screen\n";
		cout << "\n-------------------------------\n\n";

		string accountNumber = inputs::readString("Please enter AccountNumber : ");
		stClient client;
		int depositAmount = 0;

		if (findClientByAccountNumber(accountNumber, client, ::ClientsFileName)) {
			printClientCard(client);
			
			depositAmount = inputs::readPositiveNumber("Please enter deposit amount : ");

			if (myLib::isContinue("\nAre You Sure You Want perform this transaction [1]:yes , [0]:no ? ")) {
				client.accontBalance += depositAmount;
				updateClientInFile(vClients,client, ::ClientsFileName);
				cout << "transaction Successfully done\n";
			}
			else {
				cout << "Ok,not done .\n";
			}
		}
		else {
			cout << "\nClient with Account Number (" << accountNumber << ") Not Found!\n";
		}

	} while (myLib::isContinue("do you want to deposit more ? yes[1] , no[0] ? "));

}

void goToWithdraw(vector < stClient>& vClients) {
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Withdraw Screen\n";
		cout << "\n-------------------------------\n\n";

		string accountNumber = inputs::readString("Please enter AccountNumber : ");
		stClient client;
		int WithdrawAmount = 0;

		if (findClientByAccountNumber(accountNumber, client, ::ClientsFileName)) {
			printClientCard(client);

			WithdrawAmount = inputs::readNumberInRange(0,client.accontBalance,"Please enter Withdraw amount : ");

			if (myLib::isContinue("\nAre You Sure You Want perform this transaction [1]:yes , [0]:no ? ")) {
				client.accontBalance -= WithdrawAmount;
				updateClientInFile(vClients, client, ::ClientsFileName);
				cout << "transaction Successfully done.\n";
			}
			else {
				cout << "Ok,not done .\n";
			}
		}
		else {
			cout << "\nClient with Account Number (" << accountNumber << ") Not Found!\n";
		}

	} while (myLib::isContinue("do you want to  do Withdraw more ? yes[1] , no[0] ? "));
}


void goToShowBalances(vector < stClient>& vClients) {
	int totalBalances = 0;
	cout << "\t\t\t\t\t" << "Client List (" << vClients.size() << ") Client(s).\n";
	cout << "\n_________________________________________________________________________________________________________\n\n";
	cout << left << setw(20) << "| Account Number " << left << setw(40) << "| Client Name " << left << setw(40) << "| Balance "<< endl;
	cout << "_________________________________________________________________________________________________________\n\n";
	for (int i = 0; i < vClients.size(); i++) {
		printBalance(vClients[i]);
		totalBalances += vClients[i].accontBalance;
	}
	cout << "_________________________________________________________________________________________________________\n";
	cout << "\n\t\t\t\t\t"<< "Total Balances = " << totalBalances << endl<<endl;

}

void goToTransactionsMenue(vector < stClient>& vClients) {

	showTransactionsMenue();	
	enTransactions tran = enTransactions(inputs::readNumberInRange(1, 4, "Choose what do you want do ? "));

	switch (tran)
	{
		case enTransactions::deposit:
		{
			system("cls");

			goToDeposit(vClients);

			backToTransactionsMenu(vClients);
			break;
		}
		case enTransactions::withdraw:
		{
			system("cls");

			goToWithdraw(vClients);

			backToTransactionsMenu(vClients);
			break;
		}
		case enTransactions::showTotalBalances:
		{
			system("cls");

			goToShowBalances(vClients);

			backToTransactionsMenu(vClients);
			break;
		}
		case enTransactions::mainMenu:
		{
			backToProgram(true);
		}
	}
}
/////////////////
void backToManageSystem(int permission) {
		cout << "Press any key to go back to main Menue ...";
		system("pause>0");
		system("cls");
		goToManageUsersMenue(permission);
}

/// ////////////////////////////

void printUser(stUser user) {
	string userName = "| " + user.userName;
	string pass = "| " + user.password;
	string per = "| " + to_string(user.permission);

	cout << left << setw(20) << userName << left << setw(15) << pass << left << setw(40) << per << endl;

}

void AddUserToFile(stUser user, string fileName) {

	string line = convertUserRecordToString(user, "#//#");
	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);

	if (myFile.is_open()) {
		myFile << line << endl;
		myFile.close();
	}
}

bool findUserByUserName(string username, vector <stUser>& vUsers, stUser &user) {
	for (stUser& u : vUsers) {
		if (u.userName == username)
		{
			user = u;
			return 1;
		}
	}
	return 0;

}


void deleteUserFromFile(stUser user, string fileName) {
	string line = convertUserRecordToString(user, "#//#");

	vector <string> vLines; loadFileToVector(fileName, vLines);

	for (string& a : vLines) {
		if (a == line) {
			a = "";
			break;
		}
	}
	LoadVectorToFile(vLines, fileName);
}

void loadUsersToFile(vector <stUser> &vUsers,string fileName) {
	vector <string> vLines;

	for (stUser& user : vUsers) {
		vLines.push_back(convertUserRecordToString(user, "#//#"));
	}
	LoadVectorToFile(vLines, fileName);
}

void updateUserInFile(stUser user,vector <stUser> & vUsers, string fileName) {
	for (stUser & u : vUsers) {
		if (user.userName == u.userName) {
			u.userName = user.userName;
			u.password = user.password;
			u.permission= user.permission;
			break;
		}
	}
	loadUsersToFile(vUsers, fileName);
}

void showUserCard(stUser user) {
	cout << "--------------------------------\n";
	cout << "Username    : " << user.userName << endl;
	cout << "password    : " << user.password << endl;
	cout << "permissions : " << user.permission << endl;
	cout << "--------------------------------\n";
}

///////////////////////
void goToListUsers(vector <stUser>& vUsers) {
	cout << "\t\t\t\t\t" << "Client List (" << vUsers.size() << ") Client(s).\n";
	cout << "\n___________________________________________________________________________\n\n";
	cout << left << setw(20) << "| User Name " << left << setw(15) << "| Password " << left << setw(40) << "| permissions " <<endl;
	cout << "___________________________________________________________________________\n\n";
	for (int i = 0; i < vUsers.size(); i++) {
		printUser(vUsers[i]);
	}
	cout << "___________________________________________________________________________\n";
}

void goToAddUser(vector <stUser>& vUsers) {
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Add New User Screen\n";
		cout << "\n-------------------------------\n";
		cout << "Adding New User : \n\n";
		stUser user;
		user = readUser(user);
		AddUserToFile(user, "users.txt");
		vUsers.push_back(user);
	} while (myLib::isContinue("User Added Successfully , do you want to add more Users ? yes[1] , no[0] ? "));
}

void goToDeleteUser(vector <stUser>& vUsers) {
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Delete User Screen\n";
		cout << "\n-------------------------------\n";	
		stUser user;
		string username = inputs::readString("Please enter usernaem : ");
		while (!findUserByUserName(username, vUsers, user)) {
			 username = inputs::readString("User not found! , Please enter usernaem again: ");
		 }
		cout << "\nThe following are the client details : \n";
		showUserCard(user);
		
		if (myLib::isContinue("Are you sure you want delete this user [1]:yes , [0]:no ? ")) {
			deleteUserFromFile(user, "users.txt");
			cout << "User Deleted Successfully ,";
		}
		else
			cout << "Ok,not deleted \n";
		vUsers = loadUsersDataFromFile("users.txt");
	} while (myLib::isContinue("Do you want to delete more Users ? yes[1], no[0] ? "));
	

}

void goToUpdateUser(vector <stUser>& vUsers) {
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Update User Screen\n";
		cout << "\n-------------------------------\n";
		stUser user;
		string username = inputs::readString("Please enter usernaem : ");
		while (!findUserByUserName(username, vUsers, user)) {
			username = inputs::readString("User not found! , Please enter usernaem again: ");
		}
		cout << "\nThe following are the client details : \n";
		showUserCard(user);

		if (myLib::isContinue("Are you sure you want update this user [1]:yes , [0]:no ? ")) {
			user = readUser(user,true);
			updateUserInFile(user,vUsers, "users.txt");
			cout << "User updated Successfully ,";
		}
		else
			cout << "Ok,not updated \n";
		
	} while (myLib::isContinue("Do you want to update more Users ? yes[1], no[0] ? "));


}

void goToFindUser(vector <stUser>& vUsers) {
	do {
		system("cls");
		cout << "\n-------------------------------\n";
		cout << "      Find User Screen\n";
		cout << "\n-------------------------------\n";
		stUser user;
		string username = inputs::readString("Please Enter UserName : ");
		if (findUserByUserName(username, vUsers, user)) {
			cout << "\nThe following are the client details : \n";
			showUserCard(user);
		}
		else
			cout << "\nUser not found !\n";

	} while (myLib::isContinue("Do you want to find more Users ? yes[1], no[0] ? "));

}

///////////////////////
void goToManageSystem(enManageOp op,int permission) {
	vector < stUser> vUsers = loadUsersDataFromFile("users.txt");
	switch (op)
	{
		case enManageOp::listUsers:
		{
			system("cls");

			goToListUsers(vUsers);

			backToManageSystem(permission);
			break;
		}
		case enManageOp::addUser:
		{
			system("cls");
			goToAddUser(vUsers);
			backToManageSystem(permission);
			break;
		}
		case enManageOp::deleteUser:
		{
			system("cls");
			goToDeleteUser(vUsers);
			backToManageSystem(permission);
			break;
		}
		case enManageOp::updateUser:
		{
			system("cls");
			goToUpdateUser(vUsers);
			backToManageSystem(permission);
			break;
		}
		case enManageOp::findUser:
		{
			system("cls");
			goToFindUser(vUsers);
			backToManageSystem(permission);
			break;
		}

		case enManageOp::mainMenue:
		{
			goToSystem(permission);
			break;
		}
	}
}

void showManageUsersMenue() {
	cout << "==================================================\n";
	cout << "\t\t\t Mange Uers Menue\n";
	cout << "==================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "==================================================\n";

}

void goToManageUsersMenue(int permission) {
	showManageUsersMenue();
	goToManageSystem(enManageOp(inputs::readNumberInRange(1, 6, "Choose What do you want to do [1,6] ? ")), permission);

}

void giveErrorAccess() {
	cout << "----------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You dont Have Permission To Do this,\n";
	cout << "Please Conact Your Admin.\n";
	cout << "----------------------------------\n\n";
}

/////////////////
void getDoOperation(enOparations oparation, int permission) {
	vector < stClient> vClients = loadClientsDataFromFile(::ClientsFileName);
	switch (oparation)
	{
		case enOparations::showClients:
		{
			system("cls");
			if (permission & int(enPermissions::pshowClients) || permission==-1)
				goToShowClients(vClients);
			else
				giveErrorAccess();

			backToProgram(permission);
			break;
		}
		case enOparations::addClient:
		{
			system("cls");
			if (permission & int(enPermissions::paddClient) || permission == -1)
				goToAddClient(vClients);
			else
				giveErrorAccess();

			backToProgram(permission);
			break;
		}
		case enOparations::deleteClient:
		{
			system("cls");
			if (permission & int(enPermissions::pdeleteClient) || permission == -1)
				goToDeleteClient(vClients);
			else
				giveErrorAccess();
			backToProgram(permission);
			break;
		}
		case enOparations::updateClient:
		{
			system("cls");
			if (permission & int(enPermissions::pupdateClient) || permission == -1)
				goToUpdateClient(vClients);
			else
				giveErrorAccess();
			backToProgram(permission);
			break;
		}
		case enOparations::findClinet:
		{
			system("cls");
				if (permission & int(enPermissions::pfindClinet) || permission == -1)
					goToFindClient(vClients);
				else
					giveErrorAccess();
			backToProgram(permission);
			break;
		}

		case enOparations::transactions:
		{
			system("cls");
			if (permission & int(enPermissions::ptransactions) || permission == -1)
				goToTransactionsMenue(vClients);
			else {
				giveErrorAccess();
				backToProgram(permission);
			}
			break;
		}
		case enOparations::manageUsers:
		{
			system("cls");
			if (permission & int(enPermissions::pmanageUsers) || permission == -1)
				goToManageUsersMenue(permission);
			else {
				giveErrorAccess();
				backToProgram(permission);
			}
			break;
		}

		case enOparations::logout: {
			system("cls");
			login();
		}
	}
}
/////////////////////////////////


void goToSystem(int permission) {
	system("cls");
	showMainMenueScreen();
	getDoOperation(enOparations(inputs::readNumberInRange(1, 8, "Choose What do you want to do [1,8] ? ")), permission);

}

void ShowloginScreen() {
	cout << "--------------------------\n";
	cout << "      Login Screen\n";
	cout << "--------------------------\n";
}


bool login() {
	string fileName = "users.txt";
	ShowloginScreen();
	string userName = inputs::readString("Enter user name  : ");
	string password = inputs::readString("Enter a password : ");

	fstream usersFile;
	usersFile.open(fileName, ios::in);

	vector <stUser> vUsers;
	vUsers = loadUsersDataFromFile(fileName);

	if (usersFile.is_open()) {
		while (true) {
			for (stUser u : vUsers) {
				if (u.userName == userName && password == u.password) {
					goToSystem(u.permission);
					return 1;
				}
			}
			system("cls");
			ShowloginScreen();
			cout << "Invalid Username or password!\n";
			userName = inputs::readString("Enter user name   : ");
			password = inputs::readString("Enter a Password  : ");

		}
	}
	return 0;

} 

///////////////////////////////////////////
int main() {

	login();

	return 0;
}