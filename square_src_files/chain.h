/*
 * chain.h
 *
 *  Created on: Dec 25, 2023
 *      Author: bekdouche
 */

#ifndef SQUARE_SRC_FILES_CHAIN_H_
#define SQUARE_SRC_FILES_CHAIN_H_


// Includes
#include "square.h"
#include "..\level_manager_src_files\level_manager.h"

using namespace std;

// Defines
#define LOCKLEVEL 1
#define LOCKPROB 0.3f

// Structures
struct sChain
{
    int square1;
    int square2;
};

// Functions
void chain_squares(int level, int square1, int square2);
void draw_chain(sChain chain);
int get_chained_squares_collection(int square);
void add_to_collection(int square1, int square2);
void update_chain_collection(int deletedSquareID);
void random_chainer(int squareID);
// Externals
extern vector<sChain> G_vecChains;
extern vector<vector<int>> G_vecChainedSquares;

#endif /* SQUARE_SRC_FILES_CHAIN_H_ */
