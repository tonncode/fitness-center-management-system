#ifndef FITNESS_H
#define FITNESS_H

using namespace std;

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

#endif