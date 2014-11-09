#include <iostream>
using namespace std;

//returns true if the value you are looking for is not in the x, y, or cel (all three bools are false)
bool check (bool,bool,bool);

//copies one matrix to another one
void copyarray(int m[][9],int n[][9]);

//returns true of there is a zero (blank) in the matrix
bool SearchArrayForZero(int m[][9]);

//outputs the sudoku puzzle to the screen
void displays (int m [][9]);

//-----------------------------------------------------------------------------
/*
 *Given a matrix, a number, and a specific x & y coordinate,
 *determin if the number is already in that cell/column/row
 *(calls searchY, searchX, and searchCEL)
 */
void position (int m[][9], int num, int  posy, int  posx, bool & y, bool & x, bool & cel);
void searchY (int m[][9], int num, int  posy, int  posx, bool & y);
void searchX (int m[][9], int num, int  posy, int  posx, bool & x);
//no redundancy (it doesn't search the whole cell because of the first two functions)
void searchCEL (int m[][9], int num, int  posy, int  posx, bool & cel);

//-----------------------------------------------------------------------------
/*
 *Given a blank spot in a matrix with specific x & y coordinates,
 *determin if it is the only blank in that cell/column/row
 */
void ifonlyZeroinY (int m[][9], int  posy, int  posx, bool & y);
void ifonlyZeroinX (int m[][9], int  posy, int  posx, bool & x);
void ifonlyZeroinCEL (int m[][9], int  posy, int  posx, bool & cel);

//-----------------------------------------------------------------------------
/*
 *Given a matrix and a number,
 *determin if the number is located somewhere in the cell
 *(does a complete search of the cell)
 */
void searchfullCEL (int m[][9], int num, int  posy, int  posx, bool & cel);

