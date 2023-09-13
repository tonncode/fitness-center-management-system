#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "fitness.h"

using namespace std;

void Fitness::save(Fitness* fitness[])
{
	Fitness* ptr = new Fitness; 	
	ofstream fout("./Desktop/FitnessClassesTable.txt"); 
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
