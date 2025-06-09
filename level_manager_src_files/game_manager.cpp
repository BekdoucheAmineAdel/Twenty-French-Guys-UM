/*
 * game_manager.cpp
 *
 *  Created on: Jan 10, 2024
 *      Author: bekdouche
 */

#include "game_manager.h"

eGameState G_gameState;
int wincounter = FPS;
vector<sSquare> winSquares;
bool G_win_animation_ended = false;

void fill_winSquares()
{

	for(int i = 0; i < ROWS+1; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			sSquare temp;
			temp.value = 20;
			temp.x = j*SIZE;
			temp.y = (-1-i)*SIZE;
			temp.locked = false;
			winSquares.push_back(temp);
		}
	}

}
void drawGame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.87, 0.87, 0.87, 1.0);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the camer
	glOrtho(0.0, WIDTH,  0.0,  HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	draw_squares(1.0, 1.0, 1.0);
	draw_score_board(1.0, 1.0, 1.0);
}
void drawMenu()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.87, 0.87, 0.87, 1.0);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the camer
	glOrtho(0.0, WIDTH,  0.0,  HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, G_vecTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.1f);
	glVertex2f(50, 700);
	glTexCoord2f(0.8f, 0.1f);
	glVertex2f(450, 700);
	glTexCoord2f(0.8, 0.2);
	glVertex2f(450, 800);
	glTexCoord2f(0.0f, 0.2f);
	glVertex2f(50, 800);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.1f);
	glVertex2f(450, 700);
	glTexCoord2f(0.2f, 0.1f);
	glVertex2f(550, 700);
	glTexCoord2f(0.2, 0.2);
	glVertex2f(550, 800);
	glTexCoord2f(0.0f, 0.2f);
	glVertex2f(450, 800);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(550, 700);
	glTexCoord2f(0.2f, 0.0f);
	glVertex2f(650, 700);
	glTexCoord2f(0.2, 0.1);
	glVertex2f(650, 800);
	glTexCoord2f(0.0f, 0.1f);
	glVertex2f(550, 800);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.8f, 0.7f);
	glVertex2f(350, 650);
	glTexCoord2f(1.0, 0.7);
	glVertex2f(450, 550);
	glTexCoord2f(1.0f, 0.601);
	glVertex2f(350, 450);
	glTexCoord2f(0.8f, 0.601f);
	glVertex2f(250, 550);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.4f);
	glVertex2f(150, 300);
	glTexCoord2f(0.8f, 0.4f);
	glVertex2f(550, 300);
	glTexCoord2f(0.8, 0.5);
	glVertex2f(550, 400);
	glTexCoord2f(0.0f, 0.5f);
	glVertex2f(150, 400);

	draw_high_score();

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void drawWin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.87, 0.87, 0.87, 1.0);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the camer
	glOrtho(0.0, WIDTH,  0.0,  HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	if(G_win_animation_ended == false)
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, G_vecTextures[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		for (int i = 0; i < int(winSquares.size()); i++)
		{
			glNormal3f(0.0, 0.0f, 1.0f);
			glTexCoord2f(0.8f, 0.5f);
			glVertex2f(winSquares[i].x, winSquares[i].y);
			glTexCoord2f(1.0f, 0.5f);
			glVertex2f(winSquares[i].x + SIZE-ImDiffSIZE, winSquares[i].y);
			glTexCoord2f(1.0, 0.6f);
			glVertex2f(winSquares[i].x + SIZE-ImDiffSIZE, winSquares[i].y + SIZE-ImDiffSIZE);
			glTexCoord2f(0.8f, 0.6f);
			glVertex2f(winSquares[i].x, winSquares[i].y + SIZE-ImDiffSIZE);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		draw_squares(1.0, 1.0, 1.0);
		if (wincounter == 0)
		{
			for (int i = 0; i < int(winSquares.size()); i++)
			{
				winSquares[i].y = winSquares[i].y + SIZE;
				if(winSquares[i].y + SIZE > HEIGHT)
				{
					G_win_animation_ended = true;
					break;
				}
			}
			wincounter = FPS;
		}
		wincounter--;
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, G_vecTextures[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.3f);
		glVertex2f(150, 500);
		glTexCoord2f(0.8f, 0.3f);
		glVertex2f(550, 500);
		glTexCoord2f(0.8, 0.4);
		glVertex2f(550, 600);
		glTexCoord2f(0.0f, 0.4f);
		glVertex2f(150, 600);

		glNormal3f(0.0, 0.0f, 1.0f);
		glTexCoord2f(0.2f, 0.0f);
		glVertex2f(200, 300);
		glTexCoord2f(0.8f, 0.0f);
		glVertex2f(500, 300);
		glTexCoord2f(0.8, 0.1);
		glVertex2f(500, 400);
		glTexCoord2f(0.2f, 0.1f);
		glVertex2f(200, 400);

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}

void drawLose()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.87, 0.87, 0.87, 1.0);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the camer
	glOrtho(0.0, WIDTH,  0.0,  HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, G_vecTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.3f);
	glVertex2f(150, 500);
	glTexCoord2f(0.8f, 0.3f);
	glVertex2f(550, 500);
	glTexCoord2f(0.8, 0.4);
	glVertex2f(550, 600);
	glTexCoord2f(0.0f, 0.4f);
	glVertex2f(150, 600);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.2f);
	glVertex2f(150, 300);
	glTexCoord2f(0.8f, 0.2f);
	glVertex2f(550, 300);
	glTexCoord2f(0.8, 0.3);
	glVertex2f(550, 400);
	glTexCoord2f(0.0f, 0.3f);
	glVertex2f(150, 400);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void motion_game_callback(int x, int y)
{
	if (G_SelectedSquare != -1)
	{
		if (G_vecSquares[G_SelectedSquare].locked == false)
		{
			for (int i = 0; i < int(1/dt); i++)
			{
				if (G_SelectedSquare != -1)
				{
					move_square(G_SelectedSquare, x, 900-y);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < int(1/dt); i++)
			{
				if (G_SelectedSquare != -1)
				{
					move_chained_square(G_SelectedSquare, x, 900-y);
				}
				else
				{
					break;
				}
			}
		}
		if (G_SelectedSquare != -1)
		{
			if (check_square_moved() == true)
			{
				update_grid();
				simulate_gravity();
			}
		}
	}
}

void motion_menu_callback(int x, int y)
{
}
void motion_win_callback(int x, int y)
{
}
void motion_lose_callback(int x, int y)
{
}



void mouse_game_callback(int mouseKey, int state, int x, int y)
{
	switch (mouseKey)
	{
		case GLUT_LEFT_BUTTON: // Left Mouse key
			if (state == GLUT_UP) // released
			{
				if(G_SelectedSquare != -1)
				{
					deselect_square();
				}
			}
			if (state == GLUT_DOWN) // pressed
			{
				select_square(x, 900-y);
			}
			break;
	}
}

void mouse_menu_callback(int mouseKey, int state, int x, int y)
{
	switch (mouseKey)
	{
		case GLUT_LEFT_BUTTON: // Left Mouse key
			if (state == GLUT_UP) // released
			{
			}
			if (state == GLUT_DOWN) // pressed
			{
				if((x<550 and x>150) and (900-y<400 and 900-y>300))
				{
					start_game();
					G_gameState = GAME;
				}
			}
			break;
	}
}
void mouse_win_callback(int mouseKey, int state, int x, int y)
{
}
void mouse_lose_callback(int mouseKey, int state, int x, int y)
{
}
