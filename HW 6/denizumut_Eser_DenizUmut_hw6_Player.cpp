#include "denizumut_Eser_DenizUmut_hw6_Player.h"

template <class Type>
Player<Type>::Player()
{    
}

template <class Type>
Player<Type>::Player(Board<Type> & b) 
    : board(b), score(0) //take board as refernce in order to give each player the same board
{ }

template <class Type>
Type Player<Type>::openCard(int row, int column)
{
    return board.getCardData(row, column); 
    //return card data also opens the card
}

template <class Type>
bool Player<Type>::validMove(int row, int column)
{
    if (board.isCardOpen(row, column))
    {
        return false; //if card is already open
    }
    if ((board.getRow()-1 < row) || (board.getColumn()-1 < column))
    {
        return false; //if given position is not on table
    }
    if (row < 0 || column < 0)
    {
        return false;
    }
    return true; //else
}

template <class Type>
void Player<Type>::increaseNumberOfSuccess()
{
    score++;
}

template <class Type>
int Player<Type>::getNumberOfSuccess()
{
    return score;
}
