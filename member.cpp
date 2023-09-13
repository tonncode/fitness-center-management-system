#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "member.h"

using namespace std;


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

void Member::save(Member* member[])
{
	Member* ptr = new Member; 	
	ofstream fout("./Desktop/MembersTable.txt"); 
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