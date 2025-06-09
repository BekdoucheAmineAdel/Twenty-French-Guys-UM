/*
 * square.cpp
 *
 *  Created on: Dec 9, 2023
 *      Author: bekdouche
 */
// Includes
#include "square.h"

// Variables and Constants
vector<sSquare> G_vecSquares;
vector<GLuint> G_vecTextures;

int G_SelectedSquare = -1;

void load_square_images()
{
	Image* image;
	image = loadBMP("squares.bmp");
	G_vecTextures.push_back(loadTexture(image));
}
void create_square(int x, int y, int value)
{
	// Create a square object
	sSquare s;
	// Set its values
	s.x = x; s.y = y;
	s.value = value;
	s.id = G_vecSquares.size();
	s.floors_dropped = 0;
	s.locked = false;
	// Append the object to the list of squares
	G_vecSquares.push_back(s);
}

void draw_square(sSquare square)
{
	int x = square.value%5;
	if (x == 0) x = 5;
	int y = ceil(square.value/5.0f);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0+(x-1)*0.2f, 0.9-(y-1)*0.1f);
	glVertex2f(square.x, square.y);
	glTexCoord2f(0.2+(x-1)*0.2f, 0.9-(y-1)*0.1f);
	glVertex2f(square.x + SIZE-ImDiffSIZE, square.y);
	glTexCoord2f(0.2+(x-1)*0.2f, 1.0-(y-1)*0.1f);
	glVertex2f(square.x + SIZE-ImDiffSIZE, square.y + SIZE-ImDiffSIZE);
	glTexCoord2f(0.0+(x-1)*0.2f, 1.0-(y-1)*0.1f);
	glVertex2f(square.x, square.y + SIZE-ImDiffSIZE);
}

void drop_square(int squareID)
{
	int x  = 100*round(G_vecSquares[squareID].x*0.01);
	int y = 100*round(G_vecSquares[squareID].y*0.01);
	G_vecSquares[squareID].x = x;
	G_vecSquares[squareID].y = y;
}

void drop_chained_squares(int squareID)
{
	int collection = get_chained_squares_collection(squareID);
	for (int i = 0; i < int(G_vecChainedSquares[collection].size()); i++)
	{
		drop_square(G_vecChainedSquares[collection][i]);
	}
}

void draw_squares(float R, float G, float B)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, G_vecTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
	if(G_SelectedSquare == -1)
	{
		for(int i = 0; i < int(G_vecSquares.size()); i++)
			draw_square(G_vecSquares[i]);
	}
	else
	{
		draw_square(G_vecSquares[G_SelectedSquare]);
		for(int i = 0; i < int(G_vecSquares.size()); i++)
			if (i != G_SelectedSquare)
				draw_square(G_vecSquares[i]);
	}
	for(int i = 0; i < int(G_vecChains.size()); i++)
		draw_chain(G_vecChains[i]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
