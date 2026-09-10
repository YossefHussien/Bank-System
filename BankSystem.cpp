#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdio>
#include <iomanip>
#include "MyLibrary/Input.h"
#include "MyLibrary/Math.h"
#include "MyLibrary/Output.h"
#include "MyLibrary/Validation.h"

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";



vector<string> SplitString(string S1, string Delim);

struct stUser
{

	string UserName;
	string Password;
	int Permission = 0;
	bool MarkedForDelete = false;
};

stUser CurrentUser;
enum enPermissions
{
	eAllPerms = -1,  // كل الصلاحيات
	eListUsersPerm = 1,   // 0000001
	eAddUserPerm = 4,   // 0000100
	eUpdateUserPerm = 8,   // 0001000
	eFindUserPerm = 16,  // 0010000
	eTransactionsPerm = 32,  // 0100000
	eDeleteUserPerm = 64,
	eManageUsersPerm = 128   // 1000000
};

enum enManageUserMenueOptions
{
	enListClients = 1,
	enAddClients = 2,
	enDeleteClients = 3,
	enUpdateClients = 4,
	enFindClient = 5,
	enMainMenue = 6
};

void ShowMainMenue();
void AddDataLineToFile(string FileName, string stDataLine);
void ShowManageUsersScreen();
void PerfromManageUserMenueOption(enManageUserMenueOptions ManageUserOption);
vector <stUser> LoadUsersDataFromFileForUser(string FileName);
void Login();
void GoBackToMainMenue();
void ShowAccessDeniedMessage();

bool CheckAccess(stUser User, enPermissions Permission)
{
	return (User.Permission == enPermissions::eAllPerms ||	( (User.Permission & Permission) == Permission) );
}

short ReadManageUsersMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

bool IsUserExist(string Username)
{
	vector<stUser> vUsers = LoadUsersDataFromFileForUser(UsersFileName);

	for (stUser U : vUsers)
	{
		if (U.UserName == Username)
			return true;
	}

	return false;
}

string ReadUsername()
{
	string Username = Input::ReadString("Enter Username? ");
	return Username;
}

string ReadPassword()
{
	string Password = Input::ReadString("Enter Password? ");
	return Password;
}

stUser ConvertLinetoRecordForUser(string Line, string Seperator = "#//#")
{
	stUser User;
	vector <string> vUser;

	vUser = SplitString(Line, Seperator);

	if (vUser.size() >= 3)  // ✅ تأكد إن فيه 3 عناصر
	{
		User.UserName = vUser[0];
		User.Password = vUser[1];
		User.Permission = stoi(vUser[2]);
	}


	return User;
}

string ConvertRecordToLineForUser(stUser User, string Seperator = "#//#")
{
	string stUserRecord = "";

	stUserRecord += User.UserName + Seperator;
	stUserRecord += User.Password + Seperator;
	stUserRecord += to_string(User.Permission);

	return stUserRecord;
}

vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser> vUser)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (stUser& U : vUser)
		{
			if (U.MarkedForDelete == false)
			{
				//we only write records that are not marked for

				DataLine = ConvertRecordToLineForUser(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUser;
}

void PrintUserCard(stUser User)
{
	cout << "\nThe following are the user details:\n";
	cout << "-----------------------------------";
	cout << "\nUsername    : " << User.UserName;
	cout << "\nPassword    : " << User.Password;
	cout << "\nPermissions : " << User.Permission;
	
	cout << "\n-----------------------------------\n";
}

vector <stUser> LoadUsersDataFromFileForUser(string FileName)
{
	vector <stUser> vUser;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertLinetoRecordForUser(Line);
			vUser.push_back(User);
		}
		MyFile.close();
	}
	return vUser;
}

bool FindUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
	vector <stUser> vUser = LoadUsersDataFromFileForUser(UsersFileName);

	for (stUser& U : vUser)
	{
		if (U.UserName == Username && U.Password == Password) 
		{
			User = U;
			return true;
		}
	}

	return false;
}

bool FindUserByUsername(string Username, vector <stUser>& vUsers, stUser& User)
{
	vector <stUser> vUser = LoadUsersDataFromFileForUser(UsersFileName);

	for (stUser& U : vUser)
	{
		if (U.UserName == Username )
		{
			User = U;
			return true;
		}
	}

	return false;
}

void PrintLoginScreen()
{
	cout << "-----------------------------------\n";
	cout << "           Login Screen\n";
	cout << "-----------------------------------\n";
}

