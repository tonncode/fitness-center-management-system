#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Admin
{
	private:
		int adminid;
		string firstname;
		string lastname;
		string username;
		string password;
	public:
		Admin() : adminid(0), firstname(""), lastname(""), username(""), password("")
		{}
		void setData(int id, string fname, string lname, string username, string password);
		void firstadmin();
		int logIn(string username, string password, Admin* admin[]);
		bool checkId(int id, Admin* admin[]);
		void registerAdmin(Admin* admin[]);
		int idGenerator(Admin* admin[]);
		void save(Admin* admin[]);
};

class Member
{
	private:
		int memberid;
		string firstname;
		string lastname;
		string username;
		string password;
	public:
		Member() : memberid(0), firstname(""), lastname(""), username(""), password("")
		{}
		void setData(int id, string fname, string lname, string username, string password);
		int logIn(string username, string password, Member* member[]);
		bool checkId(int id, Member* member[]);
		void registerMember(Member* member[]);
		int idGenerator(Member* member[]);
		void save(Member* member[]);
};

class Fitness
{
	private:
		int classid;
		string classname;
		string classdate;
		string classtime;
		int capacity;
		int roomnumber;
		int* memberslist;
	public:
		Fitness() : classid(0), memberslist(NULL), classname(), classdate(), classtime(), capacity(0), roomnumber(0)
		{}
		void addFitnessClass(Fitness* fitness[]);
		bool checkId(string sid, Fitness* fitness[]);
		void deleteFitnessClass(Fitness* fitness[]);
		void display(Fitness* fitness[]);
		void updateClassDetails(Fitness* fitness[]);
		void viewClassesWithVacancies(Fitness* fitness[]);
		void save(Fitness* fitness[]);
		void bookAClass(int memberid, Fitness* fitness[]);
		void bookedclasses(int memberid, Fitness* fitness[]);
		void cancelBooking(int memberid, Fitness* fitness[]);
};

void logOut(bool& access, int& id, string& category, string& username)
{
	string exit;
	cout<<"Are you sure you want to log out? [press 'y' to logout][press any key to not logout]"<<endl;
	cin>>exit;
	if (exit == "y")
	{
		access = false;
		id = 0;
		category = "empty";
		username = "empty";
		cout<<"to continue you need to login"<<endl;
		cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
	}
}

int auth(bool& access, string& category, string& username, Admin* admin[], Member* member[], Admin adminN, Member memberR)
{
	string password;

	cout<<"Please enter the category of your account before logging in: [admin/member]"<<endl;
	cin>>category;
	cout<<"Please enter your username: "<<endl;
	cin>>username;
	cout<<"Please enter your password: "<<endl;
	cin>>password;

	if (category == "admin")
	{
		int id = adminN.logIn(username, password, admin);
		if (id != 0)
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"You have logged in successfuly!"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
			access = true;
			return id;
		}
	}
	else if (category == "member")
	{
		int id = memberR.logIn(username, password, member);
		if (id != 0)
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"You have logged in successfuly!"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
			access = true;
			return id;
		}
	}
	cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
	cout<<"Error: Invalid username or password or category entered"<<endl<<endl;
	return 0;
}

void Admin::setData(int id, string fname, string lname, string user, string pass)
{
	adminid = id;
	firstname = fname;
	lastname = lname;
	username = user;
	password = pass;
}

int Admin::logIn(string username, string password, Admin* admin[])
{
	for (int i = 0; i < sizeof(*admin); ++i)
	{
		if (admin[i] != NULL)
		{
			if (admin[i]->username == username && admin[i]->password == password)
			{
				return admin[i]->adminid;
			}
		}
	}
	return 0;
}

int Member::logIn(string username, string password, Member* member[])
{

	for (int i = 0; i < sizeof(*member); ++i)
	{
		if (member[i] != NULL)
		{
			if (member[i]->username == username && member[i]->password == password)
			{
				return member[i]->memberid;
			}
		}
	}
	return 0;
}


void quitProgram(int& id, bool& access, Admin* admin[], Member* member[], Fitness* fitness[], Admin adminN, Member memberR, Fitness fitnessS)
{
	id = 0;
	access = true;
	adminN.save(admin);
	memberR.save(member);
	fitnessS.save(fitness);
	cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
	cout<<"Records[admin(s), member(s), fitness class(es)] are saved - AdminsTable.txt, MembersTable.txt, FitnessClassesTable.txt"<<endl;
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
}

