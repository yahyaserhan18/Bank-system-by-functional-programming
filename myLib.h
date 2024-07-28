#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


namespace myLib {

	int randomNumberInRange(int from , int to) {
		return rand()%(to - from + 1) + from;
	}

	void Swap(int& number1, int& number2) {
		int temp = number1;
		number1 = number2;
		number2 = temp;
	}

	void Swap(double& number1, double& number2) {
		int temp = number1;
		number1 = number2;
		number2 = temp;
	}

	 bool isContinue(string message) {
		 bool a;
		 cout << message; cin >> a;
		 return a;
	}


}
