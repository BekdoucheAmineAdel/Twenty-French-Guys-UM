/*
 * level_manager.cpp
 *
 *  Created on: Dec 25, 2023
 *      Author: bekdouche
 */

#include "level_manager.h"

int leveltimer;
int G_level;

int Random_value(int maxNum)
{
	for (int i = maxNum-7; i < maxNum; i++)
	{
		if (double(rand()%100)/100 <= double(abs(i))/maxNum)
			return i;
	}
	return 1;
}

void setup_first_level()
{
	for (int j = 0; j < 2*COLS; j++)
	{
		create_square(rand()%(COLS)*SIZE, (ROWS-1)*SIZE, Random_value(STARTLEVEL));
		simulate_gravity();
	}
	sum_squares();
	G_level = 1;
	for(int i = 0; i < int(G_vecSquares.size()); i++)
	{
		if (G_vecSquares[i].value > G_level)
		{
			G_level = G_vecSquares[i].value;
		}
	}
}

void start_game()
{
	G_vecSquares.clear();
	G_vecChains.clear();
	G_vecChainedSquares.clear();
	setup_first_level();
	leveltimer = round(STARTTIMER*(21-G_level)/21)*FPS;
	update_grid();
}

void add_line_of_squares()
{
	for (int i = 0; i < COLS; i++)
	{
		create_square(i*SIZE, 0, Random_value(G_level));
	}
	update_grid();
	for (int i = 1; i < COLS+1; i++)
	{
		if(G_level >= LOCKLEVEL)
		{
			random_chainer(int(G_vecSquares.size()-i));
		}
	}
}

void move_squares_up()
{
	deselect_square();
	for(int i = 0; i < int(G_vecSquares.size()); i++)
	{
		if (G_vecSquares[i].y < (ROWS-1)*SIZE)
		{
			G_vecSquares[i].y = G_vecSquares[i].y + SIZE;
		}
		else
		{
			store_score();
			G_gameState = GAME_OVER;
			break;
		}
	}
	update_grid();
}

bool Cleared_level()
{
	for(int i = 0; i < int(G_vecSquares.size()); i++)
	{
		for(int j = 0; j < int(G_vecSquares.size()); j++)
		{
			if(G_vecSquares[i].value == G_vecSquares[j].value and i != j)
				return false;
		}
	}
	return true;
}

void draw_timer_bar()
{
	glColor3f(0.3f, 0.3f, 0.3f);
	glRectd(15, 815,double(leveltimer)/double(round(STARTTIMER*(21-G_level)/21)*FPS)*670+15, 825);
	glColor3f(0.8f, 0.8f, 0.8f);
	glRectd(10, 810, 690, 830);
}

void level_timer()
{
	if (leveltimer == 0 or Cleared_level())
	{
		move_squares_up();
		add_line_of_squares();
		leveltimer = round(STARTTIMER*(21-G_level)/21)*FPS;
	}
	else
	{
		leveltimer--;
	}
}