int main()
{
	Admin adminN;
	Member memberR;
	Fitness fitnessS;
	srand(time(0));
	Admin** admin = new Admin *[10];
	Member** member = new Member *[10];
	Fitness** fitness = new Fitness *[10];
	for (int i = 0; i < sizeof(*admin); ++i)
	{
		admin[i] = NULL;
	}
	for (int i = 0; i < sizeof(*member); ++i)
	{
		member[i] = NULL;
	}
	for (int i = 0; i < sizeof(*fitness); ++i)
	{
		fitness[i] = NULL;
	}
	admin[0] = new Admin;
	admin[0]->setData(1, "admin", "admin", "admin1", "admin1");
	bool access = false;
	string category, username;
	int id, actionNumber, not_int_error = 0;
	string sactionNumber;

	cout<<"Welcome to the fitness management system!"<<endl<<endl;

	do
	{
		id = auth(access, category, username, admin, member, adminN, memberR);

		while(id != 0)
		{
			if (category == "admin")
			{
				not_int_error = 0;
				cout<<"Category: "<<category<<endl;
				cout<<"Username: "<<username<<endl<<endl;
				cout<<"The list of available operations for Admins:"<<endl;
				cout<<"1) Register a new Admin"<<endl;
				cout<<"2) Register a new member"<<endl;
				cout<<"3) Add a fitness class"<<endl;
				cout<<"4) Delete a fitness class"<<endl;
				cout<<"5) Update the details of a fitness class"<<endl;
				cout<<"6) Display the Classes With Vacancies"<<endl;
				cout<<"7) Log Out"<<endl;
				cout<<"8) Save and Quit the program"<<endl;
				cout<<endl;
				cout<<"Enter the number of the required action: [1-8]"<<endl;

				cin>>sactionNumber;
				cout<<endl;

				int slactionNumber = sactionNumber.length();
				for (int i = 0; i < slactionNumber; ++i)
				{
					if (!isdigit(sactionNumber[i]))
					{
						not_int_error = 1;
					}
				}

				if (not_int_error == 0)
				{
					actionNumber = stoi(sactionNumber);

					if(actionNumber == 1)
					{
						adminN.registerAdmin(admin);
						actionNumber = 0;
						not_int_error = 0;
					}
					else if (actionNumber == 2)
					{
						memberR.registerMember(member);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
					}
					else if (actionNumber == 3)
					{
						fitnessS.addFitnessClass(fitness);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
					}
					else if (actionNumber == 4)
					{
						fitnessS.deleteFitnessClass(fitness);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
					}
					else if (actionNumber == 5)
					{
						fitnessS.updateClassDetails(fitness);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
					}
					else if (actionNumber == 6)
					{
						fitnessS.viewClassesWithVacancies(fitness);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
					}
					else if (actionNumber == 7)
					{
						logOut(access, id, category, username);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
					}
					else if (actionNumber == 8)
					{	
						quitProgram(id, access, admin, member, fitness, adminN, memberR, fitnessS);
						actionNumber = 0;
						not_int_error = 0;
						sactionNumber = "";
						slactionNumber = 0;
						for (int i = 0; i < sizeof(*admin); ++i)
						{
							admin[i] = NULL;
							delete admin[i];
						}
						for (int i = 0; i < sizeof(*member); ++i)
						{
							member[i] = NULL;
							delete member[i];
						}
						for (int i = 0; i < sizeof(*fitness); ++i)
						{
							fitness[i] = NULL;
							delete fitness[i];
						}
						delete [] admin;
						delete [] member;
						delete [] fitness;
					}
					else
					{
						cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
						cout<<"Error: action number out of range [1-6]!"<<endl<<endl;
					}
				}
				else if(not_int_error == 1)
				{
					cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
					cout<<"Error: invalid action number entered!"<<endl<<endl;
				}
			}
			else if (category == "member")
			{
				not_int_error = 0;

				cout<<endl<<endl;
				cout<<"The list of available operations for members:"<<endl;
				cout<<"1) Display the Classes With Vacancies"<<endl;
				cout<<"2) Display the Classes booked by me"<<endl;
				cout<<"3) Book a fitness class"<<endl;
				cout<<"4) Cancel booking"<<endl;
				cout<<"5) Log Out"<<endl;
				cout<<"6) Save and Quit the program"<<endl;
				cout<<endl;
				cout<<"Enter the number of the required action: [1-5]"<<endl;

				cin>>sactionNumber;
				cout<<endl;

				int slactionNumber = sactionNumber.length();
				for (int i = 0; i < slactionNumber; ++i)
				{
					if (!isdigit(sactionNumber[i]))
					{
						not_int_error = 1;
					}
				}

				if (not_int_error == 0)
				{
					actionNumber = stoi(sactionNumber);

					if(actionNumber == 1)
					{
						fitnessS.viewClassesWithVacancies(fitness);
						actionNumber = 0;
						not_int_error = 0;
					}
					else if(actionNumber == 2)
					{
						fitnessS.bookedclasses(id, fitness);
						actionNumber = 0;
						not_int_error = 0;
					}
					else if (actionNumber == 3)
					{
						fitnessS.bookAClass(id, fitness);
						actionNumber = 0;
						not_int_error = 0;
					}
					else if (actionNumber == 4)
					{
						fitnessS.cancelBooking(id, fitness);
						actionNumber = 0;
						not_int_error = 0;
					}
					else if (actionNumber == 5)
					{
						logOut(access, id, category, username);
						actionNumber = 0;
						not_int_error = 0;
					}
					else if (actionNumber == 6)
					{
						quitProgram(id, access, admin, member, fitness, adminN, memberR, fitnessS);
						actionNumber = 0;
						not_int_error = 0;
						for (int i = 0; i < sizeof(*admin); ++i)
						{
							admin[i] = NULL;
							delete admin[i];
						}
						for (int i = 0; i < sizeof(*member); ++i)
						{
							member[i] = NULL;
							delete member[i];
						}
						for (int i = 0; i < sizeof(*fitness); ++i)
						{
							fitness[i] = NULL;
							delete fitness[i];
						}
						delete [] admin;
						delete [] member;
						delete [] fitness;
					}		
					else
					{
						cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
						cout<<"Error: action number out of range [1-6]!"<<endl;
						cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
					}
				}
				else
				{
					cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
					cout<<"Error: invalid action number entered!"<<endl;
					cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
				}
			}
		}
	}
	while(!access);
	return 0;
}

