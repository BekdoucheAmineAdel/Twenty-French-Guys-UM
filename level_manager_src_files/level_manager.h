/*
 * level_manager.h
 *
 *  Created on: Dec 25, 2023
 *      Author: bekdouche
 */

#ifndef LEVEL_MANAGER_SRC_FILES_LEVEL_MANAGER_H_
#define LEVEL_MANAGER_SRC_FILES_LEVEL_MANAGER_H_

// Includes
#include "../square_src_files/square.h"
#include "score.h"
#include <time.h>
#include "../game_settings.h"
#include "score.h"
#include "game_manager.h"

// Defines
#define STARTTIMER 100 // s
#define STARTLEVEL 20

// Structures


// Functions
void setup_first_level();
void level_timer();
void start_game();
void draw_timer_bar();

// Externals
extern int G_level;
#endif /* LEVEL_MANAGER_SRC_FILES_LEVEL_MANAGER_H_ */
