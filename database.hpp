#ifndef DATABASE
#define DATABASE


#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <string>
#include <string.h>
#include <openssl/md5.h>
#include <iomanip>
#include <list>
	using namespace std;

typedef unsigned int uint;

list<string> children(string parent);
void add_children(list<string>& parent);
string next_string(string cur);
char next_char(char cur);


string my_compute_hash(string passwd) {
	MD5_CTX context;
	unsigned char digest[16];
	const char* string = reinterpret_cast<const char*>(passwd.c_str());

	MD5_Init(&context);
	MD5_Update(&context, string, strlen(string));
	MD5_Final(digest, &context);

	char md5string[33];
	for(int i = 0; i < 16; ++i)
    	sprintf(&md5string[i*2], "%02x", (unsigned int)digest[i]);

    return md5string;
}

class User {
public:
	string last_name, first_name, user_name, hash_val, salt;
	uint uin;

	User(string last="",string first="", string user="",uint u=0, string hash="",string s="");

	bool authenticate(string user, string passwd);

	bool operator< (const User &u1){
		return user_name < u1.user_name;
	}
	bool operator== (const User &u1){
		return user_name == u1.user_name;
	}

	friend istream &operator>>(istream &input, User &U){
		string line;
		if(!getline(input, line))
			return input;

		for (int i = 0; i < line.length(); i++){
        if (line[i] == ',')
            line[i] = ' ';
   		}
   		istringstream iss(line);
   		iss>>U.last_name>>U.first_name>>U.user_name>>U.uin>>U.hash_val;
   		if(U.hash_val.size() == 3){
   			U.salt = U.hash_val;
   			iss>>U.hash_val;
   		}


		return input;
	}

	friend ostream &operator<<(ostream &output, const User &U){
		output<<U.last_name<<","<<U.first_name<<","<<U.user_name<<","
			<<U.uin<<",";
		if(U.salt.length() > 0)
			output<<U.salt;
		output<<","<<U.hash_val;

		return output;
	}

};


class DataBase{
public:
	vector<User> db;
	ofstream out;

	DataBase(string file_name);

	bool authenticate(string user, string passwd);
	void pass_match(string hash);
	void find_passwords(string current);
	void dict_passwords();


	friend ostream &operator<<(ostream &output, const DataBase &d){
		for(auto it = d.db.begin(); it != d.db.end(); ++it)
			output<<*it<<endl;

		return output;
	}


};


User::User(string last,string first, string user,uint u, string hash,string s){
		last_name = last;
		first_name = first;
		user_name = user;
		uin = u;
		hash_val = hash;
		salt = s;
}

bool User::authenticate(string user, string passwd){
	string temp = my_compute_hash(passwd+salt);

	return 	temp == hash_val;
}

// vector<string> DataBase::pass_match(string hash){
// 	vector<string> matches;

// 	for(auto it = db.begin(); it != db.end(); ++it){
// 		if(it->hash_val == hash)
// 			matches.push_back(it->user_name);
// 	}
// 	return matches;

// }

void DataBase::pass_match(string passwd){
	string hash = my_compute_hash(passwd);
	string r_hash = hash;

	for(auto it = db.begin(); it != db.end(); ++it){
		if(it->salt.length()>0){
			hash = my_compute_hash(passwd+it->salt);
			if(it->hash_val == hash)
				cout<<it->user_name<<":"<<passwd<<endl;
			hash = r_hash;
		}
		else if(it->hash_val == hash)
			cout<<it->user_name<<":"<<passwd<<endl;
	}
}

void DataBase::find_passwords(string current){
	//list<string> tree = children(current);
	current = (char) 33;

	while(true){//!tree.empty()){
		//add_children(tree);

		//pass_match(tree.front());
		//cout<<current<<endl;
		pass_match(current);
		current = next_string(current);

		//tree.pop_front();
	}
}

void DataBase::dict_passwords(){
	ifstream ifile("cain.txt");
	out.open("cracked.txt");
	string temp;
	while(ifile.good()){
		getline(ifile, temp);
		pass_match(temp);
	}
	ifile.close();
	out.close();
}

bool DataBase::authenticate(string user, string passwd){
	User searching = User("temp","temp",user);
	vector<User>::iterator it;

	it = find(db.begin(), db.end(), searching);

  	if (it!=db.end())
    	return it->authenticate(user,passwd);
    else 
    	return false;

}



DataBase::DataBase(string file_name){
		ifstream file(file_name.c_str());
		while(file.good()){
			User tmp = User();
			file>>tmp;
			db.push_back(tmp);
		}
		if(db.back().user_name.size() < 1)
			db.pop_back();

		sort(db.begin(), db.end());


		file.close();

}

void add_children(list<string>& parent){
	string temp = parent.front();
	for(int i =33; i < 127; i++)
		parent.push_back(temp+(char)i);
}


list<string> children(string parent){
	list<string> childs;

	for(int i =33; i < 127; i++)
		childs.push_back(parent+(char)i);
	return childs;
}
bool same_chars(const std::string& s) {
    return s.find_first_not_of(s[0]) == std::string::npos;
}


string next_string(string cur){
	int i = cur.length() -1;
	do{
		cur[i] = next_char(cur[i]);
		--i;
	}while(cur[i+1] == (char) 33 && i >= 0);

	if (same_chars(cur) && cur[0] == '!')
		cur = cur+(char)33;

	return cur;
}

char next_char(char cur){
	if(cur == (char) 126)
		cur = (char) 33;
	else
		++cur;
	return cur;
}


#endif