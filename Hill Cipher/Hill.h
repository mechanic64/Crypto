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

#ifndef HILL_HEADER
#define HILL_HEADER

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
#endif