void ShowLoginScreen()
{
	PrintLoginScreen();

	stUser User;
	vector <stUser> vUser;
	string Username, Password;

	Username = ReadUsername();
	Password = ReadPassword();

	
	while (!FindUserByUsernameAndPassword(Username, Password, CurrentUser))
	
	{
		system("cls");
		PrintLoginScreen();
		cout << "Invalid Username/Password!\n";

		Username = ReadUsername();
		Password = ReadPassword();

	}


	ShowMainMenue();



}


int SetPermissionsForUser()
{
	char Choice = 'n';
	int Permissions = 0;

	cout << "Do you want to give full access? Y/N? ";
	cin >> Choice;
	if ('y' == tolower(Choice))
	{
		return -1;
	}

	cout << "\nSet Permissions:\n";

	cout << "Show Client List? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eListUsersPerm;

	cout << "Add Clients? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eAddUserPerm;

	cout << "Delete Clients? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eDeleteUserPerm;

	cout << "Update Clients? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eUpdateUserPerm;

	cout << "Find Clients? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eFindUserPerm;

	cout << "Transactions? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eTransactionsPerm;

	cout << "Manage Users? y/n? ";
	cin >> Choice;
	if (tolower(Choice) == 'y')
		Permissions += enPermissions::eManageUsersPerm;

	return Permissions;
}

stUser ReadNewUser()
{
	char Access;
	stUser User;
	cout << "Enter Username? ";
	getline(cin >> ws, User.UserName);

	while (IsUserExist(User.UserName))
	{
		cout << "\nUser with [" << User.UserName << "] already exists, Enter another Username? ";
		getline(cin >> ws, User.UserName);
	}

	cout << "\nEnter Password? ";
	getline(cin >> ws, User.Password);

	cout << "Do you want to give full access? y/n?";
	cin >> Access;

	if (tolower(Access) == 'y')
	{
		User.Permission = -1;
	}
	else 
	{
		User.Permission = SetPermissionsForUser();
	}


	return User;
}

void AddNewUser()
{
	stUser User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertRecordToLineForUser(User));
}

