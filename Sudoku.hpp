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
 *determin if the number is already in that cell/column/row.
 *It will return true or false the the boolean variable x/y/cel.
 *(void position calls searchY, searchX, and searchCEL)
 */
void position (int m[][9], int num, int  posy, int  posx, bool & y, bool & x, bool & cel);
void searchY (int m[][9], int num, int  posy, int  posx, bool & y);
void searchX (int m[][9], int num, int  posy, int  posx, bool & x);
/*
 *So there are no redundancies, searchCEL does not
 *search the whole cell because of the above two functions. It
 *only searches the four corners of a 3x3 matrix.
 */
void searchCEL (int m[][9], int num, int  posy, int  posx, bool & cel);

//-----------------------------------------------------------------------------
/*
 *Given a blank spot in a matrix with specific x & y coordinates,
 *determin if it is the only blank in that cell/column/row. If
 *it is the only blank, we know exactly which number it is.
 */
void ifonlyZeroinY (int m[][9], int  posy, int  posx, bool & y);
void ifonlyZeroinX (int m[][9], int  posy, int  posx, bool & x);
void ifonlyZeroinCEL (int m[][9], int  posy, int  posx, bool & cel);

//-----------------------------------------------------------------------------
/*
 *Given a 3x3 matrix and a number,
 *determin if the number is located somewhere in that 3x3 cell
 *(does a complete search of the cell). If it is found, return
 *true; othewise return false.
 */
void searchfullCEL (int m[][9], int num, int  posy, int  posx, bool & cel);

