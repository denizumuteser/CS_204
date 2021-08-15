#include <iostream>
#include "denizumut_Eser_DenizUmut_hw3_SubSeqsList.h"
using namespace std;

SubSeqsList::SubSeqsList()
{
	hHead = NULL; 
}

void SubSeqsList::printList()
{
	SubSeqHeadNode* ptr = hHead;
	SubSeqNode* sptr;
	cout << "FINAL CONTENT" << endl;
	if (ptr == NULL)
		cout << "List is empty!" << endl;

	while (ptr != NULL) //loop through heads list
	{	
		sptr = ptr->sHead;
		cout << ptr->size << " | "; //print size
		while (sptr != NULL) //loop through each list with given head
		{
			cout << sptr->value; //print value
			if (sptr->next != NULL)
			{
				cout << " --> ";
			}
			sptr = sptr->next;
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void SubSeqsList::insertList(int size, SubSeqNode* shead) 
{
	SubSeqHeadNode* ptr = hHead;

	if (ptr == NULL) //if adding to a empty list
	{
		ptr = new SubSeqHeadNode(size, shead, NULL);
		hHead = ptr;
	}
	else //if list is already populated
	{
		while (ptr->next != NULL) //find the node at the end
		{
			ptr = ptr->next;
		}
		ptr->next = new SubSeqHeadNode(size, shead, NULL); //add to the end
	}
}

void SubSeqsList::deleteList(int num)
{
	SubSeqHeadNode* ptr = hHead;
	SubSeqHeadNode* ptr2;
	SubSeqHeadNode* htemp;
	SubSeqNode* sptr;
	SubSeqNode* temp;
	bool toDelete = false;

	while (ptr != NULL) //looping heads list
	{
		sptr = ptr->sHead;
		while (sptr != NULL) //looping each sequence with given head
		{
			if (sptr->value == num)
			{
				toDelete = true; //decide if sequence must be deleted
			}
			sptr = sptr->next;
		}
		if (toDelete) //start deleting sequence for the current head
		{	
			sptr = ptr->sHead;
			while (sptr != NULL) //delete subsequence by looping
			{
				temp = sptr->next;
				delete sptr; //deleting subsequences
				sptr = temp;
			}
			if (ptr == hHead) //if ptr is the first element
			{
				hHead = hHead->next;
				delete ptr; //delete head from headlist
				ptr = hHead;
			}
			else //if ptr is in mid or end
			{
				ptr2 = hHead;
				while (ptr2->next != ptr) //find first node before the node being deleted
				{
					ptr2 = ptr2->next;
				}
				ptr2->next = ptr->next;
				delete ptr; //delete head from headlist
				ptr = ptr2->next;
			}			
		}
		else //noting to delete at the current subsequence
		{
			ptr = ptr->next;
		}
		toDelete = false;
	}
}

bool SubSeqsList::isExist(int val)
{
	SubSeqHeadNode* ptr = hHead;
	SubSeqNode* sptr = NULL;
	
	while (ptr != NULL) //looping heads list
	{
		sptr = ptr->sHead;
		while (sptr != NULL) //looping subsequence of given head
		{
			if (sptr->value == val)
			{
				return true; //found given number in data structure
			}
			sptr = sptr->next;
		}
		ptr = ptr->next;
	}
	return false; //could not found given number in data structure
}

void SubSeqsList::deleteAll()
{
	SubSeqHeadNode* ptr = hHead;
	SubSeqHeadNode* htemp;
	SubSeqNode* sptr = NULL;
	SubSeqNode* temp;

	while (ptr != NULL) //looping heads list
	{
		sptr = ptr->sHead;
		while (sptr != NULL) //looping subsequences of given head
		{
			temp = sptr->next;
			delete sptr; //deleting subsequences
			sptr = temp;
		}
		htemp = ptr->next;
		delete ptr; //deleting head sequences
		ptr = htemp;
	}
	hHead = NULL;
}

void SubSeqsList::createSequence(int num)
{
	SubSeqNode* shead;
	SubSeqHeadNode* ptr = hHead;
	SubSeqNode* sptr;
	bool toCopy = true;
	SubSeqNode* stemp;

	shead = new SubSeqNode(num, NULL); //construct a node with only given number
	this->insertList(1, shead); //insert given number node with size 1
	
	while (ptr != NULL) //looping heads list
	{
		sptr = ptr->sHead;
		while (sptr != NULL) //looping sequence of given head
		{
			if (sptr->value >= num)
			{
				toCopy = false; //if possible sequence is found to add given number, get ready for copying it
			}
			sptr = sptr->next;
		}
		if (toCopy)
		{
			shead = this->copyList(ptr->sHead); //copy the existing list
			stemp = shead;
			while (stemp->next != NULL) //find the last node of the sequence
			{
				stemp = stemp->next;
			}
			stemp->next = new SubSeqNode(num, NULL); //add given number to the copied sequence
			this->insertList(ptr->size+1, shead); //insert this new sequence to the end of the main list
		}
		toCopy = true;
		ptr = ptr->next;
	}
}

SubSeqNode* SubSeqsList::copyList(SubSeqNode* s)
{
	if (s == NULL) //nothing to copy
	{
		return NULL;
	}
	SubSeqNode* res = new SubSeqNode(s->value, NULL); //create a new node
	SubSeqNode* temp = res;
	
	while (s->next != NULL)
	{
		temp->next = new SubSeqNode(s->next->value, NULL); //write contents of the existing sequence to the new copy
		s = s->next;
		temp = temp->next;
	}
	return res; //return the copy
}

void SubSeqsList::sortList() //bubble sort for linked lists
{
	SubSeqHeadNode* ptr = hHead;
	SubSeqHeadNode* x = new SubSeqHeadNode; //temp for first headNode in swap 
	SubSeqHeadNode* y = new SubSeqHeadNode; //temp for second headNode in swap
	SubSeqHeadNode* temp = ptr;
	SubSeqHeadNode* temp2;
	SubSeqNode* tempS1; //temp for first node in swap 
	SubSeqNode* tempS2; //temp for second node in swap
	bool isSorted = false;
	bool ischanged = false;
	bool isBigger = false;
	bool found = false;

	if (ptr == NULL || ptr->next == NULL) //if nothing to sort
	{
		return;
	}
	
	while (!isSorted) //continue until whole list is sorted
	{
		ischanged = false;
		while (ptr != NULL && ptr->next != NULL) //looping heads list
		{
			isBigger = false;
			if (ptr->size > ptr->next->size) //decide if first size is bigger
			{
				isBigger = true;
			}
			else if (ptr->size == ptr->next->size) //decide if first numbers in sequence is bigger if sizes are equal
			{
				tempS1 = ptr->sHead;
				tempS2 = ptr->next->sHead;
				found = false;
				while (tempS1 != NULL && !found)
				{
					if (tempS1->value > tempS2->value)
					{
						isBigger = true;
						found = true;
					}
					else if (tempS1->value < tempS2->value)
					{
						isBigger = false;
						found = true;
					}
					else
					{
						tempS1 = tempS1->next;
						tempS2 = tempS2->next;
					}		
				}
			}
			if (isBigger) //if first one is bigger than second one, swap their order
			{
				ischanged = true; //cheking if anything is changed in current iteration
				x = ptr;
				y = ptr->next;
				if (x == hHead) //if swaping in first node
				{
					x->next = y->next; //swap
					hHead = y;
					y->next = x;
				}
				else //if swaping in mid or end nodes
				{
					while (temp->next != x) //find first node before the node to be swapped
					{
						temp = temp->next;
					}
					temp2 = x;
					x->next = y->next; //swap
					temp->next = y;
					y->next = x;
				}
			}
			ptr = ptr->next;
		}
		if (!ischanged) //if nothing is changed in the current iteration, list must be sorted
		{
			isSorted = true;
		}
		else //keep looping, list is not sorted yet
		{
			ptr = hHead;
			temp = ptr;
		}
	}
}
