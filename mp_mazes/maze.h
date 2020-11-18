/* Your code here! */

#pragma once 

#include <vector>
#include <map>
#include "cs225/PNG.h"
#include "dsets.h"

class SquareMaze {
    public:
        //no parameter constructor
        SquareMaze();

        /*
        *Makes a new SquareMaze of the given height and width.

        If this object already represents a maze it will clear all 
        the existing data before doing so. You will start with a square grid 
        (like graph paper) with the specified height and width. You will 
        select random walls to delete without creating a cycle, until there are
        no more walls that could be deleted without creating a cycle. Do not 
        delete walls on the perimeter of the grid.

        Hints: You only need to store 2 bits per square: the "down" and "right" 
        walls. The finished maze is always a tree of corridors.)
        * */
        void makeMaze(int width, int height);

        /*
        *This uses your representation of the maze to determine whether it is 
        possible to travel in the given direction from the square at coordinates (x,y).

        For example, after makeMaze(2,2), the possible input coordinates will be 
        (0,0), (0,1), (1,0), and (1,1).

        dir = 0 represents a rightward step (+1 to the x coordinate)
        dir = 1 represents a downward step (+1 to the y coordinate)
        dir = 2 represents a leftward step (-1 to the x coordinate)
        dir = 3 represents an upward step (-1 to the y coordinate)
        You can not step off of the maze or through a wall.

        This function will be very helpful in solving the maze. It will also be used by 
        the grading program to verify that your maze is a tree that occupies the whole grid, 
        and to verify your maze solution. So make sure that this function works!
        */
        bool canTravel(int x, int y, int dir) const;

        /*
        Sets whether or not the specified wall exists.

        This function should be fast (constant time). You can assume that 
        in grading we will not make your maze a non-tree and then call one 
        of the other member functions. setWall should not prevent cycles from 
        occurring, but should simply set a wall to be present or not present. 
        Our tests will call setWall to copy a specific maze into your implementation.
        */
        void setWall(int x, int y, int dir, bool exists);

        /*
        *Solves this SquareMaze.

        For each square on the bottom row (maximum y coordinate), there is a distance from 
        the origin (i.e. the top-left cell), which is defined as the length (measured as a 
        number of steps) of the only path through the maze from the origin to that square.

        Select the square in the bottom row with the largest distance from the origin as the 
        destination of the maze. solveMaze() returns the winning path from the origin to the 
        destination as a vector of integers, where each integer represents the direction of a 
        step, using the same encoding as in canTravel().

        If multiple paths of maximum length exist, use the one with the destination cell that 
        has the smallest x value.

        Hint: this function should run in time linear in the number of cells in the maze.
        * */
        std::vector<int> solveMaze();

        /*
        *Draws the maze without the solution.

        First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where 
        height and width were the arguments to makeMaze. Blacken the entire topmost row and 
        leftmost column of pixels, except the entrance (1,0) through (9,0). For each square in the 
        maze, call its maze coordinates (x,y). If the right wall exists, then blacken the pixels 
        with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, then 
        blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

        The resulting PNG will look like the sample image, except there will be no exit from the 
        maze and the red line will be missing.
        * */
        cs225::PNG * drawMaze() const;

        /*
        *Makes a new SquareMaze of the given height and width.

        If this object already represents a maze it will clear all the existing data before doing 
        so. You will start with a square grid (like graph paper) with the specified height and 
        width. You will select random walls to delete without creating a cycle, until there are no 
        more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.

        Hints: You only need to store 2 bits per square: the "down" and "right" walls. 
        The finished maze is always a tree of corridors.)
        * */
        cs225::PNG * drawMazeWithSolution() const;

    private:
        void removeWalls();

        DisjointSets maze;
        std::map<int, int> rightMap;
        std::map<int, int> downMap;
        int w,h;
        std::map<int, bool> walls;
};