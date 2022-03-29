#pragma once
#include "DataStructs.h"
typedef unsigned char ubyte;
union mazeInfo
{
	ubyte val;
	struct info
	{
		ubyte mapped : 1;
		
		ubyte victimDirection : 2; //0-north, 1-east, 2-south, 3-west
		ubyte victim : 1;

		//0 means that there is no wall, 1 means that there is a wall in the specified direction
		ubyte west : 1;
		ubyte south : 1;
		ubyte east : 1;
		ubyte north : 1; //Form: North, East, South, West

	} tile;

};
enum directions { North, East, South, West, End };

#define ERRORCODE -100
extern bool* visited;
extern directions curDir;
extern int curR;
extern int curC;
//finds the next node to go to and stores the surroudings in the tile passed in
//it will return the index of the next node to go
int getNext(mazeInfo* tile, int r, int c, int rowLen, int colLen);

//Updates curPos, curDir, and prints the map out
//BFS_PATH has the directions that BFS established, if there are not multiple directions, BFS_PATH should be NULL
void move(int finalR, int finalC, directions* BFS_PATH);


//miscellaneous function(s)
directions relation(int from, int to, int numCols);
int toRow(int pos, int colSize);
int toCol(int pos, int colSize);