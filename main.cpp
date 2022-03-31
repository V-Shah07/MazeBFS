#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include "Simulation.h"
#define FILEPATH "MazeGUI.txt"
#include "BFS.h"

mazeInfo* givenMaze;
int rows;
int cols;
void Parse()
{
	FILE* fp = fopen(FILEPATH, "r");
	if (fp == NULL)
	{
		printf("could not find file!");
		exit(-1);
	}
	fscanf(fp, "%d %d\n", &rows, &cols);
	char ch;
	int num;

	char** model = (char**)calloc(2 * rows + 1, sizeof(char*));
	//read in the picture from the text file
	for (int i = 0; i < (2 * rows + 1); ++i)
	{
		model[i] = (char*)calloc(2 * cols + 1, sizeof(char));
		for (int j = 0; j < (2 * cols + 1); ++j)
		{
			model[i][j] = fgetc(fp);
		}
		fgetc(fp);//new line
	}
	givenMaze = (mazeInfo*)calloc(rows * cols, sizeof(mazeInfo));
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			givenMaze[i * cols + j].tile.north = (model[2 * i][2 * j + 1] == '-') ? 1 : 0;
			givenMaze[i * cols + j].tile.south = (model[2 * i + 2][2 * j + 1] == '-') ? 1 : 0;
			givenMaze[i * cols + j].tile.east = (model[2 * i + 1][2 * j + 2] == '|') ? 1 : 0;
			givenMaze[i * cols + j].tile.west = (model[2 * i + 1][2 * j] == '|') ? 1 : 0;

		}
	}
}

int main()
{
	Parse();
	
	exploring(rows+1, cols+1);
	printf("Robot Back to the start!");
}