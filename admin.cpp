#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "admin.h"

using namespace std;


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


void Admin::save(Admin* admin[])
{
	Admin* ptr = new Admin; 	
	ofstream fout("./Desktop/AdminsTable.txt"); 
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