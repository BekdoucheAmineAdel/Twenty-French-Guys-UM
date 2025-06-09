/*
 * mouse_handler.h
 *
 *  Created on: Dec 22, 2023
 *      Author: bekdouche
 */

#ifndef USER_INTERACTIONS_SRC_FILES_MOUSE_HANDLER_H_
#define USER_INTERACTIONS_SRC_FILES_MOUSE_HANDLER_H_

// Includes
#include "..\square_src_files\square.h"
#include "..\square_src_files\gravity.h"
// Defines

// Structures

// Functions
int int_normalize_coordinate(int coordinate, int maximumValue, int factor);
void motion_callback(int x, int y);
void select_square(int x, int y);
void mouse_callback(int mouseKey, int state, int x, int y);
void deselect_square();

// Externals

#endif /* USER_INTERACTIONS_SRC_FILES_MOUSE_HANDLER_H_ */
