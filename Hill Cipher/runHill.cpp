///******************************************************************
/// @file runHill.cpp
/// @author Author: Ben Olson
/// 
/// @details This program takes in information or documents and encodes
/// or decodes it using the hill cipher. 
/// 
/// Started 3-16-2017
/// 
/// 
///******************************************************************


#include <vector>
#include <string>
#include <iostream>
#include "matrix.h"
#include "Hill.h"

using namespace std;

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
	} while (restart);
	return 0;
}