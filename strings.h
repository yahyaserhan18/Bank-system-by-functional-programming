#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>


namespace strings {
	void UpperFirstLeterOfEachFirstWord(string& str) {

		bool isFirstChar = true;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ' ' && isFirstChar)
				str[i] = toupper(str[i]);

			isFirstChar = str[i] == ' ' ? true : false;
		}
	}

	void LowerFirstLeterOfEachFirstWord(string& str) {

		bool isFirstChar = true;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ' ' && isFirstChar)
				str[i] = tolower(str[i]);

			isFirstChar = str[i] == ' ' ? true : false;
		}
	}

	void UpperString(string& str) {
		for (int i = 0; i < str.length(); i++) {
			if(str[i] != ' ')
				str[i] = toupper(str[i]);
		}
	}

	string LowerString(string str) {
		string str2 = str;
		for (int i = 0; i < str2.length(); i++) {
			if (str2[i] != ' ')
				str2[i] = tolower(str2[i]);
		}
		return str2;
	}

	char invertCharCase(char  character) {
		char c;
		isupper(character) ? c= tolower(character) : c= toupper(character);
		return c;
	}

	void invertAllCharsCase(string& str) {
		for (int i = 0; i < str.length(); i++) {
			str[i] = invertCharCase(str[i]);
		}
	}

	int countCapitalLettersOfString(string& str) {
		int count = 0;
		for (int i = 0; i < str.length(); i++) {
			if (isupper(str[i]))
				count++;
		}
		return count;
	}

	int countSmallLettersOfString(string& str) {
		int count = 0;
		for (int i = 0; i < str.length(); i++) {
			if (islower(str[i]))
				count++;
		}
		return count;
	}

	int countCharInString(string str, char character , bool caseIsImportant=true) {
		int counter = 0;
		for (int i = 0; i < str.length(); i++) {
			if (caseIsImportant)
			{
				if (str[i] == character)
					counter++;
			}
			else {
				if (toupper(str[i]) == toupper(character))
					counter++;
			}
		}
		return counter;
	}

	bool isVowelLetter(char character) {
		character = tolower(character);
		return (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u');
		
	}


	int countVowelLetters(string str) {
		int counter = 0;
		for (int i = 0; i < str.length(); i++) {
			if (isVowelLetter(str[i]))
				counter++;
		}
		return counter;
	}

//my way to split to vector  :
	/*
	void splitStringToVector(string str, char delim, vector <string>& vLines) {
		string slice = "";
		for (int i = 0; i < str.length(); i++) {

			if (str[i] == delim)
			{
				vLines.push_back(slice);
				slice = "";
			}
			else
				slice += str[i];
		}
		if(slice != "")
			vLines.push_back(slice);
	}
*/

	void splitStringToVector(string str, string delim, vector <string>& vLines) {
		short position = 0;
		string word = "";
		while((position = str.find(delim)) != string::npos) {

			word = str.substr(0, position);
			//if (word != "")
				vLines.push_back(word);

			str.erase(0, position + delim.length());

		}

		if (str != "")
			vLines.push_back(str);
		
	}


	int countWordsInString(string str, string delim) {
		short position = 0;
		int counter = 0;
		string word = "";
		while ((position = str.find(delim)) != string::npos) {

			word = str.substr(0, position);
			if (word != "")
				counter++;

			str.erase(0, position + delim.length());

		}

		if (str != "")
			counter++;


		return counter;
	}


	string trimLeft(string str) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ' ')
				return str.substr(i, str.length() - i);
		}
		return "";
		//my way :
			/*
			string temp = str;

			for (int i = 0;i < str.length();i++) {
				if (str[i] != ' ')
					break;
				else
					temp.erase(0, 1);
			}

			return temp;
		*/
	}

	string trimRight(string str) {

		for (int i = str.length()-1; i >0; i--) {
			if (str[i] != ' ')
				return str.substr(0, i+1);
		}
		return "";
	//my way : 
		/*
			string temp = str;

			for (int i = 0;i < str.length();i++) {
				if (str[str.length() -i-1] != ' ')
					break;
				else
					temp.erase(str.length() - i - 1, str.length() -1);
			}

			return temp;
		*/
	}

	string trim(string str) {
		return trimLeft(trimRight(str));
	}

	string joinString(vector <string>& Vector ,string delim ) {
		string str = "";
		for (string& s : Vector) {
			str += s;
			if (s != Vector.back())
				str += delim;
		}
		return str;

	}

	string joinString(string arr[] ,int len , string delim) {
		string str = "";
		for (int i = 0; i < len; i++) {
			str += arr[i];
			if (arr[i] != arr[len - 1])
				str += delim;
		}
			
			
		return str;
	}

	vector <string> reverseVector(vector <string> v) {
		vector <string> vTemp;
		for (int i = v.size()-1; i >= 0 ; i--) {
			vTemp.push_back(v[i]);
		}
		return vTemp;
		//for (string &line : vTemp) {
		//	v.push_back(line);
		//}
	}

	string reverseWordsInString(string str) {
		string tempStr = "";
		vector <string> vString;
		splitStringToVector(str, " ", vString);
		
		vector <string>::iterator iter = vString.end();

		while (iter != vString.begin()) {
			iter--;
			tempStr += *iter + " ";
		}
		return tempStr.substr(0,tempStr.length()-1);

		// my way :
			/*
		vector <string> vString;
		splitStringToVector(str," ",vString);

		vString = reverseVector(vString);

		return joinString(vString, " "); 
		*/
	}


	string ReplaceWordInString(string str , string wordToReplace , string ReplaceTo , bool caseIsImportant=true) {

		vector <string> vString;
		splitStringToVector(str," ",vString);

		for (string& word : vString) {
			if (!caseIsImportant) {
				if (LowerString(word) == LowerString(wordToReplace))
					word = ReplaceTo;
			}
			else {
				if (word == wordToReplace)
					word = ReplaceTo;
			}
		}

		return joinString(vString," ");

	}
		

	string RemoveAllpucsFromString(string str) {
		string result = "";
		//ispunct
		for (int i = 0; i < str.length(); i++) {
			if (!ispunct(str[i]))
				result += str[i];
		}
		return result;
	}


}