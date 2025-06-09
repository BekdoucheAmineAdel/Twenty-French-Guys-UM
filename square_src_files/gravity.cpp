/*
 * gravity.cpp
 *
 *  Created on: Dec 31, 2023
 *      Author: bekdouche
 */

#include "gravity.h"

int G_oldx;

void update_floors_dropped()
{
	for(int i = 0; i < int(G_vecSquares.size()); i++)
	{
		G_vecSquares[i].floors_dropped = 0;
	}
}

bool check_square_moved()
{
	int iX = floor((G_vecSquares[G_SelectedSquare].x)*0.01);
	if(iX != G_oldx)
	{
		G_oldx = floor((G_vecSquares[G_SelectedSquare].x)*0.01);
		return true;
	}
	else
	{
		return false;
	}
}

void simulate_gravity()
{
	int gravity_forcer = 1;
	int collection;
	update_grid();
	update_floors_dropped();
	while(gravity_forcer > 0)
	{
		for(int i = 0; i < int(G_vecSquares.size()); i++)
		{
			if (G_vecSquares[i].id != G_SelectedSquare)
			{
				if (G_vecSquares[i].locked == false)
				{
					int iX, iY;

					iY = round((G_vecSquares[i].y-SIZE)*0.01);
					iX = round((G_vecSquares[i].x)*0.01);
					if (iY >= 0)
					{
						if (G_grid[iY][iX] != G_vecSquares[i].value)
						{
							if (can_move_square_y(i, -SIZE/gravity_factor) == true)
							{
								G_vecSquares[i].y = G_vecSquares[i].y - SIZE/gravity_factor;
								gravity_forcer = 2;
							}
							else
							{
								G_vecSquares[i].floors_dropped = 0;
							}
						}
					}
					else
					{
						G_vecSquares[i].floors_dropped = 0;
					}
				}
				else
				{
					collection = get_chained_squares_collection(i);
					if (G_SelectedSquare != -1)
					{
						if (G_vecSquares[G_SelectedSquare].locked == true)
						{
							if (collection != get_chained_squares_collection(G_SelectedSquare))
							{
								empty_selected_grid(G_vecChainedSquares[collection][0]);
								for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
								{
									G_vecSquares[G_vecChainedSquares[collection][j]].value = -G_vecSquares[G_vecChainedSquares[collection][j]].value;
								}
								if (can_move_chained_square_y(collection, -SIZE/gravity_factor) == true)
								{

									for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
									{
										G_vecSquares[G_vecChainedSquares[collection][j]].y = G_vecSquares[G_vecChainedSquares[collection][j]].y - SIZE/gravity_factor;
									}
									gravity_forcer = 2;
								}
								for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
								{
									G_vecSquares[G_vecChainedSquares[collection][j]].value = -G_vecSquares[G_vecChainedSquares[collection][j]].value;
								}
								update_grid();
							}
						}
						else
						{
							empty_selected_grid(G_vecChainedSquares[collection][0]);
							for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
							{
								G_vecSquares[G_vecChainedSquares[collection][j]].value = -G_vecSquares[G_vecChainedSquares[collection][j]].value;
							}
							if (can_move_chained_square_y(collection, -SIZE/gravity_factor) == true)
							{

								for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
								{
									G_vecSquares[G_vecChainedSquares[collection][j]].y = G_vecSquares[G_vecChainedSquares[collection][j]].y - SIZE/gravity_factor;
								}
								gravity_forcer = 2;
							}
							for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
							{
								G_vecSquares[G_vecChainedSquares[collection][j]].value = -G_vecSquares[G_vecChainedSquares[collection][j]].value;
							}
							update_grid();
						}
					}
					else
					{
						empty_selected_grid(G_vecChainedSquares[collection][0]);
						for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
						{
							G_vecSquares[G_vecChainedSquares[collection][j]].value = -G_vecSquares[G_vecChainedSquares[collection][j]].value;
						}
						if (can_move_chained_square_y(collection, -SIZE/gravity_factor) == true)
						{

							for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
							{
								G_vecSquares[G_vecChainedSquares[collection][j]].y = G_vecSquares[G_vecChainedSquares[collection][j]].y - SIZE/gravity_factor;
							}
							gravity_forcer = 2;
						}
						for(int j = 0; j < int(G_vecChainedSquares[collection].size()); j++)
						{
							G_vecSquares[G_vecChainedSquares[collection][j]].value = -G_vecSquares[G_vecChainedSquares[collection][j]].value;
						}
						update_grid();
					}
				}
			}
		}
		update_grid();
		gravity_forcer--;
	}
	update_floors_dropped();
	if(G_SelectedSquare != -1)
	{
		empty_selected_grid(G_SelectedSquare);
	}
}
