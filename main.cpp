
//Created by Mitchell Barker
//3-12-16
//Password breaking tools



#include "database.hpp"

//Compile with 
//	g++ -std=c++11 main.cpp -lcrypto -lssl



int main(void){
	string user;
	string passwd;
	//authenticate();
	//cout<<"authen"<<endl;
	Database db = Database("./db.txt");

	/*cout<<"username: ";
	getline(cin, user);
	cout<<"password: ";
	cin>>passwd;*/
	/*cout<<munge_char('a')<<endl;
	cout<<munge_char('A')<<endl;
	cout<<munge_char('@')<<endl;
	cout<<munge_char('^')<<endl;*/
	//db.brute_find("");
	db.expanded_dict_find("cain.txt", "cracked.txt");

	// vector<string> temp = children("apple");
	// for(int i = 0; i < temp.size(); ++i )
	// 	cout<<temp[i]<<endl;

	// string cur = "myfavoriteplacesonearth";
	// int count = 0;
	// while(!munged_string(cur)){
	// 	cur = next_munge("myfavoriteplacesonearth", cur);
	// 	cout<<cur<<endl;
	// 	++count;
	// }
	// cout<<count<<endl;



	/*cout<<next_string("a")<<endl;
	cout<<next_string("abcdef")<<endl;
	cout<<next_string("a~")<<endl;
	cout<<(char)33<<endl;*/
	/*User mitch = User("Barker","Mitchell","mbarker2", 721007778, hash);

	db.db.push_back(mitch);

	if(db.authenticate(user,passwd))
		cout<<user<<" authenticated."<<endl<<"Password ACCEPTED"<<endl;
	else
		cout<<user<<" rejected."<<endl<<"Password DENIED"<<endl;*/



	return 0;
}