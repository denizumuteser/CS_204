#pragma	once

#ifndef _DENIZUMUT_ESER_DENIZUMUT_HW6_PLAYER_H
#define _DENIZUMUT_ESER_DENIZUMUT_HW6_PLAYER_H

using namespace std;

#include "denizumut_Eser_DenizUmut_hw6_Board.h"

template <class Type>
class Player
{
private:
	Board<Type> & board; //sharing board object using obj sharing concept, with refernce variable method
	int score;

public:
	Player(); //default constructor

	Player(Board<Type> & b); //parametric constructor

	Type openCard(int row, int column); 
	//open corresponding card

	bool validMove(int row, int column);
	//return validation of row column values

	void increaseNumberOfSuccess();
	//increase score by one

	int getNumberOfSuccess();
	//get score
	
};

#include "denizumut_Eser_DenizUmut_hw6_Player.cpp"
#endif