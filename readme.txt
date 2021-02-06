

------------------------------------------------------------------------------------------------------------------------------------------
##IMPORTANT##

******** PLEASE DIRECT TO RELEASE FOLDER AND USE pacman application extension file to start the game directly from the window *************

GAME RULES AND ALGORITHM

INSTRUCTIONS :

Please press 'T' to start the game

Use WSAD of arrows to control the game

The score will be determined on Time you took to collect all the coins in the game and exits once you collected all of them by storing the points.

------------------------------------------------------------------------------------------------------------------------------------------------------------

//**** ALGORITHM - DIJKSTRA'S ALGORITHM ***/

For this game we are using SFML library to help us out with graphics and audio. We have audio files for game opening, collecting a coin, eating a fruit, and for dying.

We have 2 textures: 1 for the maze and 1 for PacMan and ghosts. The Texture for PacMan and ghosts is treated as a sprite sheet. It contains all individual frames of moving animations and we use IntRect to pick which frame to display at each moment in time.]

Ghosts navigate the maze in different ways. At first, they all scatter to one of the four corners. After they've scattered, they each behave in a unique way to make it easier for them to catch the player:

1) Blinky (the red ghost) chases the player directly
2) Pinky (the pink ghost) always aims for the point on grid that is 4 tiles in front of the player
3) Inky (the cyan ghost) tries to ambush the player by always choosing such a destination that the player ends up between Blinky and Inky
4) Clyde (the orange ghost) patrols between the two edges of the map, unless the player gets too close too him, in which case he chases the player directly until the player is too far away, after which Clyde goes back to patrolling

Ghosts are unable to turn until they meet an intersection point, and they only think when there is a new direction to turn to. When a ghost enters an intersection point on the map (a "crossroad"), it asks the Maze which way to turn to get on the shortest path towards its destination. Cost of going from any tile A to tile B is precalculated in "Maze.cpp" file, inside Maze's constructor using Dijkstra Algorithm. Because Dijkstra Algorithm is one of the most common and efficient pathfinding algorithms, and we use it to determine the cost of getting from each point A to point B, and we store these resulting costs inside "int costs[][]". Knowing the costs is enough to know which way we need to turn. For instance, if we want to get to some point A from point B, and we know that costs[A][B] = x, then it's necessary that at least one of the neighbors of B (let's call it point C) satisfies the condition "costs[A][C] = x - 1", since going through neighbors is how we calculated the cost from A to B in the first place. Relying on this knowledge, ghosts ask the maze whichever side is cheapest and they take that route towards their destination point.


/** ALL THE TEST CASES ARE PLACED INSIDE testing.cpp file**/



THANKS!