void Admin::save(Admin* admin[])
{
	Admin* ptr = new Admin; 	
	ofstream fout("AdminsTable.txt"); 
	if (fout.is_open())
	{
		for (int i = 0; i < sizeof(*admin); ++i)
		{
			ptr = admin[i];
			if (ptr != NULL)
			{
				fout<<ptr->adminid<<","<<ptr->firstname<<","<<ptr->lastname<<","<<ptr->username<<","<<ptr->password<<endl;
			}
		}
	}
	ptr = NULL;
	delete ptr;
}

void Member::save(Member* member[])
{
	Member* ptr = new Member; 	
	ofstream fout("MembersTable.txt"); 
	if (fout.is_open())
	{
		for (int i = 0; i < sizeof(*member); ++i)
		{
			ptr = member[i];
			if (ptr != NULL)
			{
				fout<<ptr->memberid<<","<<ptr->firstname<<","<<ptr->lastname<<","<<ptr->username<<","<<ptr->password<<endl;
			}
		}
	}
	ptr = NULL;
	delete ptr;
}

void Fitness::save(Fitness* fitness[])
{
	Fitness* ptr = new Fitness; 	
	ofstream fout("FitnessClassesTable.txt"); 
	if (fout.is_open())
	{
		for (int i = 0; i < sizeof(*fitness); ++i)
		{
			ptr = fitness[i];
			if (ptr != NULL)
			{
				fout<<ptr->classid<<","<<ptr->classname<<","<<ptr->classdate<<","<<ptr->classtime<<","<<ptr->capacity<<ptr->roomnumber<<endl;
			}
		}
	}
	ptr = NULL;
	delete ptr;
}


