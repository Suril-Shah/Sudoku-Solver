/*
 *Project started Feb. 2012.
 *This application was created to imitate how a person would solve a
 *sudoku puzzle. For this reason, algorithms were based off of how
 *someone would eliminate numbers one by one while thry search through
 *the 9 rows, columns, and cells. So far 6 algorithms have been implemented.
 */

#include <iostream>
#include "Sudoku.hpp"
using namespace std;

int main ()
{
    /*
     *x/y/cel are booleans used quite alot in determining
     *if a number is in a particular location.
     */
    bool x = false, y = false, cel = false;
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

        0,6,5, 0,0,0, 0,0,0,
        0,0,2, 0,0,0, 0,0,0,
        0,1,4, 0,0,0, 0,0,0,

        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0,

        0,0,0, 0,0,0, 0,0,0,
        3,0,0, 0,0,0, 0,0,0,
        0,0,0, 0,0,0, 0,0,0};

        /*0,0,0, 7,8,0, 0,0,2,
        0,0,8, 0,0,0, 9,4,0,
        0,0,0, 0,3,0, 0,0,0,

        0,0,0, 0,7,0, 3,0,0,
        1,0,6, 4,0,0, 0,7,0,
        0,3,7, 8,0,9, 0,0,0,

        0,4,2, 0,0,0, 0,5,7,
        0,0,3, 0,4,0, 0,6,0,
        0,0,0, 6,0,0, 8,0,0};//25. solved.*/

    //Display the unsolved puzzle initially.
	displays(so);

	for (int po = 0; po < 6; po ++ )//Run set of algorithms 6 times.
	{
		for (int posy = 0; posy < 9; posy ++ )
		{
			for (int posx = 0; posx < 9; posx ++ )//Go through each cell in the puzzle.
			{
                /*
                 *Simple filling in the blank algorithm. It will see if a
                 *particular position is the only blank in its row/column/cell.
                 *If there ar mulitple numbers that can go in that position,
                 *the position will remain blank.
                 *
                 *Test each number for that blank cell.
                 *Stop if we find 2 numbers that can fit.
                 *Ideally, we only want 1 possible solution,
                 *but if we find 2, we have to stop because
                 *this algorithm won't work.
                 *
                 *Works as expected.
                 */
                //If the particular position is blank, try to fill it.
				if(so[posy][posx] == 0)
				{
				    int posibilities = 0, truenum;

				    //Try each number from 1 to 9; stop if we have more than one solution.
					for (int num = 1; num <= 9 && posibilities < 2; num ++ )
					{
						position (so, num, posy, posx, y,  x, cel);

						if (check(y,x,cel))
						{
						    //Incrment the posibilites counter, and save the number
						    //if it fits in this blank spot.
							posibilities += 1;
							truenum = num;
						}
                        //Reset.
						x = false; y = false; cel = false;
					}
                    //As long as only one number fits into this blank, fill it in.
					if (posibilities == 1)
						so[posy][posx] = truenum;

                    //Reset.
					posibilities = 0;
				}

				/*
				 *If a particular number being tested for a blank
				 *cannot be found within its 3x3 cell, but
				 *it can be found in both adjacent rows
				 *and both adjacent columns to the blank, then
				 *that particular number has to fill in that blank.
				 *
				 *The number is essentially "fenced-in".
				 *
				 *Works as expected.
				 */
                //If the position is still blank, try next algo.
				if(so[posy][posx] == 0)
				{
				    //This gives us the blank's relative position within the 3x3 cell.
                    int a = posy%3;
                    int b = posx%3;

                    bool y1, y2, x1, x2, cel1;

                    //Try each number from 1 to 9.
                    for (int num = 1; num <= 9; num ++)
					{
						searchfullCEL (so, num, posy, posx, cel1);

                        //Test first adjacent column and row.
						searchY (so, num, posy+(-2*a + a/2 +1), posx+(-2*b + b/2 +1), y1);
						searchX (so, num, posy+(-2*a + a/2 +1), posx+(-2*b + b/2 +1), x1);

                        //Test second adjacent column and row.
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

                /*
                 *Similar to the previous algo, except that this one
                 *looks at other adjacent numbers that can "fence-in"
                 *a particular value.
                 *
                 *Works as expected.
                 */
				//If the position is still blank, try next algo.
				if(so[posy][posx]==0)
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
								if (x2)
								{
									if (so[posy+(0)][posx+ (-b -b/2 +2)] != 0 &&
										so[posy+(0)][posx+ (-2*b + b/2 +1)] != 0)
									{
									    //|_ _ _|_ 3 _|_ _ _|
									    //|2 x 1|_ _ _|_ _ _|
									    //|_ _ _|_ _ _|3 _ _|
										so[posy][posx] = num;
									}
									else if (y2)
									{
										if (so[posy+(0)][posx+ (-2*b + b/2 +1)] != 0)
										{
										    //|_ _ _|_ 3 _|_ _ _|
                                            //|_ x 2|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|3 _ _|
                                            //___________________
                                            //|_ _ _|_ _ _|_ _ _|
                                            //|3 _ _|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|_ _ _|
											so[posy][posx] = num;
										}
									}
								    else if (y1)
									{
										if (so[posy+(0)][posx+ (-b -b/2 +2)] != 0)
										{
										    //|_ _ _|_ 3 _|_ _ _|
                                            //|2 x _|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|3 _ _|
                                            //___________________
                                            //|_ _ _|_ _ _|_ _ _|
                                            //|_ _ 3|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|_ _ _|
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
									    //|_ 2 _|_ _ _|_ _ _|
                                        //|_ x _|_ _ _|_ _ _|
                                        //|_ 1 _|_ _ _|_ _ _|
                                        //___________________
                                        //|_ _ _|_ _ _|_ _ _|
                                        //|3 _ _|_ _ _|_ _ _|
                                        //|_ _ _|_ _ _|_ _ _|
                                        //___________________
                                        //|_ _ _|_ _ _|_ _ _|
                                        //|_ _ 3|_ _ _|_ _ _|
                                        //|_ _ _|_ _ _|_ _ _|
										so[posy][posx] = num;
									}
									else if (x2)
									{
										if (so[posy+(-2*a + a/2 +1)][posx+ (0)] != 0)
										{
										    //|_ _ _|_ 3 _|_ _ _|
                                            //|_ x _|_ _ _|_ _ _|
                                            //|_ 2 _|_ _ _|_ _ _|
                                            //___________________
                                            //|_ _ _|_ _ _|_ _ _|
                                            //|3 _ _|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|_ _ _|
                                            //___________________
                                            //|_ _ _|_ _ _|_ _ _|
                                            //|_ _ 3|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|_ _ _|
											so[posy][posx] = num;
										}
									}
									else if (x1)
									{
										if (so[posy+(-a -a/2 +2)][posx+ (0)] != 0)
										{
										    //|_ 2 _|_ _ _|_ _ _|
                                            //|_ x _|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|3 _ _|
                                            //___________________
                                            //|_ _ _|_ _ _|_ _ _|
                                            //|3 _ _|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|_ _ _|
                                            //___________________
                                            //|_ _ _|_ _ _|_ _ _|
                                            //|_ _ 3|_ _ _|_ _ _|
                                            //|_ _ _|_ _ _|_ _ _|
											so[posy][posx] = num;
										}
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
    }

    //Display solved puzzle.
	displays(so);

    cout << "\n\n";

	//system ("PAUSE");
	return 0;
}
