#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include "admin.h"
#include "member.h"
#include "fitness.h"
#include "global.h"

using namespace std;

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