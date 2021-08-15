#include <iostream>
#include <string>
#include <istream>
#include <sstream> //istringstream
using namespace std;

//Deniz Umut Eser//

struct node //node struct for linked list
{
	int value;
	node* next;
	node() {} //default constructor
	node(int v, node *p) //constructor with two parameters
	{
		value = v;
		next = p;
	}
};

node* AddList(node* head, int newkey) { //function for adding given key to given linked list
	node* ptr = head;
	if (head == NULL)
	{
		return new node(newkey, head); //if there is no value in the head make newkey a head
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new node(newkey, ptr->next); //get to the end of the linked list and insert newkey
	return head;	
}

/* Begin: code taken from pointers-linkedlists.ppt and modified */
void DeleteOneNode(node*& head, node* toBeDeleted)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node* ptr;
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr != NULL && ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted
		//connect the previous node to the next node and delete		
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from pointers-linkedlists.ppt and modified */

void DeleteList(node* head) { //function for deleting used list in the end of the program with printing deleted items
	node* temp;
	cout << "All the nodes are deleted at the end of the program: ";
	while (head != NULL) {
		cout << head->value << " ";
		temp = head->next;
		delete head; //every iteration delete head and make next node head
		head = temp;
	}
	cout << endl;
}

void printList(node* &head) { //printing list elements one by one
	node* ptr;
	ptr = head;
	cout << "List content:";
	while (ptr != NULL)
	{
		cout << " " << ptr->value;
		ptr = ptr->next;
	}
	cout << endl;
}

bool isExist(node* &head, int value) { //checking for input value is in list
	node* ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->value == value)
		{
			return true; //if exists
		}
		ptr = ptr->next;
	}
	return false; //if not exists
}

bool isInt(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
		{
			return true;
		}
	}
	return false;
}

int main() {
	string first_input, order_mode, numbers, number;
	bool valid_input = false; //bool for checking first input
	node *head = NULL, *temp = NULL, *ptr = NULL; //nodes to be used for constructing linked list

	cout << "Please enter the order mode (A/D): ";	//take choice of order (A/D)
	while (!valid_input)
	{
		cin >> first_input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore other strings in first line input

		if (first_input == "A" || first_input == "D") //case sensitive
		{
			order_mode = first_input; //store order as A or D
			valid_input = true;
		}
		else
		{
			cout << "Please enter the order mode again (A/D): ";
		}
	}

	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers); //take list of integers
	cout << endl;

	if (numbers.length() <= 0 || !isInt(numbers)) //if second input is just 'enter'
	{
		cout << "The list is empty at the end of the program and nothing is deleted." << endl;
		return 0; //stop further processing
	}
	istringstream iss(numbers); //stream for numbers
	while (iss >> number) //taking inputs one by one
	{	
		cout << "Next number: " << number << endl;
		bool is_deleted_any = false;
		
		if (!isExist(head, stoi(number))) //if not already in list
		{
			ptr = head;
			cout << "Deleted nodes:";
			while (ptr != NULL) //looping for each list element
			{
				temp = ptr->next;
				
				if (order_mode == "A") //for assending order
				{
					if (ptr->value > stoi(number))
					{
						cout << " " << ptr->value;
						DeleteOneNode(head, ptr); //DELETE ALL NODES WITH GREATER VALUE
						is_deleted_any = true;
					}
				}
				else if (order_mode == "D") //for dessending order
				{
					if (ptr->value < stoi(number))
					{
						cout << " " << ptr->value;
						DeleteOneNode(head, ptr); //DELETE ALL NODES WITH LOWER VALUE
						is_deleted_any = true;
					}
				}
				ptr = temp;	
			}
			if (!is_deleted_any) // if no nodes deleted in the current loop
			{
				cout << " None";
			}
			cout << endl;
			//add it as the last node
			head = AddList(head, stoi(number)); //add CURRENT INPUT to the list
			cout << "Appended: " << number << endl;
		}
		else
		{
			cout << number <<" is already in the list!" << endl;
		}
		printList(head); //Print list every iteration
		cout << endl;
	}
	DeleteList(head); //Delete the used list and print deleted elements
	return 0;
}