bool Admin::checkId(int newid, Admin* admin[])
{
	Admin* ptr = new Admin;
	for (int i = 0; i < sizeof(*admin); ++i)
	{
		if (admin[i] != NULL)
		{
			ptr = admin[i];
			if (ptr->adminid == newid)
			{
				ptr = NULL;
				delete ptr;
				return true;
			}
		}
		ptr = NULL;
		delete ptr;
	}
	ptr = NULL;
	delete ptr;
	return false;
}
//====================================
int Admin::idGenerator(Admin* admin[])
{
	int unique = 0;
	int newid = 0;
	while(unique == 0)
	{
		unique = 1;
		newid = rand()%9000 + 1000;
		if (checkId(newid, admin))
		{
			unique = 0;
		}
	}
	return newid;
}

void Admin::registerAdmin(Admin* admin[])
{
	string fname, lname;
	do
	{
		cout<<"Firstname: ";
		cin>>fname;
		if (fname.length() <= 1)
		{
			cout<<"Firstname cannot be only 1 character"<<endl;
		}
	}
	while(fname.length() <= 1);

	do
	{
		cout<<"Lastname: ";
		cin>>lname;
		if (lname.length() <= 1)
		{
			cout<<"Lastname cannot be only 1 character"<<endl;
		}
	}
	while(lname.length() <= 1);

	Admin* u = new Admin;
	int id = idGenerator(admin);

	for (int i = 0; i < fname.length(); ++i)
	{
		fname[i] = tolower(fname[i]);
	}
	for (int i = 0; i < lname.length(); ++i)
	{
		lname[i] = tolower(lname[i]);
	}

	int p_rand = rand()%9000 + 1000;
	string username = fname + to_string(id);
	string password = lname + to_string(p_rand);
	for (int i = 0; i < sizeof(*admin); ++i)
	{
		if (admin[i] == NULL)
		{
			admin[i] = new Admin;
			u = admin[i];
			u->adminid = id;
			u->firstname = fname;
			u->lastname = lname;
			u->username = username;
			u->password = password;
			break;
		}
	}
	cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
	cout<<"New admin is successfuly registered! Info:"<<endl;
	cout<<"id: "<<u->adminid<<endl;
	cout<<"Firstname: "<<u->firstname<<endl;
	cout<<"Lastname: "<<u->lastname<<endl;
	cout<<"Username: "<<u->username<<endl;
	cout<<"Password: "<<u->password<<endl;
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
}

bool Member::checkId(int newid, Member* member[])
{
	Member* ptr = new Member;
	for (int i = 0; i < sizeof(*member); ++i)
	{
		ptr = member[i];
		if (member[i] != NULL)
		{
			ptr = member[i];
			if (ptr->memberid == newid)
			{
				ptr = NULL;
				delete ptr;
				return true;
			}
		}
		ptr = NULL;
		delete ptr;
	}
	ptr = NULL;
	delete ptr;
	return false;
}
//====================================
int Member::idGenerator(Member* member[])
{
	int unique = 0;
	int newid = 0;
	while(unique == 0)
	{
		unique = 1;
		newid = rand()%9000 + 1000;
		if (checkId(newid, member))
		{
			unique = 0;
		}
	}
	return newid;
}
//====================================
void Member::registerMember(Member* member[])
{
	Member* u = new Member;
	int id = idGenerator(member);
	string fname, lname;
	do
	{
		cout<<"Firstname: ";
		cin>>fname;
		if (fname.length() <= 1)
		{
			cout<<"Firstname cannot be only 1 character"<<endl;
		}
	}
	while(fname.length() <= 1);

	do
	{
		cout<<"Lastname: ";
		cin>>lname;
		if (lname.length() <= 1)
		{
			cout<<"Lastname cannot be only 1 character"<<endl;
		}
	}
	while(lname.length() <= 1);
	
	for (int i = 0; i < fname.length(); ++i)
	{
		fname[i] = tolower(fname[i]);
	}
	for (int i = 0; i < lname.length(); ++i)
	{
		lname[i] = tolower(lname[i]);
	}

	int p_rand = rand()%9000 + 1000;
	string username = fname + to_string(id);
	string password = lname + to_string(p_rand);
	for (int i = 0; i < sizeof(*member); ++i)
	{
		if (member[i] == NULL)
		{
			member[i] = new Member;
			u = member[i];
			u->memberid = id;
			u->firstname = fname;
			u->lastname = lname;
			u->username = username;
			u->password = password;
			break;
		}
	}
	cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
	cout<<"New member is successfuly registered! Info:"<<endl;
	cout<<"id: "<<u->memberid<<endl;
	cout<<"Firstname: "<<u->firstname<<endl;
	cout<<"Lastname: "<<u->lastname<<endl;
	cout<<"Username: "<<u->username<<endl;
	cout<<"Password: "<<u->password<<endl;
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
}

