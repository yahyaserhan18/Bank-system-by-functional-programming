#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

namespace inputs{

	int readIntNumber(string message) {
		int n = 0;
		cout << message;cin >> n;

		while (cin.fail()) {

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout <<	"Error : Invalid number! , "<<message;cin >> n;
		}

		return n;
	}
	int readPositiveNumber(string message) {
		int n = 0;
		cout << message;cin >> n;
		while (cin.fail()) {

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Error : Invalid number! , " << message;cin >> n;
		}

		while(n<0) {
			cout <<"Error : Out Range!  " << message;cin >> n;
		}
		return n;
	}
	double readDoubleNumber(string message) {
		double n = 0;
		cout << message;cin >> n;
		while (cin.fail()) {

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Error : Invalid number! , " << message;cin >> n;
		}
		return n;
	}
	int readNumberInRange(int from , int to , string message) {
		int n = 0;
		cout << message;cin >> n;

		while (cin.fail()) {

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Error : Invalid number! , " << message;cin >> n;
		}

		while(n<from || n>to) {
			cout << "Error : Out Range!  " << message;cin >> n;
		}
		return n;
	}

	string readString(string message) {
		string s;
		cout << message;getline(cin>>ws, s);
		return s;
	}

	char readChar(string message) {
		char c = ' ';
		cout << message; cin >> c;
		return c;
	}

}