void AddNewUsers()
{
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "Adding New User:\n\n";
		AddNewUser();
		cout << "\User Added Successfully, do you want to add more Users ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void PrintUserRecordLine(stUser User)
{
	cout << "| " << setw(20) << left << User.UserName;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(10) << left << User.Permission;
}

void ShowAllUsersScreen()
{


	vector <stUser> vUser = LoadUsersDataFromFileForUser(UsersFileName);
	cout << "\n\t\t\t\t\User List (" << vUser.size() << ") User(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(10) << "Permissions";

	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vUser.size() == 0)
		cout << "\t\t\t\tNo Users Available In the System!";
	else
		for (stUser U : vUser)
		{
			PrintUserRecordLine(U);
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowAddNewUserScreen()
{
	cout << "--------------------------------------------------\n";
	cout << "             Add New User Screen\n";
	cout << "--------------------------------------------------\n";
	AddNewUsers();
}

void ShowManageUsersMenue()
{
	if (!CheckAccess(CurrentUser, enPermissions::eManageUsersPerm))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;  
	}

	system("cls");
	cout << "============================================================\n";
	cout << "             Manage Users Menue Screen\n";
	cout << "============================================================\n";
	cout << "[1] List Users.\n";
	cout << "[2] Add New User.\n";
	cout << "[3] Delete User\n";
	cout << "[4] Update User\n";
	cout << "[5] Find User.\n";
	cout << "[6] Main Menue.\n";
	cout << "============================================================\n";
	PerfromManageUserMenueOption((enManageUserMenueOptions)ReadManageUsersMenueOption());


}

void GoBackToManageUsersMenue()
{

	cout << "\n\nPress any key to go back to Manage Users Menue...";
	system("pause>0");
	ShowManageUsersMenue();
}

bool MarkUserForDeleteByUsername(string Username, vector <stUser>& vUser)
{
	for (stUser& U : vUser)
	{
		if (U.UserName == Username)
		{
			U.MarkedForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteUserByUsername(string Username, vector<stUser>& vUser)
{
	stUser User;
	char Answer = 'n';
	if (Username == "Admin")
	{
		cout << "\nYou Cannot Delete This User.\n";
		return false;
	}
	if (FindUserByUsername(Username, vUser, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want delete this user? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserForDeleteByUsername(Username, vUser);
			SaveUsersDataToFile(UsersFileName, vUser);
			//Refresh USers
			vUser = LoadUsersDataFromFileForUser(UsersFileName);
			cout << "\n\User Deleted Successfully.";
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Username (" << Username << ") is Not Found!";
		return false;
	}
}

void ShowDeleteUserScreen()
{
	cout << "----------------------------------------------------\n";
	cout << "               Delete User Screen\n";
	cout << "----------------------------------------------------\n";
	vector <stUser> vUser = LoadUsersDataFromFileForUser(UsersFileName);
	string Username = ReadUsername();
	DeleteUserByUsername(Username, vUser);
	
}

void FindUser()
{



	vector <stUser> vUser;
	stUser User;

	string Username = ReadUsername();
	if (FindUserByUsername(Username, vUser, User))
	{
		cout << "User [" << Username << "] was found : \n\n";
		PrintUserCard(User);
	}
	else
	{
		cout << "User [" << Username << "] was not found. \n\n";
	}


}

void FindUserScreen()
{
	cout << "--------------------------------------------------\n";
	cout << "            Find User Screen\n";
	cout << "--------------------------------------------------\n";

	char Answer = 'n';

	do 
	{
		FindUser();
		cout << "Do you want to search for another user? Y/N";
		cin >> Answer;
	} while ('Y' == toupper(Answer));
}

stUser ChangeUserRecord(string Username)
{
	stUser User;
	char Access = 'n';

	User.Password = ReadPassword();
	User.UserName = Username;
	cout << "Do you want to give full access? y/n?";
	cin >> Access;

	if (tolower(Access) == 'y')
	{
		User.Permission = -1;
	}
	else
	{
		User.Permission = SetPermissionsForUser();
	}

	return User;
}

bool UpdateUserByUsername(string Username, vector <stUser>& vUser)
{
	
	stUser User;
	char Answer = 'n';
	if (FindUserByUsername(Username, vUser, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want update this User)? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stUser& U : vUser)
			{
				if (U.UserName == Username)
				{
					U = ChangeUserRecord(Username);
					break;
				}
			}
			SaveUsersDataToFile(UsersFileName, vUser);
			cout << "\n\User Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\User with Username (" << Username << ") is Not Found!";
		return false;
	}
}

void ShowUpdateUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate User Info Screen";
	cout << "\n-----------------------------------\n";


	vector <stUser> vUser = LoadUsersDataFromFileForUser(UsersFileName);
	string Username = ReadUsername();
	UpdateUserByUsername(Username, vUser);
}

void PerfromManageUserMenueOption(enManageUserMenueOptions ManageUserOption)
{
	switch (ManageUserOption)
	{
	case enManageUserMenueOptions::enListClients:
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageUsersMenue();
		break;
	case enManageUserMenueOptions::enAddClients:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageUsersMenue();
		break;
	case enManageUserMenueOptions::enDeleteClients:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenue();
		break;
	case enManageUserMenueOptions::enFindClient:
		system("cls");
		FindUserScreen();
		GoBackToManageUsersMenue();
		break;
	case enManageUserMenueOptions::enUpdateClients:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUsersMenue();
		break;
	case enManageUserMenueOptions::enMainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}



}







struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};


vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length()); /* erase() until
		positon and move to next word. */
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber,
		ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
			getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	if (!CheckAccess(CurrentUser, enPermissions::eListUsersPerm))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients =
		LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (sClient Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient>& vClients, sClient& Client)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for
				
					DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName,
		ConvertRecordToLine(Client));
}

