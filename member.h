#ifndef MEMBER_H
#define MEMBER_H

using namespace std;

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

#endif