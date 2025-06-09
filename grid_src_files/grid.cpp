/*
 * grid.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: bekdouche
 */




#include "grid.h"

int G_grid[ROWS][COLS];

int normalize_coordinate(int coordinate, int maximumValue, int factor)
{
	return floor(coordinate*factor/maximumValue);
}

void update_grid()
{
	int iX, iY;
	fill(*G_grid, *G_grid + ROWS*COLS, 0);
	for (int k=0; k<int(G_vecSquares.size()); k++)
	{
		iX = normalize_coordinate(G_vecSquares[k].x+SIZE/2, WIDTH, COLS);
		iY = normalize_coordinate(G_vecSquares[k].y+SIZE/2, HEIGHT-SIZE, ROWS);
		G_grid[iY][iX] = G_vecSquares[k].value;
	}
}

void empty_selected_grid(int squareID)
{
	if (G_vecSquares[squareID].locked == true)
	{
		int collection = get_chained_squares_collection(squareID);
		for (int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
		{
			int iX = normalize_coordinate(G_vecSquares[G_vecChainedSquares[collection][j]].x+SIZE/2, WIDTH, COLS);
			int iY = normalize_coordinate(G_vecSquares[G_vecChainedSquares[collection][j]].y+SIZE/2, HEIGHT-SIZE, ROWS);
			G_grid[iY][iX] = 0;
		}
	}
	else
	{
		int iX = normalize_coordinate(G_vecSquares[squareID].x+SIZE/2, WIDTH, COLS);
		int iY = normalize_coordinate(G_vecSquares[squareID].y+SIZE/2, HEIGHT-SIZE, ROWS);
		G_grid[iY][iX] = 0;
	}
}