bool Fitness::checkId(string sid, Fitness* fitness[])
{
	Fitness* ptr = new Fitness;
	int int_length = sid.length();

	for (int i = 0; i < int_length; ++i)
	{
		if (!isdigit(sid[i]))
		{
			ptr = NULL;
			delete ptr;
			cout<<"Error: ID consists only integers"<<endl;
			return true;
		}
	}

	int id = stoi(sid);

	for (int i = 0; i < sizeof(*fitness); ++i)
	{
		ptr = fitness[i];
		if (ptr != NULL && ptr->classid == id)
		{
			ptr = NULL;
			delete ptr;
			cout<<"Error: A class with the same id already exists"<<endl;
			return true;
		}
	}
	ptr = NULL;
	delete ptr;
	return false;
}

void Fitness::addFitnessClass(Fitness* fitness[])
{
	string sid,smax,sroom;
	string name,date,time;
	do
	{
		cout<<"Class ID: ";
		cin>>sid;
	}
	while(checkId(sid, fitness));

	int addid = stoi(sid);

	do
	{
		cout<<"Class Name: ";
		cin>>name;
		if (name.length() <= 1)
		{
			cout<<"Error: Class Name cannot be only 1 character"<<endl;
		}
	}
	while(name.length() <= 1);
	int date_check = 1;
	do
	{
		date_check = 1;
		cout<<"Class date(dd-mm-yy): ";
		cin>>date;
		if (date.length() != 8 || date[2] != '-' || date[5] != '-')
		{
			cout<<"Error: invalid date(dd-mm-yy)"<<endl;
			date_check = 0;

		}
		else if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[3]) || !isdigit(date[4]) || !isdigit(date[6]) || !isdigit(date[7]))
		{
			cout<<"Error: invalid date(dd-mm-yy)"<<endl;
			date_check = 0;
		}
	}
	while(date_check == 0);
	int time_check = 1;
	do
	{
		time_check = 1;
		cout<<"Class time(16:00): ";
		cin>>time;
		if (time.length() != 5 || time[2] != ':')
		{
			cout<<"Error: invalid time(hh:mm, 16:00)"<<endl;
			time_check = 0;

		}
		else if (!isdigit(time[0]) || !isdigit(time[1]) || !isdigit(time[3]) || !isdigit(time[4]))
		{
			cout<<"Error: invalid time(hh:mm, 16:00)"<<endl;
			time_check = 0;
		}
	}
	while(time_check == 0);

	int max_check = 1;
	do
	{
		max_check = 1;
		cout<<"Maximum capacity: ";
		cin>>smax;
		int int_length = smax.length();
		for (int i = 0; i < int_length; ++i)
		{
			if (!isdigit(smax[i]))
			{
				max_check = 0;
				cout<<"Error: capacity consists only integers"<<endl;
				break;
			}
		}
	}
	while(max_check == 0);
	int max = stoi(smax);

	int room_check = 1;
	do
	{
		room_check = 1;
		cout<<"Room Number: ";
		cin>>sroom;
		int sroom_length = sroom.length();
		for (int i = 0; i < sroom_length; ++i)
		{
			if (!isdigit(sroom[i]))
			{
				room_check = 0;
				cout<<"Error: roomnumber consists only integers"<<endl;
				break;
			}
		}
	}
	while(room_check == 0);
	int room = stoi(sroom);

	Fitness* u = new Fitness;
	u->classid = addid;
	u->classname = name;
	u->classdate = date;
	u->classtime = time;
	u->capacity = max;
	u->roomnumber = room;
	u->memberslist = new int[max];
	for (int i = 0; i < max; ++i)
	{
		u->memberslist[i] = 0;
	}
	for (int i = 0; i < sizeof(*fitness); ++i)
	{
		if (fitness[i] == NULL)
		{
			fitness[i] = u;
			break;
		}
	}
	cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
	cout<<"New Fitness Class is successfuly added!"<<endl;
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
}


