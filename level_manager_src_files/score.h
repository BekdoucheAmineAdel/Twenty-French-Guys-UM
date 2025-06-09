/*
 * score.h
 *
 *  Created on: Jan 8, 2024
 *      Author: bekdouche
 */

#ifndef LEVEL_MANAGER_SRC_FILES_SCORE_H_
#define LEVEL_MANAGER_SRC_FILES_SCORE_H_


// Includes
#include <iostream>
#include <fstream>
#include "../game_settings.h"
#include "level_manager.h"

using namespace std;

// Defines


// Structures

// Functions
void draw_score_board(float R, float G, float B);
void draw_high_score();
void load_score();
void store_score();

// Externals
extern int highestScore;

#endif /* LEVEL_MANAGER_SRC_FILES_SCORE_H_ */
