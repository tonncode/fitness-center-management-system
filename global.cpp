#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "global.h"
#include "admin.h"
#include "member.h"
#include "fitness.h"

using namespace std;

Member** member = new Member *[10];
Admin** admin = new Admin *[10];
Fitness** fitness = new Fitness *[10];

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