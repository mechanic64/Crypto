///******************************************************************
/// @file Hill.h
/// @author Author: Ben Olson
/// 
/// @details This program takes in information or documents and encodes
/// or decodes it using the hill cipher. 
/// Started 3-16-2017
/// Last Updated 11-28-2021
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

	/// @param string plainText contains the incoming data
	/// @param vector of matrix objects
	/// @param string savedText is a copy of the incoming data
	/// @param string cipherText is the encoded data
	/// @param int matrix key stores the key that encodes the data
	string plainText; //Text that will get destroyed as program runs
	vector<matrix> matrixList; //array that holds the text as matrices
	string savedText; //a copy of the original message
	string cipherText;
	int key[2][2];

public:

	/// @brief This function encodes the data stored in the plainText variable, then stores it in the cipherText variable
	/// 
	/// 
	/// @return returns nothing
	void Encode();

	/// @brief This function decodes the data stored in the cipherText variable, then stores it in the plainText variable
	/// 
	/// 
	/// @return returns nothing
	void Decode();

	/// @brief Sets the plainText string with the passed data and saves a copy
	/// 
	/// @param string a - passed data
	/// @return returns nothing
	void setPlainText(string a);

	/// @brief This sets the key and transforms it to uppercase
	/// 
	/// 
	/// @return returns nothing
	void setKey(string a);

	/// @brief This function returns the data stored in the cipherText variable
	/// 
	/// 
	/// @return returns string cipherText
	string getCipherText();

	/// @brief This function returns the data stored in the plainText variable
	/// 
	/// 
	/// @return returns string plainText
	string getPlainText();

	/// @brief Sets the cipherText string with the passed data and saves a copy
	/// 
	/// @param string a - passed data
	/// @return returns nothing
	void setCipherText(string a);

	/// @brief This function attempts to find the inverse of the key matrix
	/// 
	/// 
	/// @return returns nothing
	void REAsetKey();

};
#endif
