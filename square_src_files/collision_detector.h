/*
 * collision_detector.h
 *
 *  Created on: Jan 6, 2024
 *      Author: bekdouche
 */

#ifndef SQUARE_SRC_FILES_COLLISION_DETECTOR_H_
#define SQUARE_SRC_FILES_COLLISION_DETECTOR_H_

// Includes
#include "square.h"
// Defines

// Structures

// Functions
bool can_move_square_x(int squareID, int dx);
bool can_move_square_y(int squareID, int dy);
void move_square(int squareID, int x, int y);
bool can_move_chained_square_x(int collection, int dx);
bool can_move_chained_square_y(int collection, int dy);
void move_chained_square(int squareID, int x, int y);

// Externals

#endif /* SQUARE_SRC_FILES_COLLISION_DETECTOR_H_ */
