#include "database.hpp"

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

User::User(string last,string first, string user,uint u, string hash,int s){
		last_name = last;
		first_name = first;
		user_name = user;
		uin = u;
		hash_val = hash;
		salt = s;
}

bool User::authenticate(string user, string passwd){
	string temp = my_compute_hash(passwd);
	return 	temp == hash_val;
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