void Fitness::display(Fitness* fitness[])
{
	cout<<"All fitness classes with detailed information:"<<endl;
	Fitness* ptr = new Fitness;
	int a = 1;
	for (int i = 0; i < sizeof(*fitness); ++i)
	{
		ptr = fitness[i];
		if (ptr != NULL)
		{
			cout<<"----------------------------------------"<<endl;
			cout<<a<<")id: "<<ptr->classid<<endl;
			cout<<" Class Name: "<<ptr->classname<<endl;
			cout<<" Class date: "<<ptr->classdate<<endl;
			cout<<" Class time: "<<ptr->classtime<<endl;
			cout<<" Maximum capacity: "<<ptr->capacity<<endl;
			cout<<" Room Number: "<<ptr->roomnumber<<endl;
			cout<<"----------------------------------------"<<endl;
			a = a + 1;
		}	
	}
	ptr = NULL;
	delete ptr;
}

void Fitness::deleteFitnessClass(Fitness* fitness[])
{
	string sdeleteid;
	int not_int_error = 0;
	int deleteid, deleted = 0;
	Fitness* ptr = new Fitness;
	display(fitness);
	cout<<endl;
	cout<<"Enter id class to delete: ";
	cin>>sdeleteid;
	int sldeleteid = sdeleteid.length();
	for (int i = 0; i < sldeleteid; ++i)
	{
		if (!isdigit(sdeleteid[i]))
		{
			not_int_error = 1;
		}
	}
	if (not_int_error == 0)
	{
		deleteid = stoi(sdeleteid);
		for (int i = 0; i < sizeof(*fitness); ++i)
		{
			ptr = fitness[i];
			if (ptr != NULL && ptr->classid == deleteid)
			{
				deleted = 1;
				fitness[i] = NULL;
				cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
				cout<<"Fitness Class with "<<deleteid<<" is successfuly deleted!"<<endl;
				cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
				break;
			}
		}
		if (deleted == 0)
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"Error: No Fitness Class with id "<<deleteid<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
		}
	}
	else
	{
		cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
		cout<<"Error: invalid id entered"<<endl;
		cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
	}
	ptr = NULL;
	delete ptr;
}

