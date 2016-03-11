
#include "database.hpp"

//Compile with 
//	g++ -std=c++11 main.cpp -lcrypto -lssl



int main(void){
	string user;
	string passwd;
	//authenticate();
	//cout<<"authen"<<endl;
	DataBase db = DataBase("./db.txt");

	/*cout<<"username: ";
	getline(cin, user);
	cout<<"password: ";
	cin>>passwd;*/

	db.find_passwords("");
	//db.dict_passwords();
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