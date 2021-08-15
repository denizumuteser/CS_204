#include "denizumut_Eser_DenizUmut_hw6_Board.h"

template <class Type>
Board<Type>::Board()
{
}

template <class Type>
Board<Type>::Board(int row, int column)
{

	Matrix = new Card<Type>*[row]; //dynamic matrix from cards
	for (int i = 0; i < row; i++)
	{
		Matrix[i] = new Card<Type>[column];
	}
	rows = row;
	columns = column;
}

template <class Type>
Board<Type>::~Board()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] Matrix[i]; //delete each column
		Matrix[i] = NULL;
	}
	delete[] Matrix; //delete rows
	Matrix = NULL;
}

template <class Type>
void Board<Type>::readBoardFromFile(ifstream& input)
{
	string line;
	Type a;
	for (int i = 0; i < rows; i++)
	{
		getline(input, line);
		istringstream iss(line);
		for (int ii = 0; ii < columns; ii++)
		{
			iss >> a; //first take input into a type var
			Matrix[i][ii].data = a; //take input into card data
			Matrix[i][ii].isFaceClosed = true; //initilize each card face closed
		}
	}
}

template <class Type>
void Board<Type>::displayBoard()
{
	for (int i = 0; i < rows; i++)
	{
		for (int ii = 0; ii < columns; ii++)
		{
			if (Matrix[i][ii].isFaceClosed)
			{
				cout << "X "; //x for closed cards
			}
			else
			{
				cout << Matrix[i][ii].data << " ";
			}
		}
		cout << endl;
	}
}

template <class Type>
void Board<Type>::closeCard(int row, int column)
{
	Matrix[row][column].isFaceClosed = true;
}

template <class Type>
int Board<Type>::getRow()
{
	return rows;
}

template <class Type>
int Board<Type>::getColumn()
{
	return columns;
}

template<class Type>
Type Board<Type>::getCardData(int row, int column)
{
	Matrix[row][column].isFaceClosed = false; //change card face
	return Matrix[row][column].data; //return card data
}

template<class Type>
bool Board<Type>::isCardOpen(int row, int column)
{
	if (row>=rows || column >= columns || row < 0 || column < 0)
	{
		return false;
	}
	return !Matrix[row][column].isFaceClosed;
}
