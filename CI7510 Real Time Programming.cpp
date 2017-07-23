// CI7510 Real Time Programming Assignment II
// Programmed by Ibby M Bouaraba


#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <iostream>
#include "stdafx.h"


#define XGRID 30    
#define YGRID 30
#define GENERATIONS 100
using namespace std;

/*	for (int i = 0; i < XGRID; i++)
	{
		for (int j = 0; j < YGRID; j++)
		{
			cout << "a[" << i << "][" << j << "]: ";
			cout << grid_OLD[i][j] << endl;
		}
	}
	*/

int main()
{
	int nX, nY, i, j = 0;
	float r;

	nX = XGRID + 2;
	nY = YGRID + 2;

	int gridOLD[XGRID][YGRID];
	int gridNEW[XGRID][YGRID];

	for (nX = 1; nX <= XGRID; nX++)
	{
		for (nY = 1; nY <= YGRID; nY++)
		{
			r = rand() / ((float)RAND_MAX + 1);
			if (r<0.6)
			{
				gridOLD[nX][nY] = 0;
			}
			else
			{
				gridOLD[nX][nY] = 1;
			}
		}
	}
	system("pause");
	return 0;
}