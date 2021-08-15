#pragma once
#ifndef _DENIZUMUT_ESER_DENIZUMUT_HW3_SUBSEQSLIST_H
#define _DENIZUMUT_ESER_DENIZUMUT_HW3_SUBSEQSLIST_H

struct SubSeqNode {
	int value; //numbers in linked list
	SubSeqNode* next; //next node

	SubSeqNode() {}

	SubSeqNode(const int& number, SubSeqNode* link)
	{
		value = number;
		next = link;
	}
};

struct SubSeqHeadNode {
	int size; //size of the subsequence linked list
	SubSeqNode* sHead; // head of the subsequence linked list
	SubSeqHeadNode* next; // next element of the heads sequence
	
	SubSeqHeadNode() {}

	SubSeqHeadNode(const int& s, SubSeqNode* link, SubSeqHeadNode* link2)
	{
		size = s;
		sHead = link;
		next = link2;
	}
};

class SubSeqsList
{
private:
	SubSeqHeadNode* hHead; // head of the heads list

public:
	SubSeqsList(); //default constructor that creates an empty list
	void printList(); //Display the entire structure
	void insertList(int, SubSeqNode*); //Insert sequences which are coming from function createSequence() into list
	void deleteList(int); //Delete one or more subsequence lists from the data structure
	bool isExist(int); //Find whether the particular value exist in the data structure
	void deleteAll(); //Delete the entire data structure
	void createSequence(int); //creates sequences to add into list from inputs
	SubSeqNode* copyList(SubSeqNode*); //create a copy of given sequence
	void sortList(); //sort all data structure
};

#endif