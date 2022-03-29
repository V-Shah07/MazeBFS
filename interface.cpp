#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Simulation.h" 
//no need to include Abstraction.h since Simulation.h already includes it
#pragma warning(disable:4996)

int toRow(int pos, int colSize)
{
	return pos / colSize;
}
int toCol(int pos, int colSize)
{
	return pos - toRow(pos, colSize) * colSize;
}

int makeIndex(int pos, directions dir, int rowSize, int colSize)
{
	int r = pos / cols;
	int c = pos - (r * cols);
	if (dir == North)
	{
		if ((r != 0) && (givenMaze[pos].tile.north == 0))
		{
			return (((r - 1) * colSize) + c);
		}
		else
		{
			return ERRORCODE;
		}
	}


	if (dir == East)
	{
		if ((c != (colSize - 1)) && (givenMaze[pos].tile.east == 0))
		{
			return ((r * colSize) + (c + 1));
		}
		else
		{
			return ERRORCODE;
		}
	}

	if (dir == South)
	{
		if ((r != (rowSize - 1)) && (givenMaze[pos].tile.south == 0))
		{
			return (((r + 1) * colSize) + c);
		}
		else
		{
			return ERRORCODE;
		}
	}

	if (dir == West)
	{
		if ((c != 0) && (givenMaze[pos].tile.west == 0))
		{
			return ((r * colSize) + (c - 1));
		}
		else
		{
			return ERRORCODE;
		}
	}


	return ERRORCODE;
}

void printBoard(directions dir, int r, int c)
{
	//Maze Top Wall:
	FILE* fp = fopen("MazeGUI.txt", "r");
	int index = ((2 * r + 1) * (2*cols + 1)) + (2 * c + 1);
	char ch;
	int indexCt = 0;
	while (ch = fgetc(fp) != '\n');
	while ((ch = fgetc(fp)) != EOF)
	{
		if (indexCt == index)
		{
			switch (dir)
			{
			case North:
				ch = '^';
				break;
			case East:
				ch = '>';
				break;
			case South:
				ch = 'v';
				break;
			case West:
				ch = '<';
				break;
			}
		}


		printf("%c", ch);

		if (ch != '\n')
		{
			indexCt++;
		}


	}
}

void nextSimulationStep(directions curDir, int r, int c)
{
	char space = getch();
	if (space == ' ')
	{
		system("CLS");
		printBoard(curDir, r, c);
		printf("\n");
	}

}

directions drawBFS(directions* path, int startR, int startC)
{
	
	directions curDir, prevDir;
	
	int i = 0;
	curDir = path[0];
    for (; curDir != End;)
	{
		switch (curDir)
		{
		case North:
			--startR;
			break;
		case East:
			++startC;
			break;
		case South:
			++startR;
			break;
		case West:
			--startC;
			break;
		}

		nextSimulationStep(curDir, startR, startC);
		++i;
		prevDir = curDir;
		curDir = path[i];

	}
	return prevDir;

}

directions relation(int from, int to, int numCols)
{
	if (to == (from - numCols))
	{
		return North;
	}
	if (to == (from + numCols))
	{
		return South;
	}
	if (to == (from + 1))
	{
		return East;
	}
	if (to == (from - 1))
	{
		return West;
	}
	return End; //to avoid warning
}

int getNext(mazeInfo* tile, int r, int c, int rowLen, int colLen)
{
	int pos = r * cols + c;
	
	//this is the part where the robot looks around its surroundings and finds out where walls and victims are
	*tile = givenMaze[pos];
	int count = 0;
	for (int tryDir = curDir, index; count < 4; ++count, ++tryDir)
	{

		if (((index = makeIndex(pos, (directions)tryDir, rowLen, colLen)) != ERRORCODE) && (visited[index] == false))
		{
			return index;
		}
		if (tryDir == West)
		{
			tryDir = North - 1;
		}

	}
	return ERRORCODE;
}


void move(int finalR, int finalC, directions* BFS_PATH)
{
	int startPos = curR * cols + curC;
	int finalPos = finalR * cols + finalC;
	directions dir = relation(startPos, finalPos, cols);
	
	if (BFS_PATH == NULL)
	{
		nextSimulationStep(dir, finalR, finalC);
	}
	else
	{
		dir = drawBFS(BFS_PATH,curR, curC);
	}
	curDir = dir;
	curR = finalR;
	curC = finalC;

}