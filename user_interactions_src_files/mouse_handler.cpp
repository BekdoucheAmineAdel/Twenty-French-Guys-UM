/*
 * mouse_handler.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: bekdouche
 */

#include "mouse_handler.h"



void motion_callback(int x, int y)
{
	switch(G_gameState)
	{
		case MAIN_MENU:
			motion_menu_callback(x, y);
			break;
		case GAME:
			motion_game_callback(x, y);
			break;
		case GAME_WON:
			motion_win_callback(x, y);
			break;
		case GAME_OVER:
			motion_lose_callback(x, y);
			break;
	}
}

void select_square(int x, int y)
{
	for (int i = 0; i < int(G_vecSquares.size()); i++)
	{
		if (x > G_vecSquares[i].x and x < G_vecSquares[i].x + SIZE and
				y > G_vecSquares[i].y and y < G_vecSquares[i].y + SIZE)
		{
			G_SelectedSquare = G_vecSquares[i].id;
			empty_selected_grid(i);
			G_oldx = floor((G_vecSquares[i].x)*0.01);
			break;
		}
	}
}

void deselect_square()
{
	if (G_SelectedSquare != -1)
	{
		if (G_vecSquares[G_SelectedSquare].locked == false)
		{
			drop_square(G_SelectedSquare);
		}
		else
		{
			drop_chained_squares(G_SelectedSquare);
		}
		G_SelectedSquare = -1;
		simulate_gravity();
	}
}


void mouse_callback(int mouseKey, //The mouse key that was pressed
		int state, // indicated weather the key was pressed or released
		int x, int y) //The current mouse coordinates
{
	switch(G_gameState)
	{
		case MAIN_MENU:
			mouse_menu_callback(mouseKey, state, x, y);
			break;
		case GAME:
			mouse_game_callback(mouseKey, state, x, y);
			break;
		case GAME_WON:
			mouse_win_callback(mouseKey, state, x, y);
			break;
		case GAME_OVER:
			mouse_lose_callback(mouseKey, state, x, y);
			break;
	}
}
