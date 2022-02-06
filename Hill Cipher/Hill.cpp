///******************************************************************
/// @file Hill.cpp
/// @author Author: Ben Olson
/// 
/// @details Definition of the Hill header, defines all the methods 
/// required to process the file provided
/// 
/// Started 3-16-2017
/// Last Updated 11-28-2021
/// 
///******************************************************************


#include <vector>
#include <string>
#include <iostream>
#include "matrix.h"
#include "Hill.h"


/// @brief Sets the plainText string with the passed data and saves a copy
/// 
/// @param string a - passed data
/// @return returns nothing
void Hill::setPlainText(string a)
{
	plainText = a;
	savedText = a;
}

/// @brief Sets the cipherText string with the passed data and saves a copy
/// 
/// @param string a - passed data
/// @return returns nothing
void Hill::setCipherText(string a)
{
	cipherText = a;
	savedText = a;
}


/// @brief This function encodes the data stored in the plainText variable, then stores it in the cipherText variable
/// 
/// 
/// @return returns nothing
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

	//cout << plainText << endl;
	plainText.erase(remove_if(plainText.begin(), plainText.end(), ::isspace), plainText.end()); //strip spaces
	//cout << plainText << endl;

	for (int i = 0; i < plainText.size(); i++)
		plainText[i] = toupper(plainText[i]); //changes to uppercase

	//cout << plainText << endl;

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

/// @brief This function decodes the data stored in the cipherText variable, then stores it in the plainText variable
/// 
/// 
/// @return returns nothing
void Hill::Decode()
{
	/*
	This is the setup portion of the program
	It will create the matrices with which the program
	will encode and decode the messeges
	*/
	

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
		out[1][0] = ((-matrixList.at(i).m[1][0] * (key[1][0])) + (matrixList.at(i).m[1][0] * -key[1][1])) % 26;

		plainText = plainText + ((char)(out[0][0] + 65)) + ((char)(out[1][0] + 65));
		
	}
}

/// @brief This sets the key and transforms it to uppercase
/// 
/// 
/// @return returns nothing
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

/// @brief This function attempts to find the inverse of the key matrix
/// 
/// 
/// @return returns nothing
void Hill::REAsetKey()
{
	//http://www-math.ucdenver.edu/~wcherowi/courses/m5410/exeucalg.html
	//math goes here lol, the key should already be loaded so we can use the key matrix
	//just need to find the inverse of it, set it, and then use it
	int b[2][2] = { 0,0,0,0 };

	/*float p, q;

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
	}*/

	int i, j, k;
	float p, q;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++) {
			if (i == j)
				b[i][j] = 1;
			else
				b[i][j] = 0;
		}
	for (k = 0; k < 2; k++) {
		for (i = 0; i < 2; i++) {
			p = key[i][k];
			q = key[k][k];
			for (j = 0; j < 2; j++) {
				if (i != k)
				{
					key[i][j] = (key[i][j] * q) - (p * key[k][j]);
					b[i][j] = (b[i][j] * q) - (p * b[k][j]);
				}
			}
		}
	}
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			b[i][j] = b[i][j] / key[i][i];
	/*cout << "\n\nInverse Matrix is:\n";
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++)
			cout << b[i][j] << " ";
		cout << "\n";
	}*/


}

/// @brief This function returns the data stored in the cipherText variable
/// 
/// 
/// @return returns string cipherText
string Hill::getCipherText()
{
	return cipherText;
}

/// @brief This function returns the data stored in the plainText variable
/// 
/// 
/// @return returns string plainText
string Hill::getPlainText()
{
	return plainText;
}