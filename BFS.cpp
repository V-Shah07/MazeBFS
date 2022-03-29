#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BFS.h"
//do not need to include Abstraction.h since BFS.h already includes it


mazeInfo* map;
int numR;
int numC;
int startR;
int startC;


directions curDir;
bool* visited;
int curR;
int curC;

int formIndex(int rows, int cols)
{
	return rows * numC + cols;
}
directions* ans(int* parent, int end)
{
	int index = end;
	int* ans = (int*)calloc(numC * (size_t)numR, sizeof(int));
	int i;

	for (i = 0; parent[index] != index; ++i)
	{
		ans[i] = index;
		index = parent[index];

	}
	ans[i] = index;
	directions* finalDirections = (directions*)calloc((size_t)i + 1, sizeof(directions));
	for (int ct = 0, j = i; j > 0; --j, ++ct)
	{
		finalDirections[ct] = relation(ans[j], ans[j - 1], numC);
	}
	finalDirections[i] = End;
	return finalDirections;
}
int getIndex(int pos, directions dir, int rowSize, int colSize)
{
	int r = pos / colSize;
	int c = pos - (r * colSize);
	if (dir == North)
	{
		if ((r != 0) && (map[pos].tile.north == 0))
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
		if ((c != (colSize - 1)) && (map[pos].tile.east == 0))
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
		if ((r != (rowSize - 1)) && (map[pos].tile.south == 0))
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
		if ((c != 0) && (map[pos].tile.west == 0))
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
int BFS(int curPos, directions curD, directions** ansPath, bool traceBack) //will return final position 
{
	int* parent = (int*)calloc(numR * numC, sizeof(int));
	memset(parent, -1, (size_t)numR * numC * sizeof(int));
	queue worker;
	worker.enqueue(curPos);
	parent[curPos] = curPos;
	int childIndexes[4] = { 0 };
	while (true)
	{
		if ((!visited[worker.getHead()->value]) && (!traceBack))
		{
			break;
		}
		else if ((worker.getHead()->value == ((startR * numC) + startC)) && (traceBack))
		{
			break;
		}
		if (worker.getHead()->value != parent[worker.getHead()->value])
		{
			curD = relation(parent[worker.getHead()->value], worker.getHead()->value, numC);
		}

 		childIndexes[0] = getIndex(curPos, North, numR, numC);
		childIndexes[1] = getIndex(curPos, East, numR, numC);
		childIndexes[2] = getIndex(curPos, South, numR, numC);
		childIndexes[3] = getIndex(curPos, West, numR, numC);
		for (int d = curD, ct = 0; ct < 4; ++ct, ++d)
		{
			if ((childIndexes[d] >= 0) && (parent[childIndexes[d]] == -1))
			{
				worker.enqueue(childIndexes[d]);
				parent[childIndexes[d]] = worker.getHead()->value;
			}
			if (d == (End - 1))
			{
				d = North - 1;
			}
		}

		worker.dequeue();
		if (worker.getHead() != NULL)
		{
			curPos = worker.getHead()->value;
		}
		else
		{
			return ERRORCODE;
		}

	}


	*ansPath = ans(parent, worker.getHead()->value);
	return worker.getHead()->value;
}


void exploring(int upperLimitR, int upperLimitC)
{

	numR = upperLimitR, numC = upperLimitC;
	curDir = North;
	map = (mazeInfo*)calloc((size_t)numR * numC, sizeof(mazeInfo));
	visited = (bool*)calloc((size_t)numR * numC, sizeof(bool));
	int* parent = (int*)calloc((size_t)numR* numC, sizeof(int));
	directions* ansPath = (directions*)calloc((size_t)numR * numC, sizeof(directions));
	int newPos;
	int curPos;
 
	curR = -1, curC = 0; //starts at "row" "-1", basically one above the start of the maze
	move(0, 0, NULL); //this is just to signal it moves into the maze

	startR = 0, startC = 0;
	curR = startR;
	curC = startC;
    while (true)
	{
		curPos = formIndex(curR, curC);
		//sets the cur position as visited
		visited[curPos] = true;
		
		newPos = getNext(&map[curPos], toRow(curPos, numC), toCol(curPos, numC), numR, numC);
		map[curPos].tile.mapped = true;
		if (newPos == ERRORCODE)
		{
 			memset(parent, -1, (size_t)numR * numC * sizeof(int));
			queue worker;
			worker.enqueue(curPos);
			parent[curPos] = curPos;
			printf("Calling BFS!\n");
  			newPos = BFS(curPos, curDir, &ansPath, false);
 			if (newPos == ERRORCODE)
			{
				break;
			}
 			move(toRow(newPos, numC), toCol(newPos, numC), ansPath);
			printf("At new node now!\n");
		}
		else
		{
			move(toRow(newPos, numC), toCol(newPos, numC), NULL);
		}

		
		
		

	}
	printf("Visited all nodes!\n");
	printf("Going back to beginning");
 	newPos = BFS(curPos, curDir, &ansPath, true);
	move(startR, startC, ansPath);
}