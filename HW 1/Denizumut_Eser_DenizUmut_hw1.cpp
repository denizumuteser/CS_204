#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//denizUmutEser

//struct for storing each keyword and its direction
struct puzzlePiece
{
	int startingColumn;
	int startingRow;
	string direction;
	string orientation;
	string keyword;
	bool invalidLine;
};
//////////////////////////////////////////////////

//matrix printer//////////////////////////////////
void PrintMatrix(vector<vector<char> > m) { 
	for (int row = 0; row < m.size(); row++)
	{
		for (int column = 0; column < m[0].size(); column++)
		{
			cout << m[row][column] << " ";
		}
		cout << endl;
	}
}
//////////////////////////////////////////////////

//Keyword placer with input correctness checker///
int PlacePuzzle(vector<vector<char> > &m, puzzlePiece p) {
	//ERROR check for Invalid line//
	if (p.invalidLine)
	{
		cout << "Invalid line! Number of values is different than 5." << endl;
		return -1;
	}
	//ERROR check for starting point//
	else if (p.startingRow < 0 || p.startingColumn < 0 || p.startingRow >= m.size() || p.startingColumn >= m[0].size())
	{
		cout << "Starting point is out of range! Point: " << p.startingRow << "," << p.startingColumn << endl;
		return -1;
	}
	//ERROR check for direction//
	else if (p.direction != "u" && p.direction != "r" && p.direction != "d" && p.direction != "l")
	{
		cout << "Invalid input for direction! Direction: " << p.direction << endl;
		return -1;
	}
	//ERROR check for orientation//
	else if (p.orientation != "CW" && p.orientation != "CCW")
	{
		cout << "Invalid input for orientation! Orientation: " << p.orientation << endl;
		return -1;
	}
	//////////////////////////////

	//inits
	vector<vector<char> > tempMatrix = m;
	int index = 0, column = p.startingColumn, row = p.startingRow, numberOfturns = 0;
	string firstDirection = p.direction;
	bool isClockWise, canPlace = true;
	if (p.orientation == "CW")
	{
		isClockWise = true;
	}
	else if (p.orientation == "CCW")
	{
		isClockWise = false;
	}
	//////////////////////////////

	//try to place first character into starting point
	if (m[row][column] == '-')
	{
		m[row][column] = p.keyword[index];
		index++;
	}
	else
	{
		canPlace = false;
	}
	
	//keep placing
	while (index < p.keyword.length() && canPlace && numberOfturns <= 4)
	{
		//position iterations
		if (p.direction == "r")
		{
			if (column+1 < m[0].size() && m[row][column+1] == '-') //out of boundary check
			{
				column++;
				m[row][column] = p.keyword[index];
				index++;
				p.direction = firstDirection;
				numberOfturns = 0;
			}
			else //change direction
			{
				if (isClockWise)
				{
					p.direction = "d";
				}
				else
				{
					p.direction = "u";
				}
				numberOfturns++;
			}
		}
		else if (p.direction == "d")
		{
			if (row + 1 < m.size() && m[row+1][column] == '-') //out of boundary check
			{
				row++;
				m[row][column] = p.keyword[index];
				index++;
				p.direction = firstDirection;
				numberOfturns = 0;
			}
			else //change direction
			{
				if (isClockWise)
				{
					p.direction = "l";
				}
				else
				{
					p.direction = "r";
				}
				numberOfturns++;
			}
		}
		else if (p.direction == "l")
		{
			if (column > 0 && m[row][column-1] == '-') //out of boundary check
			{
				column--;
				m[row][column] = p.keyword[index];
				index++;
				p.direction = firstDirection;
				numberOfturns = 0;
			}
			else //change direction
			{
				if (isClockWise)
				{
					p.direction = "u";
				}
				else
				{
					p.direction = "d";
				}
				numberOfturns++;
			}
		}
		else if (p.direction == "u")
		{
			if (row > 0 && m[row-1][column] == '-') //out of boundary check
			{
				row--;
				m[row][column] = p.keyword[index];
				index++;
				p.direction = firstDirection;
				numberOfturns = 0;
			}
			else //change direction
			{
				if (isClockWise)
				{
					p.direction = "r";
				}
				else
				{
					p.direction = "l";
				}
				numberOfturns++;
			}
		}
	}
	if (index == p.keyword.length())
	{
		return 1; //Correct format and placed successfully
	}
	else
	{
		m = tempMatrix;
		return 0; //Correct format but cant placed
	}
}
//////////////////////////////////////////////////


int main()
{
	int matrixHeight, matrixWidth, outputChoice;
	string filename, line, firstLine, word;
	bool FilenameNotCorrect = true;
	vector<puzzlePiece> puzzle(0);

	//take filename input
	cout << "Please enter the name of the file: ";
	cin >> filename;
	
	while (FilenameNotCorrect)
	{
		ifstream input;
		input.open(filename.c_str()); //read txt file
		if (!input.fail()) //check name is correct or not
		{
			FilenameNotCorrect = false;
			getline(input, firstLine);
			istringstream iss(firstLine);
			iss >> matrixHeight >> matrixWidth;
			if (matrixHeight <= 0 || matrixWidth <= 0)
			{
				cout << "Invalid number for row and/or column!" << endl;
				return 0; //ERROR false format
			}

			while (getline(input, line)) //read line by line
			{
				puzzlePiece newPiece; //variable for sotring each puzzle direction
				istringstream iss(line);

				//Line count check//////////////
				string storage = "";
				int wordCount = 0;
				while (iss >> word)
				{
					storage += word + " ";
					wordCount++;
				}
				if (wordCount != 5)
				{
					newPiece.invalidLine = true;
				}
				////////////////////////////////
				else
				{
					istringstream iss2(storage);
					iss2 >> newPiece.keyword >> newPiece.startingRow >> newPiece.startingColumn >> newPiece.direction >> newPiece.orientation;
					newPiece.invalidLine = false;
				}
				puzzle.push_back(newPiece); //collect each keyword and direction in a vector
			}
		}
		else
		{
			cout << "File name is incorrect, please enter again: ";
			cin >> filename;
		}

	}
	//create matrix according to matrix dimensions
	vector<vector<char> > matrix(matrixHeight, vector<char> (matrixWidth));
	//put dash every slot
	for (int row = 0; row < matrixHeight; row++)
	{
		for (int column = 0; column < matrixWidth; column++)
		{
			matrix[row][column] = '-';
		}
	}
	/////////////////////////////////////////////

	//Main Loop//////////////////////////////////
	for (int piece = 0; piece < puzzle.size(); piece++)
	{
		outputChoice = PlacePuzzle(matrix, puzzle[piece]);
		if (outputChoice == 1) { //Correct format and placed
			cout << '"' << puzzle[piece].keyword << '"' << " was put into the matrix with given starting point: " << puzzle[piece].startingRow << "," << puzzle[piece].startingColumn << " direction: " << puzzle[piece].direction << " orientation: " << puzzle[piece].orientation << endl;
			PrintMatrix(matrix); //display updated matrix
			cout << endl;
		}
		else if (outputChoice == 0) //Correct Format but could not placed
		{
			cout << '"' << puzzle[piece].keyword << '"' << " could not be put into the matrix with given starting point: " << puzzle[piece].startingRow << "," << puzzle[piece].startingColumn << " direction: " << puzzle[piece].direction << " orientation: " << puzzle[piece].orientation << endl;
			PrintMatrix(matrix); //display updated matrix
			cout << endl;
		}
		
	}
	//End of Fun/////////////////////////////////
}