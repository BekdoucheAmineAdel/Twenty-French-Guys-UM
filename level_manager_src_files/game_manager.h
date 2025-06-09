/*
 * game_manager.h
 *
 *  Created on: Jan 10, 2024
 *      Author: bekdouche
 */

#ifndef LEVEL_MANAGER_SRC_FILES_GAME_MANAGER_H_
#define LEVEL_MANAGER_SRC_FILES_GAME_MANAGER_H_

// Includes
#include "../square_src_files/square.h"
#include "score.h"

// Defines


// Structures and Enums
enum eGameState {
		MAIN_MENU,
		GAME,
		GAME_WON,
		GAME_OVER,
};

// Functions
void fill_winSquares();
void drawGame();
void drawMenu();
void drawWin();
void drawLose();
void motion_game_callback(int x, int y);
void motion_menu_callback(int x, int y);
void motion_win_callback(int x, int y);
void motion_lose_callback(int x, int y);
void mouse_game_callback(int mouseKey, int state, int x, int y);
void mouse_menu_callback(int mouseKey, int state, int x, int y);
void mouse_win_callback(int mouseKey, int state, int x, int y);
void mouse_lose_callback(int mouseKey, int state, int x, int y);
// Externals
extern eGameState G_gameState;
extern bool G_win_animation_ended;

#endif /* LEVEL_MANAGER_SRC_FILES_GAME_MANAGER_H_ */