void Fitness::updateClassDetails(Fitness* fitness[])
{
	string supdateid;
	string datamember;
	string newdata;
	int classfound = 0;
	int not_int_error = 0, wrong_datamember = 0;
	int updateid, updated = 0;
	Fitness* ptr = new Fitness;
	display(fitness);
	cout<<"Enter id of a Fitness Class to update: ";
	cin>>supdateid;
	cout<<"Enter data member you want to update: [name/capacity/room/date/time] (capacity change will lead to deleting all records about members)"<<endl;
	cin>>datamember;

	int slupdateid = supdateid.length();
	for (int i = 0; i < slupdateid; ++i)
	{
		if (!isdigit(supdateid[i]))
		{
			not_int_error = 1;
		}
	}
	if (datamember != "name" && datamember != "capacity" && datamember != "room" && datamember != "date" && datamember != "time")
	{
		wrong_datamember = 1;
	}

	if (not_int_error == 0)
	{
		int updateid = stoi(supdateid);
		for (int i = 0; i < sizeof(*fitness); ++i)
		{
			ptr = fitness[i];
			if (ptr != NULL && ptr->classid == updateid)
			{
				classfound = 1;
				break;
			}
		}

		if (wrong_datamember == 0 && classfound == 1)
		{
			cout<<"Enter new value of "<<datamember<<endl;

			if (datamember == "name")
			{
				do
				{
					cout<<"Class Name: ";
					cin>>newdata;
					if (newdata.length() <= 1)
					{
						cout<<"Error: Class Name cannot be only 1 character"<<endl;
					}
				}
				while(newdata.length() <= 1);
				ptr->classname = newdata;
			}
			else if (datamember == "date")
			{
				int date_check = 1;
				do
				{
					date_check = 1;
					cout<<"Class date(dd-mm-yy): ";
					cin>>newdata;
					if (newdata.length() != 8 || newdata[2] != '-' || newdata[5] != '-')
					{
						cout<<"Error: invalid date(dd-mm-yy)"<<endl;
						date_check = 0;

					}
					else if (!isdigit(newdata[0]) || !isdigit(newdata[1]) || !isdigit(newdata[3]) || !isdigit(newdata[4]) || !isdigit(newdata[6]) || !isdigit(newdata[7]))
					{
						cout<<"Error: invalid date(dd-mm-yy)"<<endl;
						date_check = 0;
					}
				}
				while(date_check == 0);
				ptr->classdate = newdata;
			}
			else if (datamember == "time")
			{
				int time_check = 1;
				do
				{
					time_check = 1;
					cout<<"Class time(16:00): ";
					cin>>newdata;
					if (newdata.length() != 5 || newdata[2] != ':')
					{
						cout<<"Error: invalid time(hh:mm, 16:00)"<<endl;
						time_check = 0;

					}
					else if (!isdigit(newdata[0]) || !isdigit(newdata[1]) || !isdigit(newdata[3]) || !isdigit(newdata[4]))
					{
						cout<<"Error: invalid time(hh:mm, 16:00)"<<endl;
						time_check = 0;
					}
				}
				while(time_check == 0);	
				ptr->classtime = newdata;
			}
			else if (datamember == "capacity")
			{
				int max_check = 1;
				do
				{
					max_check = 1;
					cout<<"Maximum capacity: ";
					cin>>newdata;
					int int_length = newdata.length();
					for (int i = 0; i < int_length; ++i)
					{
						if (!isdigit(newdata[i]))
						{
							max_check = 0;
							cout<<"Error: capacity consists only integers"<<endl;
							break;
						}
					}
				}
				while(max_check == 0);
				int max = stoi(newdata);
				ptr->capacity = max;
				delete [] ptr->memberslist;
				ptr->memberslist = new int[max];
				for (int i = 0; i < max; ++i)
				{
					ptr->memberslist[i] = 0;
				}
			}
			else if (datamember == "room")
			{
				int room_check = 1;
				do
				{
					room_check = 1;
					cout<<"Room Number: ";
					cin>>newdata;
					int newdata_length = newdata.length();
					for (int i = 0; i < newdata_length; ++i)
					{
						if (!isdigit(newdata[i]))
						{
							room_check = 0;
							cout<<"Error: roomnumber consists only integers"<<endl;
							break;
						}
					}
				}
				while(room_check == 0);
				int room = stoi(newdata);	
				ptr->roomnumber = room;
			}
			cout<<endl;
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"Fitness Class with id "<<updateid<<" is successfuly updated!"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
		}
		else if(wrong_datamember == 1 && classfound == 1)
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"Error: invalid data member entered"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
		}
	}
	else if(not_int_error == 1)
	{
		cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
		cout<<"Error: invalid id number entered"<<endl;
		cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
	}

	if (classfound == 0)
	{
		cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
		cout<<"Error: no fitness class with id number entered"<<endl;
		cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
	}
	ptr = NULL;
	delete ptr;
}


void Fitness::viewClassesWithVacancies(Fitness* fitness[])
{
	int notfull = 0, a = 1;
	Fitness* ptr = new Fitness;
	cout<<"All fitness classes with vacancies:"<<endl;
	for (int d = 0; d < sizeof(*fitness); ++d)
	{
		ptr = fitness[d];
		if (ptr != NULL)
		{
			for (int i = 0; i < ptr->capacity; ++i)
			{
				if (ptr->memberslist[i] == 0)
				{
					i = i + 1;
					notfull = 1;
					break;
				}
			}
		}
		if (notfull == 1)
		{
			cout<<"----------------------------------------"<<endl;
			cout<<a<<")id: "<<ptr->classid<<endl;
			cout<<"  Class Name: "<<ptr->classname<<endl;
			cout<<"  Class date: "<<ptr->classdate<<endl;
			cout<<"  Class time: "<<ptr->classtime<<endl;
			cout<<"  Room Number: "<<ptr->roomnumber<<endl;
			cout<<"----------------------------------------"<<endl;
		}
		a = a + 1;
		notfull = 0;
	}
	ptr = NULL;
	delete ptr;
}


