#include <iostream>
#include <string>
#include <istream>
#include <sstream> //istringstream
#include "denizumut_Eser_DenizUmut_hw3_SubSeqsList.h"
using namespace std;

//Deniz Umut Eser//
bool isInt(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
			return true;
	}
	return false;
}

int main() 
{
	int number, size = 1; //inits
	string numbers;
	SubSeqsList* myList = NULL;	//construct the subseqsList
	myList = new SubSeqsList; //main data structure

	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers); //take list of integers for input
	cout << endl;

	if (numbers.length() <= 0 || !isInt(numbers)) //if second input is just 'enter' or just spaces
	{
		myList->printList(); //print current list, which is empty
		return 0; //stop further processing
	}
	istringstream iss(numbers); //stream for numbers
	while (iss >> number) //taking inputs one by one
	{
		if (number >= 0) //if non-negative number add to the sequences
		{
			if (!myList->isExist(number)) //number is not in structure add
			{
				myList->createSequence(number); //create all possible sequences then function sends each sequence to insertList() to be added into list.
				cout << "Subsequence(s) containing " << number << " has/have been added" << endl;
			}
			else // if number already exists ignore
			{
				cout << number << " is already in the list!" << endl;
			}
		}
		else if (number < 0) //if negative number is given remove from sequences
		{
			if (myList->isExist(abs(number))) //if number as ordered to delete is exist
			{
				myList->deleteList(abs(number)); //deletes all sequences with the given number 
				cout << "All subsequence(s) containing " << abs(number) << " has/have been deleted" << endl;
			}
			else //if there is no such number to delete
			{
				cout << "There is no subsequence that contains " << abs(number) << " to be deleted" << endl;
			}	
		}
		size += 1; //iterate current size
	}
	cout << endl;
	myList->sortList(); //sort list before printing
	myList->printList(); //print the final list
	myList->deleteAll(); //delete whole structure after printing
	return 0; //end of fun
}