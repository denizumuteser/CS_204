#pragma once

#ifndef _DENIZUMUT_ESER_DENIZUMUT_HW6_BOARD_H
#define _DENIZUMUT_ESER_DENIZUMUT_HW6_BOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

template <class Type>
struct Card
{
	Type data; //for storing card data
	bool isFaceClosed; //for storing card face open/close	

	Card() {} //default constructor

	Card(Type d, bool face) //parametrix constructor
	{
		data = d;
		isFaceClosed = face;
	}
};

template <class Type>
class Board
{
private:
	Card<Type>** Matrix; //matrix which can keep any kind of data type
	int rows; //row count
	int columns; //column count

public:

	Board(); //default constructor

	Board(int row, int column); //create board matrix here dynamically

	~Board(); //delete dynamic memory //make pointers null

	void readBoardFromFile(ifstream& input);
		//fill the board using input stream
		//initilaze satus of card faces
		//input is at second line

	void displayBoard();
		//display board matrix
		//x for closed cards

	void closeCard(int row, int column);
		//change card face status to closed

	int getRow();
		//return row count

	int getColumn();
		//return column count

	//future functions to interact with the player class
	//accessor, mutators

	Type getCardData(int row, int column);
	//return card data
	//change card face to open

	bool isCardOpen(int row, int column);
	//return true if card face is open

};

#include "denizumut_Eser_DenizUmut_hw6_Board.cpp"
#endif

