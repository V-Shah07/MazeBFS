# MazeBFS

## How to run:

1. Clone this repository 
2. Go to the directory that you want this program in and type "git clone " followed by the "HTTPS" link you can find from the "Code" button
3. Enter the "MazeBFS" folder using ```cd MazeBFS```
4. Compile using this command: ```g++ -o MazeSimulation BFS.cpp interface.cpp main.cpp```
5. In terminal, type: ```./MazeSimulation.exe```
6. click space to simulate every step the robot takes in the virtual map!
### Alternatively:
1. Download the files of this repository by zipping it, and then open that folder through file explorer
2. If you are on a linux based shell: ```g++ -o MazeSimulation BFS.cpp interface.cpp main.cpp``` should compile and ```./MazeSimulation.exe``` should run it
3. If you are on windows: ```gcc BFS.cpp interface.cpp main.cpp -o MazeSimulation.exe``` should compile and ```MazeSimulation.exe``` should run it

Finally, click space to move the "robot"!
## How it works

* This program simulates a robot traversing an unknown maze 
* The robot is not allowed to look at the maze from the file that provides it
  - It is only allowed to use the file to see the 4 walls around its **current** position. 
  - This is because in a real-world rescue scenario, a robot would not know a fully developed enviroment that it is put into. 
* Robot represented by a simple text-based arrow 
* Procedure:
  - Click space to simulate every step it takes
  - Keeps moving in the direction that it is facing until it reaches a wall
  - When it reaches a wall, it simply turns around until it finds a path that it can go through
  - The path that it goes through must:
    - be traversable(anything that isn't a wall)
    - be an unvisited point 
  - Procedure when all 4 surrounding grids are visited/walls: 
    - All throughout this simulation, since the robot does not know how the map looks, it makes its own _virtual map_ that it develops in an array every step it     takes in the maze
    - Runs BFS using the _virtual_ map it made and goes to that point since it is the closest unvisited point
   - Once ever single grid has been visited(to ensure no fake victims were left behind), using BFS and the virtual map that is now completed and identical to the real one, the robot will go back to the start
