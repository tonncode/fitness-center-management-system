#ifndef ADMIN_H
#define ADMIN_H

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

#endif