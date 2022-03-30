# MazeBFS

## How to run:

1. Clone this repository 
2. Enter the "MazeBFS" folder using ```cd MazeBFS```
3. Compile using this command: ```g++ -o MazeSimulation BFS.cpp interface.cpp main.cpp```
4. In terminal, type: ```./MazeSimulation.exe```
5. click space to simulate every step the robot takes in the virtual map!

## How it works

This program simulates a robot traversing an unknown maze. Since this is all virtual, the map is given to the robot. However, the robot is not allowed to look at the maze from that file, and is only allowed to use the file to see the 4 walls around its **current** position. This is because in a real-world rescue scenario, a robot would not know a fully developed enviroment that it is put into. 
The robot represented by a simple text-based arrow in this case and keeps moving in the direction that it is facing until it reaches a wall. When it reaches a wall, it simply turns around until it finds a path that it can go through. The pat that it goes through must traversable(anything that isn't a wall), and it must be an unvisited grid. Therefore, at walls it will turn around and go to a space that it can move to, **and** to a space that has not been visited. Now, the algorithmic part of the program is when all spaces around the robot are visited or walls. All throughout this simulation, since the robot does not know how the map looks, it makes its own "_virtual map_" that it develops in an array every step it takes in the maze. Once it is stuck, it uses that virtual map and runs the Breadth First Search(BFS) Algorithm to find the closest unviisted spot. Then the robot will go towards that spot. Once ever single grid has been visited(to ensure no fake victims were left behind), it will use BFS while reffering to the virtual map to go back to the starting of the maze.
Every time BFS is called, my program uses a print statement to signal that.
Furhtermore, everytime it finds an unvisited node using BFS, it displays a statement to signal that it has reached the unvisited node.
