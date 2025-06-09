/*
 * chain.cpp
 *
 *  Created on: Dec 25, 2023
 *      Author: bekdouche
 */


#include "chain.h"

vector<sChain> G_vecChains;
vector<vector<int>> G_vecChainedSquares;

int get_chained_squares_collection(int square)
{

	for (int i = 0; i < int(G_vecChainedSquares.size()); i++)
	{
		for (int j = 0; j < int(G_vecChainedSquares[i].size()); j++)
		{
			if (square == G_vecChainedSquares[i][j])
			{
				return i;
			}
		}
	}
	return -1;
}

void update_chain_collection(int deletedSquareID)
{
	for (int i = 0; i < int(G_vecChainedSquares.size()); i++)
	{
		for (int j = 0; j < int(G_vecChainedSquares[i].size()); j++)
		{
			if (G_vecChainedSquares[i][j] > deletedSquareID)
			{
				G_vecChainedSquares[i][j]--;
			}
		}
	}
}
void add_to_collection(int square1, int square2)
{
	int collection1 = get_chained_squares_collection(square1);
	int collection2 = get_chained_squares_collection(square2);
	if (collection1 == -1 and collection2 == -1)
	{
		vector<int> temporaryVector;
		temporaryVector.push_back(square1);
		temporaryVector.push_back(square2);
		G_vecChainedSquares.push_back(temporaryVector);
	}
	else if (collection1 != -1 and collection2 == -1)
	{
		G_vecChainedSquares[collection1].push_back(square2);
	}
	else if (collection1 == -1 and collection2 != -1)
	{
		G_vecChainedSquares[collection2].push_back(square1);
	}
	else if (collection1 != -1 and collection2 != -1 and collection1 != collection2)
	{
		for (int i = 0; i < int(G_vecChainedSquares.size()); i++)
		{
			G_vecChainedSquares[collection1].push_back(G_vecChainedSquares[collection2][i]);
		}
		G_vecChainedSquares.erase(G_vecChainedSquares.begin()+collection2);
	}
}

void chain_squares(int level, int square1, int square2)
{
	if (level >= LOCKLEVEL)
	{
		sChain chain;
		chain.square1 = square1;
		chain.square2 = square2;
		G_vecSquares[chain.square1].locked = true;
		G_vecSquares[chain.square2].locked = true;
		G_vecChains.push_back(chain);
		add_to_collection(square1, square2);
	}
}

void random_chainer(int squareID)
{
	if(double(rand()%100)/100 <= LOCKPROB)
	{
		int iX, iY;
		iY = round((G_vecSquares[squareID].y)*0.01);
		iX = round((G_vecSquares[squareID].x)*0.01);

		int iX2, iY2;

		if(double(rand()%100)/100 <= 1.0/3.0 and G_grid[iY+1][iX] != 0)
		{
			for(int i = 0; i < int(G_vecSquares.size()); i++)
			{
				iY2 = round((G_vecSquares[i].y)*0.01);
				iX2 = round((G_vecSquares[i].x)*0.01);
				if (iX2 == iX and iY2 == iY+1)
				{
					chain_squares(G_level, squareID, i);
				}
			}
		}
		else if(double(rand()%100)/100 <= 1.0/3.0 and G_grid[iY][iX+1] != 0 and iX != COLS-1)
		{
			for(int i = 0; i < int(G_vecSquares.size()); i++)
			{
				iY2 = round((G_vecSquares[i].y)*0.01);
				iX2 = round((G_vecSquares[i].x)*0.01);
				if (iX2 == iX+1 and iY2 == iY)
				{
					chain_squares(G_level, squareID, i);
				}
			}
		}
		else if(double(rand()%100)/100 <= 1.0/3.0 and G_grid[iY][iX-1] != 0 and iX != 0)
		{
			for(int i = 0; i < int(G_vecSquares.size()); i++)
			{
				iY2 = round((G_vecSquares[i].y)*0.01);
				iX2 = round((G_vecSquares[i].x)*0.01);
				if (iX2 == iX-1 and iY2 == iY)
				{
					chain_squares(G_level, squareID, i);
				}
			}
		}
	}
}

void draw_chain(sChain chain)
{
	glColor3f(0.0, 0.0, 0.0);
	glNormal3f(0.0, 0.0f, 1.0f);
	glVertex2f(G_vecSquares[chain.square1].x+SIZE/2-3*ImDiffSIZE, G_vecSquares[chain.square1].y+SIZE/2-3*ImDiffSIZE);
	glVertex2f(G_vecSquares[chain.square2].x+SIZE/2+2*ImDiffSIZE, G_vecSquares[chain.square1].y+SIZE/2-3*ImDiffSIZE);
	glVertex2f(G_vecSquares[chain.square2].x+SIZE/2+2*ImDiffSIZE, G_vecSquares[chain.square2].y+SIZE/2+2*ImDiffSIZE);
	glVertex2f(G_vecSquares[chain.square1].x+SIZE/2-3*ImDiffSIZE, G_vecSquares[chain.square2].y+SIZE/2+2*ImDiffSIZE);
}
