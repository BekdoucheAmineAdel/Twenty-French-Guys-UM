/*
 * grid.h
 *
 *  Created on: Dec 22, 2023
 *      Author: bekdouche
 */

#ifndef GRID_SRC_FILES_GRID_H_
#define GRID_SRC_FILES_GRID_H_

// Includes
#include <cmath>
#include "../square_src_files/square.h"
#include "../game_settings.h"

// Defines
#define ROWS 8
#define COLS 7

// Structures

// Functions
void update_grid();
int normalize_coordinate(int coordinate, int maximumValue, int factor);
void empty_selected_grid(int squareID);

// Externals
extern int G_grid[ROWS][COLS];

#endif /* GRID_SRC_FILES_GRID_H_ */
