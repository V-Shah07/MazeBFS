#pragma once
#include "Abstraction.h"

extern mazeInfo* map;
extern int numR;
extern int numC;

//runs the entire BFS Algorithm, it refrences move() and getnext() functions from Simulation
int BFS(int r, int c, directions curDir, int* parent, queue* worker, directions** ansPath);
void exploring(int upperGuessR, int upperGuessC);

