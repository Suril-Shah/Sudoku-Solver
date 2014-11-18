#include <iostream>
#include "Sudoku.hpp"
using namespace std;

//-----------------------------------------------------------------------------
void displays (int so[][9])
{
    cout << endl;
    for (int y = 0; y < 9; y ++ )
    {
        cout << endl;

        if (y%3 == 0)
            cout << "------------" << endl;

        for (int x = 0; x < 9; x ++ )
        {
            if (so[y][x] == 0)
                cout << '_';
            else
                cout << so[y][x];
            if ((x+1)%3 == 0)
                cout << '|';
        }
    }
    cout << endl;
}
//-----------------------------------------------------------------------------
void position (int m[][9], int num, int  posy, int  posx, bool & y, bool & x, bool & cel)
{
	searchY (m, num, posy, posx, y);
	searchX (m, num, posy, posx, x);
	searchCEL (m, num, posy, posx, cel);
}
//-----------------------------SEARCHING IN THE Y------------------------------
//-----------------------------------------------------------------------------
void searchY (int m[][9], int num, int  posy, int  posx, bool & y)
{
   for (int b = (posy+1); b < 9; b++)
	   if (m[b][posx] == num)
		   y = true;
   for (int b = (posy-1); b > -1; b--)
	   if (m[b][posx]== num)
		   y = true;
}
//-----------------------------------------------------------------------------
void ifonlyZeroinY (int m[][9], int  posy, int  posx, bool & y)
{
   int total = 0;
   for (int b = (posy+1); b < 9; b++)
	   if (m[b][posx] != 0)
		   total ++;

   for (int b = (posy-1); b > -1; b--)
	   if (m[b][posx] != 0)
		   total ++;

   if (total == 8)
      y = true;
}
//-----------------------------SEARCHING IN THE X------------------------------
//-----------------------------------------------------------------------------
void searchX (int m[][9], int num, int  posy, int  posx, bool & x)
{
   for (int b = posx+1; b <9; b++)//left of the box
	   if (m[posy][b] == num)
		   x = true;

   for (int b = posx-1; b > -1; b--)//right of the box
	   if (m[posy][b]== num)
		   x = true;
}
//-----------------------------------------------------------------------------
void ifonlyZeroinX (int m[][9], int  posy, int  posx, bool & x)
{
   int total = 0;
   for (int b = posx+1; b <9; b++)
	   if (m[posy][b] != 0)
		   total ++;

   for (int b = posx-1; b > -1; b--)
	   if (m[posy][b] != 0)
		   total ++;

   if (total == 8)
      x = true;
}
//-----------------------------SEARCHING EACH CELL-----------------------------
//-----------------------------------------------------------------------------
void searchCEL (int m[][9], int num, int  posy, int  posx, bool & cel)
{
	int a = posy%3, b = posx%3;

	if (m[posy+(-2*a + a/2 +1)][posx+(-2*b + b/2 +1)] == num ||
		m[posy+(-2*a + a/2 +1)][posx+(-b -b/2 +2)] == num ||
		m[posy+(-a -a/2 +2)][posx+(-2*b + b/2 +1)] == num ||
		m[posy+(-a -a/2 +2)][posx+(-b -b/2 +2)] == num)
	{
		cel = true;
	}
}
//-----------------------FULLY SEARCHING EACH CELL-----------------------------
//-----------------------------------------------------------------------------
void searchfullCEL (int m[][9], int num, int  posy, int  posx, bool & cel)
{//cel = true if num is in the cell
	int a = posy%3, b = posx%3;

	if (m[posy+(-2*a + a/2 +1)][posx+(-2*b + b/2 +1)] == num ||
		m[posy+(-2*a + a/2 +1)][posx+(-b -b/2 +2)] == num ||
		m[posy+(-a -a/2 +2)][posx+(-2*b + b/2 +1)] == num ||
		m[posy+(-a -a/2 +2)][posx+(-b -b/2 +2)] == num ||

		m[posy+ (0)][posx+ (-b -b/2 +2)] == num ||
				//(m[posy+ (0)][posx+ (-b -b/2 +2)] != num &&
				// m[posy+ (0)][posx+ (-b -b/2 +2)] != 0) ||
		m[posy+ (0)][posx+ (-2*b + b/2 +1)] == num ||
			   //(m[posy+ (0)][posx+ (-2*b + b/2 +1)] != num &&
				// m[posy+ (0)][posx+ (-2*b + b/2 +1)] != 0) ||
		m[posy+ (-2*a + a/2 +1)][posx+ (0)] == num ||
				//(m[posy+ (-2*a + a/2 +1)][posx+ (0)] != num &&
				// m[posy+ (-2*a + a/2 +1)][posx+ (0)] != 0) ||
		m[posy+ (-a -a/2 +2)][posx+ (0)] == num //||
				//(m[posy+ (-a -a/2 +2)][posx+ (0)] != num &&
				// m[posy+ (-a -a/2 +2)][posx+ (0)] != 0)
	   )

	{
		cel = true;
	}
}
//-----------------------------------------------------------------------------
void ifonlyZeroinCEL (int m[][9], int  posy, int  posx, bool & cel)
{
	int a = posy%3, b = posx%3;

	if (m[posy+(-2*a + a/2 +1)][posx+(-2*b + b/2 +1)] != 0 &&
		m[posy+(-2*a + a/2 +1)][posx+(-b -b/2 +2)] != 0 &&
		m[posy+(-a -a/2 +2)][posx+(-2*b + b/2 +1)] != 0 &&
		m[posy+(-a -a/2 +2)][posx+(-b -b/2 +2)] != 0 &&

		m[posy+(0)][posx+ (-b -b/2 +2)] != 0&&
		m[posy+(0)][posx+ (-2*b + b/2 +1)] != 0 &&
		m[posy+(-2*a + a/2 +1)][posx+ (0)] != 0 &&
		m[posy+(-a -a/2 +2)][posx+ (0)] != 0)

	{
		cel = true;
	}
}
//----------------------------Miscellaneous------------------------------------
//-----------------------------------------------------------------------------
bool check (bool y, bool x, bool cel)
{//returns true if the value you are looking for is not in the x, y, or cel
     return (x == false && y == false && cel == false);
}
//-----------------------------------------------------------------------------
void copyarray (int n [][9], int so[][9])
{
    for (int y = 0; y < 9; y ++ )
        for (int x = 0; x < 9; x ++ )
            n[y][x] = so[y][x];
}
//-----------------------------------------------------------------------------
bool SearchArrayForZero(int so[][9])
{
    bool zero = false;
    for (int y = 0; y < 9; y ++ )
        for (int x = 0; x < 9; x ++ )
            if (so[y][x]==0)
                zero = true;

     return (zero);
}
//-----------------------------------------------------------------------------

/*
        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,

        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,

        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0};
//////////////////////////////////
------------
5__|___|___|
_8_|__7|_1_|
6__|___|285|
------------
__5|6_9|___|
9_3|_4_|6_7|
___|7_1|4__|
------------
174|___|__8|
_6_|5__|_7_|
___|___|__2|
////////////////
------------
5__|___|___|
48_|__7|_1_|
6__|___|285|
------------
745|6_9|___|
913|_4_|6_7|
826|7_1|4__|
------------
174|___|__8|
26_|5__|_7_|
3__|___|__2|
*/

