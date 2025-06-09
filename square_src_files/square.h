/*
 * square.h
 *
 *  Created on: Dec 9, 2023
 *      Author: bekdouche
 */

#ifndef SQUARE_SRC_FILES_SQUARE_H_
#define SQUARE_SRC_FILES_SQUARE_H_

// Includes
#include <vector>
#include <iostream>
#include <tuple>
#include <cmath>

#include "..\loaders_src_files\imageloader.h"
#include "..\loaders_src_files\textureloader.h"
#include "..\game_settings.h"
#include "..\grid_src_files\grid.h"
#include "chain.h"
#include "..\user_interactions_src_files\mouse_handler.h"
#include "adder.h"
#include "collision_detector.h"
#include "..\level_manager_src_files\level_manager.h"
// Defines
#define SIZE 100
#define ImDiffSIZE 10
#define dt 0.05f
using namespace std;

// Structures
struct sSquare
{
	int x,y;
    int value;
    int id;
    bool locked;
    int floors_dropped;
};

// Functions
void load_square_images();
void create_square(int x, int y, int value);
void draw_square(sSquare square);
void draw_squares(float R, float G, float B);
void move_square(int squareID, int x, int y);
bool can_move_chained_square_x(int squareID, int x);
bool can_move_chained_square_y(int squareID, int y);
void move_chained_square(int squareID, int x, int y);
void drop_square(int squareID);
void drop_chained_squares(int squareID);
// Externals
extern vector<sSquare> G_vecSquares;
extern vector<GLuint> G_vecTextures;
extern int G_SelectedSquare;
#endif /* SQUARE_SRC_FILES_SQUARE_H_ */
