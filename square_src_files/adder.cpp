/*
 * adder.cpp
 *
 *  Created on: Jan 3, 2024
 *      Author: bekdouche
 */

#include "adder.h"


void update_squares_id(int deletedSquareID)
{
	for (int i = 0; i < int(G_vecSquares.size()); i++)
	{
		if (G_vecSquares[i].id > deletedSquareID)
		{
			G_vecSquares[i].id --;
		}
	}
	for (int i = 0; i < int(G_vecChains.size()); i++)
	{
		if (G_vecChains[i].square1 > deletedSquareID)
		{
			G_vecChains[i].square1--;
		}
		if (G_vecChains[i].square2 > deletedSquareID)
		{
			G_vecChains[i].square2--;
		}
	}
	for (int j = 0; j < int(G_vecChainedSquares.size()); j++)
	{
		for (int i = 0; i < int(G_vecChainedSquares[j].size()); i++)
		{
			if (G_vecChainedSquares[j][i] > deletedSquareID)
			{
				G_vecChainedSquares[j][i]--;
			}
		}
	}
}
void unchain_square(int square)
{
	vector<int> ids2remove;
	ids2remove.push_back(square);
	for (int i = 0; i < int(G_vecChains.size()); i++)
	{
		if (G_vecChains[i].square1 == square or G_vecChains[i].square2 == square )
		{
			if(G_vecChains[i].square1 == square)
			{
				ids2remove.push_back(G_vecChains[i].square2);
			}
			else
			{
				ids2remove.push_back(G_vecChains[i].square1);
			}
			G_vecSquares[G_vecChains[i].square1].locked = false;
			G_vecSquares[G_vecChains[i].square2].locked = false;
			G_vecChains.erase(G_vecChains.begin()+i);
			i --;
		}
	}
	int collection;
	for (int j = 0; j < int(ids2remove.size()); j++)
	{
		collection = get_chained_squares_collection(ids2remove[j]);
		for (int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
		{
			if (G_vecChainedSquares[collection][i] == square)
			{
				G_vecChainedSquares[collection].erase(G_vecChainedSquares[collection].begin()+i);
				break;
			}
		}
		if(G_vecChainedSquares[collection].size() == 0)
		{
			G_vecChainedSquares.erase(G_vecChainedSquares.begin()+collection);
		}
	}
}
void relock_squares()
{
	for (int i = 0; i < int(G_vecChains.size()); i++)
	{
		G_vecSquares[G_vecChains[i].square1].locked = true;
		G_vecSquares[G_vecChains[i].square2].locked = true;
	}
}
void sum_squares()
{
	int square1X, square1Y, square2X, square2Y;
	for (int i = 0; i < int(G_vecSquares.size()); i++)
	{
		square1X = 100*round(G_vecSquares[i].x*0.01);
		square1Y = 100*round(G_vecSquares[i].y*0.01);
		for (int j = 0; j < int(G_vecSquares.size()); j++)
		{
			if (j != i)
			{
				square2X = 100*round(G_vecSquares[j].x*0.01);
				square2Y = 100*round(G_vecSquares[j].y*0.01);
				if(square2X == square1X and square2Y == square1Y)
				{
					deselect_square();
					if (G_vecSquares[i].locked == true)
					{
						unchain_square(i);
						G_vecSquares[i].locked = false;
					}
					if (G_vecSquares[j].locked == true)
					{
						unchain_square(j);
					}
					G_vecSquares[i].value++;
					if(G_vecSquares[i].value > G_level)
					{
						G_level = G_vecSquares[i].value;
						if (G_level > highestScore)
						{
							highestScore = G_level;
						}
						if(G_level == 20)
						{
							G_gameState = GAME_WON;
							G_win_animation_ended = false;
						}
					}
					update_squares_id(j);
					G_vecSquares.erase(G_vecSquares.begin()+j);
					relock_squares();
					i = -1;
					break;
				}
			}
		}
		update_grid();
	}
}
