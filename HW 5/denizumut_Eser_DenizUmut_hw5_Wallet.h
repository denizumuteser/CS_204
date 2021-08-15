#pragma once
#ifndef _DENIZUMUT_ESER_DENIZUMUT_HW5_WALLET_H
#define _DENIZUMUT_ESER_DENIZUMUT_HW5_WALLET_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

struct Money
{
	string currency;
	double amount;

	Money() {} //default constructor

	Money(string c, double a) { //constructor
		currency = c;
		amount = a;
	}
};

class Wallet
{
private:
	Money* currencies;
	int size;

public:
	//constructors
	Wallet();//default constructor
	Wallet(const Wallet& wallet); //deep copy constructor
	~Wallet(); //generic destructor
	Money* deepCopy() const; //deep copy function

	//helper functions
	bool isExist(const Money& money) const; //is money exist in wallet
	bool isExistEqual(const Money& money) const; //is money exist and amount is same
	int getSize() const; //get wallet size
	Money* getCurrencies() const; //get wallet currencies

	//operator override member functions
	Wallet operator + (const Money& rhs) const; //add money yo wallet, then return total as new wallet
	Wallet operator + (const Wallet& rhs) const; //return sum of both wallets as new wallet
	const Wallet& operator = (const Wallet& rhs); //assing rhs wallet to lhs wallet
	const Wallet& operator += (const Wallet& rhs); //add sum of two wallets to the left wallet
	Wallet operator - (const Money& rhs) const; //spend money from wallet, return as new wallet
	bool operator >= (const Money& rhs) const; //checks if money exist in wallet is greater
	
};
//free functions
bool operator == (const Wallet& lhs ,const Wallet& rhs); //checks if both wallets are equal
ostream& operator << (ostream& os, const Wallet& ct); //puts wallet object into outputstream
bool operator <= (const Money& lhs ,const Wallet& rhs); //checks if money exist in wallet is lessser

#endif // !_DENIZUMUT_ESER_DENIZUMUT_HW3_WALLET_H