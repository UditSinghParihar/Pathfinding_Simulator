# Pathfinding-GUI-made-in-SFML
A pathfinding GUI made in SFML/C++ for comparing optimality and speed of Dijkstra and A* algorithms 

Color coding :-
Open cells - White
Blocked cells - Black
Start and End cells - Blue and Red
Explored cells - Yellow
Shortest Path of Dijkstra and A* - Green and Magenta

Three major components:-
i. Main loop to render frames at 60 frames/second
ii. Dijkstra program
iii. Astar program

IMPLEMENTATION :-
i. Map as 2D array of cells
ii. Binary representation of cells as 0 and 1 for blocked and open cells
iii. Each cell has information of its parent and its state of exploration

Heuristics for any node having coordinates (node_x, node_y) is:-
i. Horizontal and vertical cost, D1 = 1
ii. Diagonal cost, D2 = √2
iii. Abscissa difference, dx = |goal_x – node_x|
iv. Ordinate difference, dy = |goal_y – node_y|
v. Diagonal heuristics, h = D1* |dx - dy| + D2* min(dx, dy)

Video Analysis in Detail :- https://www.youtube.com/watch?v=t3rh8RnQ1qE&t=1295s