void Fitness::bookAClass(int memberid, Fitness* fitness[])
{
	string sbookid;
	int bookid, not_int_error = 0, notfull, alreadybooked = 0;
	Fitness* ptr = new Fitness;
	viewClassesWithVacancies(fitness);
	cout<<endl;
	cout<<"Enter Fitness Class id to book a class: ";
	cin>>sbookid;

	int slbookid = sbookid.length();
	for (int i = 0; i < slbookid; ++i)
	{
		if (!isdigit(sbookid[i]))
		{
			not_int_error = 1;
		}
	}

	if (not_int_error == 0)
	{
		bookid = stoi(sbookid);
		for (int i = 0; i < sizeof(*fitness); ++i)
		{
			ptr = fitness[i];
			if (ptr != NULL)
			{
				if (ptr->classid == bookid)
				{
					break;
				}
			}
		}

		if (ptr != NULL)
		{
			if (ptr->classid == bookid)
			{
				for (int i = 0; i < ptr->capacity; ++i)
				{
					if (ptr->memberslist[i] == 0)
					{
						notfull = 1;
						break;
					}
				}

				for (int i = 0; i < ptr->capacity; ++i)
				{
					if (ptr->memberslist[i] == memberid)
					{
						alreadybooked = 1;
						cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
						cout<<ptr->classname<<" Fitness Class is already booked"<<endl;
						cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
						break;
					}
				}
				if(notfull == 0 && alreadybooked == 0)
				{
					cout<<ptr->classname<<" Fitness Class is full"<<endl;
				}
				else if(notfull == 1 && alreadybooked == 0)
				{
					for (int i = 0; i < ptr->capacity; ++i)
					{
						if (ptr->memberslist[i] == 0)
						{
							ptr->memberslist[i] = memberid;
							cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
							cout<<ptr->classname<<" Fitness Class is successfuly booked"<<endl;
							cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
							break;
						}
					}
				}
			}
		}
		else
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"Error: no Fitness Class with id entered!"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
		}
	}
	else
	{
		cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
		cout<<"Error: invalid id entered!"<<endl;
		cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
	}
	ptr = NULL;
	delete ptr;
}


void Fitness::bookedclasses(int memberid, Fitness* fitness[])
{
	Fitness* ptr = new Fitness;
	cout<<"Booked Fitness Classes: "<<endl;
	for (int d = 0; d < sizeof(*fitness); ++d)
	{
		ptr = fitness[d];
		if (ptr != NULL)
		{
			for (int i = 0; i < ptr->capacity; ++i)
			{
				if (ptr->memberslist[i] == memberid)
				{
					cout<<"----------------------------------------"<<endl;
					cout<<"id: "<<ptr->classid<<endl;
					cout<<" Class Name: "<<ptr->classname<<endl;
					cout<<" Class date: "<<ptr->classdate<<endl;
					cout<<" Class time: "<<ptr->classtime<<endl;
					cout<<" Room Number: "<<ptr->roomnumber<<endl;
					cout<<"----------------------------------------"<<endl;
				}
			}
		}
	}
	ptr = NULL;
	delete ptr;
}


void Fitness::cancelBooking(int memberid, Fitness* fitness[])
{
	string scancelid;
	int cancelid, not_int_error = 0, canceled = 0;
	Fitness* ptr = new Fitness;
	cout<<"Booked Classes:"<<endl<<endl;
	bookedclasses(memberid, fitness);
	cout<<endl;
	cout<<"Enter Fitness Class id to cancel: ";
	cin>>scancelid;
	int slcancelid = scancelid.length();
	for (int i = 0; i < slcancelid; ++i)
	{
		if (!isdigit(scancelid[i]))
		{
			not_int_error = 1;
		}
	}
	if (not_int_error == 0)
	{
		cancelid = stoi(scancelid);
		for (int i = 0; i < sizeof(*fitness); ++i)
		{
			ptr = fitness[i];
			if (ptr != NULL && ptr->classid == cancelid)
			{
				break;
			}
		}
		if (ptr != NULL)
		{
			for (int i = 0; i < ptr->capacity; ++i)
			{
				if (ptr != NULL && ptr->memberslist[i] == memberid)
				{
					canceled = 1;
					ptr->memberslist[i] = 0;
					break;
				}
			}
		}
		if (canceled == 0)
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"Error: no booked Class with id number "<<cancelid<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
		}
		else if (canceled == 1)
		{
			cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
			cout<<"Fitness Class with id number "<<cancelid<<" is successfuly canceled"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
		}
	}
	else
	{
		cout<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<"|"<<endl<<endl;
		cout<<"Error: invalid id entered!"<<endl;
		cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl<<endl;
	}
	ptr = NULL;
	delete ptr;
}
