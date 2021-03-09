///******************************************************************
/// @file Hill.cpp
/// @author Author: Ben Olson
/// 
/// @details This program takes in information or documents and encodes
/// or decodes it using the hill cipher. 
/// Started 3-16-2017
/// 
/// 
///******************************************************************

#include <vector>
#include <string>
#include <iostream>
#include "matrix.h"

using namespace std;

class Hill
{

	string plainText; //Text that will get destroyed as program runs
	vector<matrix> matrixList; //array that holds the text as matrices
	string savedText; //a copy of the original message
	string cipherText;
	int key[2][2];

public:
	void Encode();
	void Decode();
	void setPlainText(string a);
	void setKey(string a);
	string getCipherText();
	string getPlainText();
	void setCipherText(string a);
	void REAsetKey();

};

void Hill::setPlainText(string a)
{
	plainText = a;
	savedText = a;
}
void Hill::setCipherText(string a)
{
	cipherText = a;
	savedText = a;
}

void Hill::Encode()
{
	/*
	This is the setup portion of the program
	It will create the matrices with which the program
	will encode and decode the messeges
	*/
	string text;
	string inputkey;

	cout << "Please input a string" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin,text);

	setPlainText(text);

	cout << "Please input a four letter key" << endl;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, inputkey);
	setKey(inputkey);

	plainText.erase(remove_if(plainText.begin(), plainText.end(), ::isspace), plainText.end()); //strip spaces

	for (int i = 0; i < plainText.size(); i++)
		plainText[i] = toupper(plainText[i]); //changes to uppercase

	int size = plainText.length();
	for (int i = 0; i <= size; i++)
	{
		//put some code here to create the matrices
		matrix m;

		for (int j = 0; j<2; j++)
		{
			m.m[j][0] = plainText[0] - 65;
			plainText.erase(0, 1);

		}
		matrixList.push_back(m);
	}

	/*
	This following section does the actual work
	For every entry in the m matrix, it will multiply the integer by the [0][0] and [0][1]
	entries in the key
	It will then save the result into the out matrix
	and append the character (noted by the integer) onto the appropriate string
	*/
	
	int out[2][1];

	for (int i = 0; i<matrixList.size() / 2; i++)
	{
		out[0][0] = ((matrixList.at(i).m[0][0] * key[0][1]) + (matrixList.at(i).m[0][0] * key[0][0])) % 26;
		out[1][0] = ((matrixList.at(i).m[1][0] * key[1][1]) + (matrixList.at(i).m[1][0] * key[1][0])) % 26;

		cipherText = cipherText + ((char)(out[0][0] + 65)) + ((char)(out[1][0] + 65));
	}
}
void Hill::Decode()
{
	/*
	This is the setup portion of the program
	It will create the matrices with which the program
	will encode and decode the messeges
	*/
	//

	string text;
	string inputkey;

	cout << "Please input a coded message" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, text);

	setCipherText(text);

	cout << "Please input a four letter key" << endl;
	getline(cin, inputkey);
	setKey(inputkey);
	REAsetKey();

	cipherText.erase(remove_if(cipherText.begin(), cipherText.end(), ::isspace), cipherText.end()); //strip spaces

	for (int i = 0; i<cipherText.size(); i++)
		cipherText[i] = toupper(cipherText[i]);

	int size = cipherText.length();
	for (int i = 0; i <= size; i++)
	{
		//put some code here to create the matrices
		matrix m;

		for (int j = 0; j<2; j++)
		{
			m.m[j][0] = cipherText[0]-65;
			cipherText.erase(0, 1);

		}
		matrixList.push_back(m);
	}

	/*
	This following section does the actual work
	For every entry in the m matrix, it will multiply the integer by the [0][0] and [0][1]
	entries in the key
	It will then save the result into the out matrix
	and append the character (noted by the integer) onto the appropriate string
	*/

	int out[2][1];

	for (int i = 0; i<matrixList.size()/2; i++)
	{
		out[0][0] = ((matrixList.at(i).m[0][0] * key[0][0]) + (matrixList.at(i).m[0][0] * (key[0][1]))) % 26;
		out[1][0] = ((matrixList.at(i).m[1][0] * (key[1][0])) + (matrixList.at(i).m[1][0] * key[1][1])) % 26;

		plainText = plainText + ((char)(out[0][0] + 65)) + ((char)(out[1][0] + 65));
	}
}

void Hill::setKey(string a)
{
	for (int i = 0; i<a.size(); i++)
		a[i] = toupper(a[i]);
	int k = 0;
	for (int i = 0; i<2; i++)
	{
		for (int j = 0; j<2; j++)
		{
			key[i][j] = a[k] - 65;
			k++;
		}
	}
}
void Hill::REAsetKey()
{
	//http://www-math.ucdenver.edu/~wcherowi/courses/m5410/exeucalg.html
	//math goes here lol, the key should already be loaded so we can use the key matrix
	//just need to find the inverse of it, set it, and then use it


	float p, q;

	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 2; i++)
		{
			p = key[i][k];
			q = key[k][k];

			for (int j = 0; j < 2; j++)
			{
				if (i != k)
				{
					//key[i][j] = (key[i][j] * q) - (p * key[k][j]);
					key[i][j] = (key[i][j] * q) - (p * key[k][j]);
				}
			}
		}
	}


}
string Hill::getCipherText()
{
	return cipherText;
}
string Hill::getPlainText()
{
	return plainText;
}

int main()
{
	bool restart = true;
	char answer;
	do
	{
		Hill cipher;
		int selection = 0;

		cout << "Please input a choice from the list" << endl;
		cout << "HILL CIPHER PROGRAM" << endl;
		cout << "-------------------" << endl;
		cout << "1. Encryption" << endl;
		cout << "2. Decryption with known key" << endl;
		cout << "3. Decryption with unknown key (not implemented)" << endl;
		cin >> selection;



		switch (selection)
		{
			case 1: cipher.Encode(); cout << cipher.getCipherText() << endl; break;
			case 2: cipher.Decode(); cout << cipher.getPlainText() << endl; break;
			default: cout << "Please input an option in the list" << endl;
		}
		cout << "Would you like to continue" << endl;
		cin >> answer;
		if (answer == 'N' || answer == 'n')
		{
			restart = !restart;
		}
	} 
	while (restart);
	return 0;
}
