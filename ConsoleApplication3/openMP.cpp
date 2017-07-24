//
// Programmed by Ibby M. Bouaraba [K1538649]
//Real time programming
//Assignment II Parallel programming “prey / predator"
//

#include "stdafx.h"
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <windows.h>
#include "ConsoleColor.h"

using namespace std;
using chrono::milliseconds;
using std::flush;
using std::this_thread::sleep_for;
#define arrayAlocation 250

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}

void slow_print(const string& message, unsigned int millis_per_char)
{// Range loops are "for each" constructs; here: for each character in the string
	for (const char c : message)
	{// flush is used to make sure the buffer is emptied to the terminal immediately
		cout << c << flush;
		// Ask the thread to sleep for at least n millis.
		sleep_for(milliseconds(millis_per_char));
	}
}

int rollDie10() {
	return (rand() % 10) + 1;
}
int rollDie32() {
	return (rand() % 32) + 1;
}

int main()
{
	//set window size for startup
	SetWindow(100, 40);
	// diclaring stuff needed
	int reply = 0;
	int empty = 0;
	int r = 0;
	int areaCheck[8];
	int ageCheck[8];
	int randomDeath;
	bool sharkBreed;
	bool fishBreed;
	bool snapMode = false;
	string message;

	system("Color 0a");

	cout << "" << endl;
	cout << "####### #######  ####### ###  ##   ###    ##  #####" << endl;
	cout << "#     # #    ##  ###  ## ###  ##   ###    ## ##" << endl;
	cout << "######  ######   ####### #######    ###  ##   ###" << endl;
	cout << "###     ##  ##   ###       ###       #####    ###" << endl;
	cout << "###     ##   ##  #######   ###        ###  #####" << endl;
	cout << "" << endl;
	cout << "####### #######  #######  #####   #######  #######  ####### ######" << endl;
	cout << "##   #  ###  ##  ###      ###  ## ##   ##    ###    ##   ## ##  ##" << endl;
	cout << "######  ######   #######  ###  ## #######    ###    ##   ## ######" << endl;
	cout << "###     ##  ##   ###      ###  ## ###  ##    ###    ##   ## ##  ##" << endl;
	cout << "###     ##   ##  #######  ######  ###  ##    ###     #####  ##   ##" << endl;
	cout << "" << endl;
	cout << "Programmed by ibby.b" << endl;
	cout << "warning may contain digital cellular automata.\n";
	cout << "" << endl;

	system("pause");
	system("cls");

	message = "Welcome to ibby's Prey vs Predator program.\n";
	slow_print(message, 30);
	message = "would you please define grid size between 0-249, parameter (X) \n";
	slow_print(message, 30);
	cin >> reply;
	const int Y = 0 + (reply + 2);
	message = "would you kindly also define grid size between 0-249, parameter (Y) \n";
	slow_print(message, 30);
	cin >> reply;
	const int X = 0 + (reply + 2);
	message = "please specifiy total number of runs, parameter (Runs) \n";
	slow_print(message, 30);
	cin >> reply;
	message = "Would you like to enable 'snap shot mode' (true or false) \n";
	slow_print(message, 30);
	cin >> message;
	system("pause");
	system("cls");

	if (message == "false") { snapMode = false; }
	if (message == "true") { snapMode = true; }
	const int RUNS = reply;


	int seedArray[arrayAlocation][arrayAlocation];
	int ageArray[arrayAlocation][arrayAlocation];
	int arrayB[arrayAlocation][arrayAlocation];
	int breedableB = 0;
	int	breedableA = 0;
	int shark = 0;
	int fish = 0;

	// Filling the grid with sudorandom generator //
	for (int nX = 1; nX < X; nX++)
	{
		for (int nY = 1; nY < Y - 1; nY++)
		{
			ageArray[nX][nY] = 0;

			r = rollDie10();
			if (r <= 5)
			{
				//fish
				seedArray[nX][nY] = 1;
				ageArray[nX][nY] = 1;
			}
			else
			{
				r = rollDie10();
				if (r <= 5)
				{
					//shark
					seedArray[nX][nY] = 2;
					ageArray[nX][nY] = 1;
				}
				else {
					// empty cell
					seedArray[nX][nY] = 0;
					ageArray[nX][nY] = 0;
				}
			}
		}
	}

	// write mirror cels for age array and seed array
	for (int nX = 0; nX <= X; nX++)
	{
		for (int nY = 0; nY < Y; nY++)
		{
			//top
			if ((nX == 0) && (nY > 0 && nY < Y))
			{
				seedArray[nX][nY] = seedArray[X - 1][nY];
				ageArray[nX][nY] = ageArray[X - 1][nY];
			}
			//bottom
			else if ((nY == X) && (nY > 0 && nY < Y))
			{
				seedArray[nX][nY] = seedArray[1][nY];
				ageArray[nX][nY] = ageArray[1][nY];
			}
			//left
			else if ((nY == 0) && (nX > 0 && nX < X))
			{
				seedArray[nX][nY] = seedArray[nX][Y - 1];
				ageArray[nX][nY] = ageArray[nX][Y - 1];
			}
			//right
			else if ((nX == X) && (nY > 0 && nY < Y))
			{
				seedArray[nX][nY] = seedArray[nX][1];
				ageArray[nX][nY] = ageArray[nX][1];
			}
			//corners
			else if ((nY == 0) && (nX == 0))
			{
				seedArray[nX][nY] = seedArray[X - 1][Y - 1];
				ageArray[nX][nY] = ageArray[X - 1][Y - 1];
			}
			else if ((nY == 0) && (nX == X))
			{
				seedArray[nX][nY] = seedArray[1][Y - 1];
				ageArray[nX][nY] = ageArray[1][Y - 1];
			}
			else if ((nY == Y) && (nX == 0))
			{
				seedArray[nX][nY] = seedArray[X - 1][1];
				ageArray[nX][nY] = ageArray[X - 1][1];

			}
			else if ((nY == Y) && (nX == X))
			{
				seedArray[nX][nY] = seedArray[1][1];
				ageArray[nX][nY] = ageArray[1][1];
			}
		}
	}

	// Printing the generated grid into the console


	for (int nX = 1; nX < X - 1; nX++)
	{
		for (int nY = 1; nY < Y - 1; nY++)
		{
			if (seedArray[nX][nY] == 0) { cout << blue << seedArray[nX][nY]; }
			if (seedArray[nX][nY] == 1) { cout << green << seedArray[nX][nY]; }
			if (seedArray[nX][nY] == 2) { cout << red << seedArray[nX][nY]; }
		}
		cout << endl;
	}

	//Set Window Size to X and Y parameters plus a little space
	SetWindow(Y + 10, X + 10);

	cout << "" << endl;
	message = "seed grid generated.\n";

	slow_print(message, 30);
	cout << "" << endl;
	system("pause");
	system("cls");

	// main loop of the program
	for (int GENNo = 1; GENNo <= RUNS; GENNo++)
	{

		// calculate new values and pass onto other array
		for (int nX = 1; nX < X; nX++)
		{
			for (int nY = 1; nY < Y; nY++)
			{
				areaCheck[0] = seedArray[nX - 1][nY - 1];
				areaCheck[1] = seedArray[nX][nY - 1];
				areaCheck[2] = seedArray[nX + 1][nY - 1];
				areaCheck[3] = seedArray[nX + 1][nY];
				areaCheck[4] = seedArray[nX + 1][nY + 1];
				areaCheck[5] = seedArray[nX][nY + 1];
				areaCheck[6] = seedArray[nX - 1][nY + 1];
				areaCheck[7] = seedArray[nX - 1][nY];
				ageCheck[0] = ageArray[nX - 1][nY - 1];
				ageCheck[1] = ageArray[nX][nY - 1];
				ageCheck[2] = ageArray[nX + 1][nY - 1];
				ageCheck[3] = ageArray[nX + 1][nY];
				ageCheck[4] = ageArray[nX + 1][nY + 1];
				ageCheck[5] = ageArray[nX][nY + 1];
				ageCheck[6] = ageArray[nX - 1][nY + 1];
				ageCheck[7] = ageArray[nX - 1][nY];
				//check the area around the cell to add up all of the varibles
				for (int areaSlot = 0; areaSlot <= 7; areaSlot++)
				{
					if (areaCheck[areaSlot] == 2)
					{
						shark = shark + 1;
						if (ageCheck[areaSlot] >= 3) { breedableB = breedableB + 1; }
					}
					else if (areaCheck[areaSlot] == 1)
					{
						fish = fish + 1;
						if (ageCheck[areaSlot] >= 2) { breedableA = breedableA + 1; }
					}
					else if (areaCheck[areaSlot] == 0)
					{
						empty = empty + 1;
					}
				}

				if (breedableA >= 3 && fish == 4) { fishBreed = true; }
				if (breedableB >= 3 && shark == 4) { sharkBreed = true; }

				//Empty cell rules
				//if cell is empty then fishes and sharks have a chance to breed
				if (seedArray[nX][nY] == 0)
				{
					if (fishBreed == true)
					{
						arrayB[nX][nY] = 1;
						ageArray[nX][nY] = 1;
					}
					else if (sharkBreed == true)
					{
						arrayB[nX][nY] = 2;
						ageArray[nX][nY] = 1;
					}
					else
					{
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
				}

				//Fish rules
				if (seedArray[nX][nY] == 1)
				{
					//dies of old age //note age array needs ghost cells
					if (ageArray[nX][nY] == 10)
					{
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					//dies of over crowding or over population
					else if (fish >= 8)
					{
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					// fish is converted strait to shark food, one way ticket...
					else if (shark >= 5)
					{
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					// if all gos well for the fish it lives to see its next birthday
					else
					{
						ageArray[nX][nY] = ageArray[nX][nY] + 1;
						arrayB[nX][nY] = 1;
					}
				}

				//shark rules
				if (seedArray[nX][nY] == 2)
				{
					//roll the dice ! sharks have a one in 32 chance of just dieing randomly.
					//sharks only live till 20
					randomDeath = rollDie10();
					if (randomDeath == 13 || ageArray[nX][nY] >= 20)
					{
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					//shark dies of starvation
					else if (shark >= 6 && fish == 0)
					{
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					//shark lives to fight another day..yay
					else
					{
						ageArray[nX][nY] = ageArray[nX][nY] + 1;
						arrayB[nX][nY] = 2;
					}
				}

				//resetting all ints and bools for next round on the forloop
				fishBreed = false;
				sharkBreed = false;
				breedableA = 0;
				breedableB = 0;
				shark = 0;
				fish = 0;
				empty = 0;
			}
		}

		// print new Generation
		for (int nX = 1; nX < X; nX++)
		{
			for (int nY = 1; nY < Y - 1; nY++)
			{
				if (arrayB[nX][nY] == 0)
				{
					cout << blue << arrayB[nX][nY];
				}
				if (arrayB[nX][nY] == 1)
				{
					cout << green << arrayB[nX][nY];
				}
				if (arrayB[nX][nY] == 2)
				{
					cout << red << arrayB[nX][nY];
				}
			}
			cout << endl;
		}

		cout << "" << endl;
		cout << "Run no. " << GENNo << endl;

		//reload into seed array for next generation to process
		for (int nX = 1; nX < X; nX++)
		{
			for (int nY = 1; nY < Y - 1; nY++)
			{
				seedArray[nX][nY] = arrayB[nX][nY];
			}
		}

		//write to mirror cels again for next cycle in the for loop
		for (int nX = 0; nX < X; nX++)
		{
			for (int nY = 0; nY < Y; nY++)
			{
				//top
				if ((nX == 0) && (nY > 0 && nY < Y))
				{
					seedArray[nX][nY] = seedArray[X - 1][nY];
					ageArray[nX][nY] = ageArray[X - 1][nY];
				}
				//bottom
				else if ((nY == X) && (nY > 0 && nY < Y))
				{
					seedArray[nX][nY] = seedArray[1][nY];
					ageArray[nX][nY] = ageArray[1][nY];
				}
				//left
				else if ((nY == 0) && (nX > 0 && nX < X))
				{
					seedArray[nX][nY] = seedArray[nX][Y - 1];
					ageArray[nX][nY] = ageArray[nX][Y - 1];
				}
				//right
				else if ((nX == X) && (nY > 0 && nY < Y))
				{
					seedArray[nX][nY] = seedArray[nX][1];
					ageArray[nX][nY] = ageArray[nX][1];
				}
				//corners
				else if ((nY == 0) && (nX == 0))
				{
					seedArray[nX][nY] = seedArray[X - 1][Y - 1];
					ageArray[nX][nY] = ageArray[X - 1][Y - 1];
				}
				else if ((nY == 0) && (nX == X))
				{
					seedArray[nX][nY] = seedArray[1][Y - 1];
					ageArray[nX][nY] = ageArray[1][Y - 1];
				}
				else if ((nY == Y) && (nX == 0))
				{
					seedArray[nX][nY] = seedArray[X - 1][1];
					ageArray[nX][nY] = ageArray[X - 1][1];

				}
				else if ((nY == Y) && (nX == X))
				{
					seedArray[nX][nY] = seedArray[1][1];
					ageArray[nX][nY] = ageArray[1][1];
				}
			}
		}

		if (snapMode == true) { system("pause"); }

		system("cls");
	}

	message = "		Run Compleate! \nThank you for using this application.\n";
	slow_print(message, 30);
	system("pause");
	system("cls");
	return 0;
}
