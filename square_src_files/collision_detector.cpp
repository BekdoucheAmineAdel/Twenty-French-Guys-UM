/*
 * collision_detector.cpp
 *
 *  Created on: Jan 6, 2024
 *      Author: bekdouche
 */

#include "collision_detector.h"

bool can_move_square_x(int squareID, int dx)
{
	int iX, iYmin, iYmax, value;
	iYmin = normalize_coordinate(G_vecSquares[squareID].y+ImDiffSIZE, HEIGHT-SIZE, ROWS);
	iYmax = normalize_coordinate(G_vecSquares[squareID].y+SIZE-ImDiffSIZE, HEIGHT-SIZE, ROWS);
	value = G_vecSquares[squareID].value;
	if(dx >= 0)
	{
		iX = normalize_coordinate(G_vecSquares[squareID].x+dx+SIZE-ImDiffSIZE, WIDTH, COLS);
	}
	else
	{
		iX = normalize_coordinate(G_vecSquares[squareID].x+dx+ImDiffSIZE, WIDTH, COLS);
	}
	if (G_vecSquares[squareID].x+dx+SIZE-ImDiffSIZE > WIDTH or G_vecSquares[squareID].x+dx < 0)
	{
		return false;
	}
	else if (G_grid[iYmin][iX] != value and G_grid[iYmin][iX] != 0)
	{
		return false;
	}
	else if (G_grid[iYmax][iX] != value and G_grid[iYmax][iX] != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool can_move_square_y(int squareID, int dy)
{
	int iY, iXmin, iXmax, value;
	iXmin = normalize_coordinate(G_vecSquares[squareID].x+2*ImDiffSIZE, WIDTH, COLS);
	iXmax = normalize_coordinate(G_vecSquares[squareID].x+SIZE-2*ImDiffSIZE, WIDTH, COLS);
	value = G_vecSquares[squareID].value;
	if(dy >= 0)
	{
		iY = normalize_coordinate(G_vecSquares[squareID].y+dy+SIZE-ImDiffSIZE, HEIGHT-SIZE, ROWS);
	}
	else
	{
		iY = normalize_coordinate(G_vecSquares[squareID].y+dy+ImDiffSIZE, HEIGHT-SIZE, ROWS);
	}
	if (G_vecSquares[squareID].y+dy+SIZE-ImDiffSIZE > HEIGHT-SIZE or G_vecSquares[squareID].y+dy < 0)
	{
		return false;
	}
	if (G_grid[iY][iXmin] != value and G_grid[iY][iXmin] != 0)
	{
		return false;
	}
	else if (G_grid[iY][iXmax] != value and G_grid[iY][iXmax] != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void move_square(int squareID, int x, int y)
{
	int iX, iY;
	iY = round((G_vecSquares[squareID].y)*0.01);
	iX = round((G_vecSquares[squareID].x)*0.01);

	float Vx, Vy, alpha;

	Vx = sqrt(pow((x-SIZE/2-G_vecSquares[squareID].x), 2));
	Vy = sqrt(pow((y-SIZE/2-G_vecSquares[squareID].y), 2));
	alpha = atan2(y-SIZE/2-G_vecSquares[squareID].y, x-SIZE/2-G_vecSquares[squareID].x);

	int dx, dy;

	dx = round(dt*Vx*cos(alpha));
	dy = round(dt*Vy*sin(alpha));

	int numOfSquares = G_vecSquares.size();
	if (G_grid[iY][iX] == G_vecSquares[squareID].value)
	{
		sum_squares();
		if(numOfSquares > int(G_vecSquares.size()))
		{
            audioManager.playEffect("fusion");
		}
	}
	else
	{
		if(can_move_square_x(squareID, dx) == true)
		{
			G_vecSquares[squareID].x = G_vecSquares[squareID].x + dx;
		}
		if(can_move_square_y(squareID, dy) == true)
		{
			G_vecSquares[squareID].y = G_vecSquares[squareID].y + dy;
		}
	}
}
bool can_move_chained_square_x(int collection, int dx)
{
	for(int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
	{
		if(can_move_square_x(G_vecChainedSquares[collection][i], dx) == false)
		{
			return false;
		}
	}
	return true;
}
bool can_move_chained_square_y(int collection, int dy)
{
	for(int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
	{
		if(can_move_square_y(G_vecChainedSquares[collection][i], dy) == false)
		{
			return false;
		}
	}
	return true;
}
void move_chained_square(int squareID, int x, int y)
{
	int iX, iY;

	float Vx, Vy, alpha;
	Vx = sqrt(pow((x-SIZE/2-G_vecSquares[squareID].x), 2));
	Vy = sqrt(pow((y-SIZE/2-G_vecSquares[squareID].y), 2));
	alpha = atan2(y-SIZE/2-G_vecSquares[squareID].y, x-SIZE/2-G_vecSquares[squareID].x);

	int dx, dy;
	dx = round(dt*Vx*cos(alpha));
	dy = round(dt*Vy*sin(alpha));

	int collection;
	collection = get_chained_squares_collection(squareID);

	bool already_summed = false;

	int numOfSquares = G_vecSquares.size();
	for(int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
	{
		iY = round((G_vecSquares[G_vecChainedSquares[collection][i]].y)*0.01);
		iX = round((G_vecSquares[G_vecChainedSquares[collection][i]].x)*0.01);
		if (G_grid[iY][iX] == G_vecSquares[G_vecChainedSquares[collection][i]].value)
		{
			sum_squares();
			if(numOfSquares > int(G_vecSquares.size()))
			{
				audioManager.playEffect("fusion");
			}
			already_summed = true;
		}
	}
	if (already_summed == false)
	{
		if(can_move_chained_square_x(collection, dx) == true)
		{
			for(int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
			{
				G_vecSquares[G_vecChainedSquares[collection][i]].x = G_vecSquares[G_vecChainedSquares[collection][i]].x + dx;
			}
		}
		if(can_move_chained_square_y(collection, dy) == true)
		{
			for(int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
			{
				G_vecSquares[G_vecChainedSquares[collection][i]].y = G_vecSquares[G_vecChainedSquares[collection][i]].y + dy;
			}
		}
	}
}


