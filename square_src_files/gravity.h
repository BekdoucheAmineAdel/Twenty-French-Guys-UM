/*
 * gravity.h
 *
 *  Created on: Dec 31, 2023
 *      Author: bekdouche
 */

#ifndef SQUARE_SRC_FILES_GRAVITY_H_
#define SQUARE_SRC_FILES_GRAVITY_H_

// Includes

#include "square.h"

// Defines
#define gravity_factor 1
// Structures

// Functions
void simulate_gravity();
bool check_square_moved();
// Externals
extern int G_oldx;

#endif /* SQUARE_SRC_FILES_GRAVITY_H_ */
