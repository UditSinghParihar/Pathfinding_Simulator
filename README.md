## Pathfinding Simulator implementing Dijkstra and A* algorithms ##

1. A pathfinding simulator using [SFML](https://www.sfml-dev.org/index.php)(Simple and Fast Multimedia Library) for comparing optimality and speed of Dijkstra and A* algorithms. 

## Video Analysis ##

![alt text](astar_vs_dijkstra.jpg)  

1. Video Analysis in Detail :- https://www.youtube.com/watch?v=t3rh8RnQ1qE&t=1295s

## Implementation ##


1. **Color coding** :
	1. *Open cells* - White
	2. *Blocked cells* - Black
	3. *Start and End cells* - Blue and Red
	4. *Explored cells* - Yellow
	5. *Shortest Path of Dijkstra and A-star* - Green and Magenta

2. **Major components** :
	1. Main loop to render frames at 60 frames/second
	2. Dijkstra program
	3. Astar program

3. **Implementation** :
	1. Map as 2D array of cells
	2. Binary representation of cells as 0 and 1 for blocked and open cells
	3. Each cell has information of its parent and its state of exploration

4. **Heuristics for a node having coordinates `(node_x, node_y)` is** :
	1. *Horizontal and vertical cost*: `D1 = 1`
	2. *Diagonal cost*: `D2 = √2`
	3. *Abscissa difference*: `dx = |goal_x – node_x|`
	4. *Ordinate difference*: `dy = |goal_y – node_y|`
	5. *Diagonal heuristics*: `h = D1* |dx - dy| + D2* min(dx, dy)`

## Build ##

1. See how to compile sfml for your operating system [here](https://www.sfml-dev.org/tutorials/2.5/#getting-started) 

2. If you are using Ubuntu or other Linux distros, then for a quick compilation:
	1. **Install sfml**: `sudo apt-get install libsfml-dev`
	2. **Complile simulator.cpp** :
		1. `g++ simulator.cpp -std=c++11 -lsfml-window -lsfml-system -lsfml-graphics`
	3. Run the exectuable: `./a.out`



## TODO ##

1. Place the text in button menu.
2. Add smooth selection of blocking cells(obstacle cells), by clicking left mouse and hovering over the cells.
3. Add CMake build system for easy compilation.
4. Refactoring code into headers and OOPS style.