/*
 * score.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: bekdouche
 */


#include "score.h"

int highestScore;

void create_score_file()
{
	ofstream myfile;
	myfile.open ("hs.txt", ios::out);
	myfile << 1 << endl;
	myfile.close();
}
void store_score()
{
	ofstream hs;
	hs.open("hs.txt", ios::out | ios::trunc);
	hs << highestScore << endl;
	hs.close();
}
void load_score()
{
	ifstream hs("hs.txt", ios_base::in);
	if(hs.is_open()) // file does exist
	{
	    hs >> highestScore;
		hs.close();
	}
	else // file doesn't exist
	{
		hs.close();
		create_score_file();
		highestScore = 1;
	}
}

void draw_score()
{
	int x = G_level%5;
	if (x == 0) x = 5;
	int y = ceil(G_level/5.0f);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0+(x-1)*0.2f, 0.9-(y-1)*0.1f);
	glVertex2f(640, 840);
	glTexCoord2f(0.2+(x-1)*0.2f, 0.9-(y-1)*0.1f);
	glVertex2f(690, 840);
	glTexCoord2f(0.2+(x-1)*0.2f, 1.0-(y-1)*0.1f);
	glVertex2f(690, 890);
	glTexCoord2f(0.0+(x-1)*0.2f, 1.0-(y-1)*0.1f);
	glVertex2f(640 , 890);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.32f, 0.55f);
	glVertex2f(500.0, 830);
	glTexCoord2f(0.6f, 0.55f);
	glVertex2f(640.0, 830);
	glTexCoord2f(0.6f, 0.6);
	glVertex2f(640.0, 890);
	glTexCoord2f(0.32f, 0.6f);
	glVertex2f(500, 890);
}

void draw_logo()
{
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.55f);
	glVertex2f(10, 830);
	glTexCoord2f(0.32f, 0.55f);
	glVertex2f(210.0, 830);
	glTexCoord2f(0.32f, 0.6);
	glVertex2f(210.0, 900);
	glTexCoord2f(0.0f, 0.6f);
	glVertex2f(10, 900);
}

void draw_high_score()
{
	int x = highestScore%5;
	if (x == 0) x = 5;
	int y = ceil(highestScore/5.0f);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0+(x-1)*0.2f, 0.9-(y-1)*0.1f);
	glVertex2f(450, 100);
	glTexCoord2f(0.2+(x-1)*0.2f, 0.9-(y-1)*0.1f);
	glVertex2f(550, 100);
	glTexCoord2f(0.2+(x-1)*0.2f, 1.0-(y-1)*0.1f);
	glVertex2f(550, 200);
	glTexCoord2f(0.0+(x-1)*0.2f, 1.0-(y-1)*0.1f);
	glVertex2f(450 , 200);

	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex2f(150.0, 125.0);
	glTexCoord2f(0.6f, 0.5f);
	glVertex2f(450, 125.0);
	glTexCoord2f(0.6f, 0.55);
	glVertex2f(450, 175.0);
	glTexCoord2f(0.0f, 0.55f);
	glVertex2f(150.0, 175);
}

void draw_score_board(float R, float G, float B)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, G_vecTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
	draw_score();
	draw_logo();
	glEnd();
	glDisable(GL_TEXTURE_2D);
	draw_timer_bar();
	glColor3f(0.848f, 0.2f, 0.2f);
	glRectd(0, 800, 700, 810);
}
