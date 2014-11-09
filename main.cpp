#include <iostream>
#include "Sudoku.hpp"
using namespace std;

//-----------------------------------------------------------------------------
int main ()
{
    bool x = false, y = false, cel = false;
    int truecount=0, truenum;
    int so [9][9] = {


        /*
        8,0,0, 4,0,6, 0,0,7,
        0,0,0, 0,0,0, 4,0,0,
        0,1,0, 0,0,0, 6,5,0,

        5,0,9, 0,3,0, 7,8,0,
        0,0,0, 0,7,0, 0,0,0,
        0,4,8, 0,2,0, 1,0,3,

        0,5,2, 0,0,0, 0,9,0,
        0,0,1, 0,0,0, 0,0,0,
        3,0,0, 9,0,2, 0,0,5};*/


        0,0,0, 7,8,0, 0,0,2,
        0,0,8, 0,0,0, 9,4,0,
        0,0,0, 0,3,0, 0,0,0,

        0,0,0, 0,7,0, 3,0,0,
        1,0,6, 4,0,0, 0,7,0,
        0,3,7, 8,0,9, 0,0,0,

        0,4,2, 0,0,0, 0,5,7,
        0,0,3, 0,4,0, 0,6,0,
        0,0,0, 6,0,0, 8,0,0};//25. solved.

	/*for (int y = 0; y < 9; y ++ )
		for (int x = 0; x < 9; x ++ )
			cin >> so[y][x];*/

	displays(so);

	for (int po = 0; po < 15; po ++ )//do
	{
		for (int posy = 0; posy < 9; posy ++ )
		{
			for (int posx = 0; posx < 9; posx ++ )//go through each cell
			{

                //SIMPLE, FILLING IN THE BLANK ALG///////////////  WORKS
				if(so[posy][posx]==0)//if cell is blank
				{
					for (int n = 1; n < 10 && truecount < 2; n ++ )//test each number for that blank cell
					{
						position (so, n, posy, posx, y,  x,  cel);

						if (check(y,x,cel))
						{
							truecount+=1;
							truenum = n;
						}

						x= false; y=false; cel=false;
					}

					if (truecount == 1)
						so[posy][posx]=truenum;

					truecount = 0;
				}
				//////////////////////////////////////////////////////////

				//////////////Filling in the blank of a cell///////////////// WORKS
                if(so[posy][posx]==0)//if cell is blank
                {
					bool LastCel, celtest;
					ifonlyZeroinCEL (so, posy, posx, LastCel);

					if (LastCel)//if it is the only blank space in a cell
					{
						for (int num = 1; num < 10; num ++)
						{
							searchfullCEL (so, num, posy, posx, celtest);
							if (!celtest)//if num not in cell
							{
								so[posy][posx] = num;
							}
							celtest = false;
						}
					}

					LastCel = false;
                }
                //////////////////////////////////////////////////////////////

                /////////////////////FILL IN THE BLANK OF ROW////////////////// WORKS
                if(so[posy][posx]==0)//if cell is blank
                {
					bool LastCel, celtest;
					ifonlyZeroinY  (so, posy, posx, LastCel);

					if (LastCel)//if it is the only blank space in a cell
					{
						for (int num = 1; num < 10; num ++)
						{
							searchY(so, num, posy, posx, celtest);
							if (!celtest)//if num not in cell
							{
								so[posy][posx] = num;
							}
							celtest = false;
						}
					}

					LastCel = false;
                }
                //////////////////////////////////////////////////////////

                /////////////////////FILL IN THE BLANK OF COL//////////////////WORKS
                if(so[posy][posx]==0)//if cell is blank
                {
					bool LastCel, celtest;
					ifonlyZeroinX  (so, posy, posx, LastCel);

					if (LastCel)//if it is the only blank space in a cell
					{
						for (int num = 1; num < 10; num ++)
						{
							searchX(so, num, posy, posx, celtest);
							if (!celtest)//if num not in cell
							{
								so[posy][posx] = num;
							}
							celtest = false;
						}
					}

					LastCel = false;
                }
                //////////////////////////////////////////////////////////

				///////////////////FENCED IN NUMBER ALG//////////////// WORKS
				if(so[posy][posx]==0)//if cell is blank
				{
                    int a = posy%3;
                    int b = posx%3;
                    bool y1, y2, x1, x2, cel1;

                    for (int num = 1; num < 10; num ++ )//test each number for that blank cell
					{
						searchfullCEL (so, num, posy, posx, cel1);

						searchY (so, num, posy+(-2*a + a/2 +1), posx+(-2*b + b/2 +1), y1);
						searchX (so, num, posy+(-2*a + a/2 +1), posx+(-2*b + b/2 +1), x1);

						searchY (so, num, posy+(-2*a + a/2 +1), posx+(-b -b/2 +2), y2);
						//searchX (so, num, posy+(-2*a + a/2 +1), posx+(-b -b/2 +2), x1);

						//searchY (so, num, posy+(-a -a/2 +2), posx+(-2*b + b/2 +1), y1);
						searchX (so, num, posy+(-a -a/2 +2), posx+(-2*b + b/2 +1), x2);

						//searchY (so, num, posy+(-a -a/2 +2), posx+(-b -b/2 +2), y2);
						//searchX (so, num, posy+(-a -a/2 +2), posx+(-b -b/2 +2), x2);

						if (!cel1 && y1 && y2 && x1 && x2)
						{
							 so[posy][posx] = num;
						}
						cel1=false; y1=false; y2=false; x1=false; x2=false;
                    }
                }
                //////////////////////////////////////////////////////////

                ///////////////////FENCED/BOXED IN NUMBER ALG////////////////WORKS
				if(so[posy][posx]==0)//if cell is blank
				{
                    int a = posy%3;
                    int b = posx%3;
                    bool y1, y2, x1, x2, cel1;

                    for (int num = 1; num < 10; num ++ )//test each number for that blank cell
					{
						searchfullCEL (so, num, posy, posx, cel1);

						searchY (so, num, posy+(-2*a + a/2 +1), posx+(-2*b + b/2 +1), y1);
						searchX (so, num, posy+(-2*a + a/2 +1), posx+(-2*b + b/2 +1), x1);

						searchY (so, num, posy+(-2*a + a/2 +1), posx+(-b -b/2 +2), y2);
						//searchX (so, num, posy+(-2*a + a/2 +1), posx+(-b -b/2 +2), x1);

						//searchY (so, num, posy+(-a -a/2 +2), posx+(-2*b + b/2 +1), y1);
						searchX (so, num, posy+(-a -a/2 +2), posx+(-2*b + b/2 +1), x2);

						//searchY (so, num, posy+(-a -a/2 +2), posx+(-b -b/2 +2), y2);
						//searchX (so, num, posy+(-a -a/2 +2), posx+(-b -b/2 +2), x2);
						if (!cel1)
						{
							if (x1)
							{
                                /*if (m[posy+(-2*a + a/2 +1)][posx+(-2*b + b/2 +1)] == num ||
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
		m[posy+ (-a -a/2 +2)][posx+ (0)] == num  )
                                {

					                {
							            so[posy][posx] = num;
							        }
							    } */
								if (x2)
								{
									if (so[posy+(0)][posx+ (-b -b/2 +2)] != 0 &&
										so[posy+(0)][posx+ (-2*b + b/2 +1)] != 0)
									{
										so[posy][posx] = num;
									}
								}
							}
							if (x1)
							{
								if (x2)
								{
									if (y2)
									{
										if (so[posy+(0)][posx+ (-2*b + b/2 +1)] != 0)
										{
											so[posy][posx] = num;
										}
									}
								    else if (y1)
									{
										if (so[posy+(0)][posx+ (-b -b/2 +2)] != 0)
										{
											so[posy][posx] = num;
										}
									}
								}
							}
							////////////////////////////
							if (y1)
							{
								if (y2)
								{
									if (x2)
									{
										if (so[posy+(-2*a + a/2 +1)][posx+ (0)] != 0)
										{
											so[posy][posx] = num;
										}
									}
									else if (x1)
									{
										if (so[posy+(-a -a/2 +2)][posx+ (0)] != 0)
										{
											so[posy][posx] = num;
										}
									}
								}
							}
							if (y1)
							{
								if (y2)
								{
									if (so[posy+(-2*a + a/2 +1)][posx+ (0)] != 0 &&
                                        so[posy+(-a -a/2 +2)][posx+ (0)] != 0)
									{
										so[posy][posx] = num;
									}
								}
							}
                        }


						cel1=false; y1=false; y2=false; x1=false; x2=false;
                    }
                }
                //////////////////////////////////////////////////////////

			}
		}
    }//while(SearchArrayForZero(so));


	displays(so);

    cout << "\n\n";

	//system ("PAUSE");
	return 0;
}

