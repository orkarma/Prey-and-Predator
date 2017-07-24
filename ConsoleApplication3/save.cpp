// Programmed by Ibby M Bouaraba
// "A game of life and death" RTP Assignment II

#include "stdafx.h"
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <iostream>

#define XGRID 20    
#define YGRID 30
#define GENERATIONS 100
using namespace std;
/*void seedGrid()
{
//int seedGrid(const int[][], int)

//int seedArray[XGRID][YGRID];

//int seedArray[X][Y];
//int(*seedArray)[XGRID + 2] = new int[NI + 2][NJ + 2];
//seedGrid(seedArray[X][Y]);

}
*/

int main()
{
	// diclaring stuff needed
	int X = XGRID;
	int Y = YGRID;

	int r = 0;

	int seedArray[XGRID][YGRID];
	int ageArray[XGRID][YGRID];
	int arrayB[XGRID][YGRID];

	int shark = 0;
	int fish = 0;
	int empty = 0;
	int areaSlot = 1;
	int areaCheck[8];
	int randomDeath;
	int breedableA = 0;
	int breedableB = 0;

	bool sharkBreed;
	bool fishBreed;
	XGRID + 2;
	YGRID + 2;

	// Filling the grid with sudorandom generator //
	for (int nX = 1; nX <= XGRID; nX++)
	{
		for (int nY = 1; nY <= YGRID; nY++)
		{

			ageArray[nX][nY] = 0;
			r = rand() % 10;
			if (r <= 5)
			{
				// Generating fishes
				seedArray[nX][nY] = 1;
			}
			else
			{
				r = rand() % 10;
				if (r <= 5)
				{
					// Breeding sharks
					seedArray[nX][nY] = 2;
				}
				else {
					// empty cell
					seedArray[nX][nY] = 0;
				}
			}
		}
	}



	for (int GENNo = 1; GENNo <= GENERATIONS; GENNo++)
	{
		// Printing the generated grid into the console
		for (int nX = 1; nX <= XGRID; nX++)
		{
			for (int nY = 1; nY <= YGRID; nY++)
			{
				cout << seedArray[nX][nY];
			}
			cout << endl;
		}
		system("pause");
		system("cls");

		// pass seedgrid onto secondary arrays
		for (int nX = 1; nX <= XGRID; nX++)
		{
			for (int nY = 1; nY <= YGRID; nY++)
			{
				//arrayB[nX][nY] = seedArray[nX][nY];
			}
		}


		// calculate new values and pass onto other array


		for (int nX = 1; nX <= XGRID; nX++)
		{
			for (int nY = 1; nY <= YGRID; nY++)
			{


				areaCheck[1] = seedArray[nX - 1][nY - 1];
				areaCheck[2] = seedArray[nX][nY - 1];
				areaCheck[3] = seedArray[nX + 1][nY - 1];
				areaCheck[4] = seedArray[nX + 1][nY];
				areaCheck[5] = seedArray[nX + 1][nY + 1];
				areaCheck[6] = seedArray[nX][nY + 1];
				areaCheck[7] = seedArray[nX - 1][nY + 1];
				areaCheck[8] = seedArray[nX - 1][nY];

				for (areaSlot = 1; areaSlot <= 8; areaSlot++)
				{
					if (areaCheck[areaSlot] == 2)
					{
						shark = shark + 1;
						if (ageArray[nX][nY] >= 3) { breedableB += 1; }
					}
					else if (areaCheck[areaSlot] == 1)
					{
						fish = fish + 1;
						if (ageArray[nX][nY] >= 2) { breedableA += 1; }
					}
					else
					{
						empty = empty + 1;
					}
				}
				if (breedableA >= 3) { fishBreed = true; }
				if (breedableB >= 3) { sharkBreed = true; }

				if (seedArray[nX][nY] == 0 && (sharkBreed == true || fishBreed == true))
				{
					//Empty
					//age needs to be added later(done)
					if ((fish <= 4) && (shark >= 4)) { arrayB[nX][nY] = 1; }
					else if ((shark <= 4) && (fish >= 4)) { arrayB[nX][nY] = 2; }
					else {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
				}
				else if (seedArray[nX][nY] == 1)
				{
					//Fish
					if (ageArray[nX][nY] == 10) {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					else if (fish >= 8) {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					else if (shark >= 5) {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}

					else {
						ageArray[nX][nY] += 1;
						arrayB[nX][nY] = 1;
					}
				}
				else if (seedArray[nX][nY] == 2)
				{
					//shark
					randomDeath = rand() % 32;
					if (randomDeath == 13) {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					else if ((shark >= 6) && (fish == 0)) {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					else if (ageArray[nX][nY] == 20) {
						ageArray[nX][nY] = 0;
						arrayB[nX][nY] = 0;
					}
					else {
						ageArray[nX][nY] += 1;
						arrayB[nX][nY] = 2;
					}
				}
				else
				{
					//error
					arrayB[nX][nY] = 8;
				}

				//arrayB[nX][nY] = seedArray[nX][nY];
				fishBreed = false;
				sharkBreed = false;
				shark = 0;
				fish = 0;
				empty = 0;

			}
		}

		// print new Generation
		for (int nX = 1; nX <= XGRID; nX++)
		{
			for (int nY = 1; nY <= YGRID; nY++)
			{
				cout << arrayB[nX][nY];
			}
			cout << endl;
		}





		/*
		/// print age array

		for (int nX = 1; nX <= XGRID; nX++)
		{
		for (int nY = 1; nY <= YGRID; nY++)
		{
		cout << ageArray[nX][nY];
		}
		cout << endl;
		}


		*/





		//reload into seed array for next generation to process
		for (int nX = 1; nX <= XGRID; nX++)
		{
			for (int nY = 1; nY <= YGRID; nY++)
			{
				arrayB[nX][nY] = seedArray[nX][nY];
			}
		}
		system("pause");
		system("cls");
	}


	return 0;
}

//for (n = 0; n<NSTEPS; n++)