void AddNewClients()
{

	if (!CheckAccess(CurrentUser, enPermissions::eAddUserPerm))
	{
		ShowAccessDeniedMessage();
		return;
	}
	char AddMore = 'Y';
	do
	{
		//system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
			cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n? ";
			cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber,
				vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
			cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	if (!CheckAccess(CurrentUser, enPermissions::eDeleteUserPerm))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
	if (!CheckAccess(CurrentUser, enPermissions::eUpdateUserPerm))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";
	AddNewClients();
}

void ShowFindClientScreen()
{
	if (!CheckAccess(CurrentUser, enPermissions::eFindUserPerm))
	{
		ShowAccessDeniedMessage();
		return;
	}


	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients,	Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber
		<< "] is not found!";
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void PrintClientRecordLineShortCut(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreenShortCut()
{
	vector <sClient> vClients =
		LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (sClient Client : vClients)
		{
			PrintClientRecordLineShortCut(Client);
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

enum enTransactionMenuOptions
{
	eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eMainMenu = 4

};

short ReadTransactionnOption()
{
	short Option = Input::ReadNumberInRange("Choose what do you want to do? [ 1 to 4]?", 1, 4);
	return Option;
}

void DepositeMoney()
{
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	sClient Client;
	double DepositAmount = 0;

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		char Answer;
		PrintClientCard(Client);
		DepositAmount = Input::ReadPositiveNumber("Please enter deposite amount?");

		Answer = Input::ReadCharacter("Are you sure you want to perform this transaction? y/n? ");

		if (Answer == 'Y' || Answer == 'y') {
			
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance += DepositAmount;
					cout << "\n\nDeposit Successful. New Balance is : " << C.AccountBalance << endl;
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClient);
			vClient = LoadCleintsDataFromFile(ClientsFileName);

			
		}
		
	}
	else
	{
		cout << "Client with [" << AccountNumber << "] does not exist.\n";
	}
}

void ShowDepositeMoneyScreen()
{
	cout << "-------------------------------------\n";
	cout << "          Deposite Screen \n";
	cout << "-------------------------------------\n";
	DepositeMoney();
}

void GoBackToTransactionMenue();

double CalcClientsTotalBalances()
{
	vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	double TotalBalance = 0;

	for(sClient& C : vClient)
	{
		TotalBalance += C.AccountBalance;

	}
	return TotalBalance;
}

void ShowTotalBalanceScreen()
{
	cout << "                                     Total Balances : " << CalcClientsTotalBalances();

}

void WithDrawMoney()
{
	vector < sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);

	string AccountNumber = ReadClientAccountNumber();
	char Answer = 'n';
	sClient Client;
	double WithDrawAmount = 0;
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);
		
	
		for (sClient& C : vClient)
		{

			if (C.AccountNumber == AccountNumber)
			{

				WithDrawAmount = (double)Input::ReadPositiveNumber("Please enter withdraw amount ? ");

				while (WithDrawAmount > C.AccountBalance)
				{
					cout << "Amount Exceeds the balance, you can withdraw up to : " << C.AccountBalance;
					WithDrawAmount = (double)Input::ReadNumberInRange("\nPlease enter another amount", 0, C.AccountBalance);
				}


				Answer = Input::ReadCharacter("\nAre you sure you want to perform this transaction? y/n? ");
				if (Answer == 'Y' || Answer == 'y')
				{
					C.AccountBalance -= WithDrawAmount;
					cout << "\nWithdrawed Sucessfully. New Balance is : " << C.AccountBalance << endl;;
				}

			}

		}
		
		SaveCleintsDataToFile(ClientsFileName, vClient);
		vClient = LoadCleintsDataFromFile(ClientsFileName);
	}
	else
	{
		cout << "Client with [" << AccountNumber << "] does not exist.\n";
	}
}

void ShowWithDrawMoneyScreen()
{
	cout << "-------------------------------------\n";
	cout << "          WithDraw Screen \n";
	cout << "-------------------------------------\n";
	WithDrawMoney();

}

void PerformTransactionMenueOption(enTransactionMenuOptions TransactionOption)
{
	switch (TransactionOption)
	{

	case enTransactionMenuOptions::eMainMenu:
		ShowMainMenue();
		break;

	case enTransactionMenuOptions::eDeposit:
		system("cls");
		ShowDepositeMoneyScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionMenuOptions::eShowTotalBalance:
		system("cls");
		ShowAllClientsScreenShortCut();
		ShowTotalBalanceScreen();
		GoBackToMainMenue();
		break;

	case enTransactionMenuOptions::eWithdraw:
		system("cls");
		ShowWithDrawMoneyScreen();
		GoBackToMainMenue();
		break;

	}



}

void ShowTransactionMenu()
{
	if (!CheckAccess(CurrentUser, enPermissions::eTransactionsPerm))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}


	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransaction Menue Screen\n";
	cout << "===========================================\n";
	cout << "[1] Deposit.\n";
	cout << "[2] Withdraw\n";
	cout << "[3] Total Balance\n";
	cout << "[4] Main Menue\n";
	cout << "===========================================\n";
	PerformTransactionMenueOption((enTransactionMenuOptions)ReadTransactionnOption());
}

void GoBackToTransactionMenue()
{
	cout << "\n\nPress any key to go back to Transaction Menue...";
	system("pause>0");
	ShowTransactionMenu();
}

enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionMenue = 6 , eManageUsers = 7, eExit = 8
};

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void ShowAccessDeniedMessage()
{
	system("cls");
	cout << "----------------------------------------------------";
	cout << "\nAccess Denied,\n";
	cout << "You Dont Have Permission To Do This.\n";
	cout << "Please Contact Your Admin.\n";
	cout << "----------------------------------------------------\n";
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eShowTransactionMenue:
		system("cls");
		ShowTransactionMenu();
		break;
	case enMainMenueOptions::eManageUsers:
		system("cls");
		ShowManageUsersMenue();
		break;
	case enMainMenueOptions::eExit:
		Login();
		break;
	}
}

void ShowMainMenue()
{
	system("cls");

	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions. \n";
	cout << "\t[7] Manage Users. \n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

void Login()
{
	ShowLoginScreen();
}

int main()
{
	Login();

	system("pause>0");
	return 0;
}                                                                 