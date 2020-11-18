/* Your code here! */

#include "maze.h"
#include <queue>

// i dont know how large the default maze is supposed to be?
SquareMaze::SquareMaze() {
    w = 0;
    h = 0;
}

void SquareMaze::makeMaze(int width, int height) {
    w = width;
    h = height;
    maze.addelements(width * height);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int coord = i + (j * w);
            walls[coord] = true;
        }
    }

    for (int i = 0; i < width - 1; i++) {
        for (int j = 0; j < height; j++) {
            rightMap[i + (j * w)] = (i + 1) + (j * w);
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height - 1; j++) {
            downMap[i + (j * w)] = i + ((j + 1) * w);
        }
    }

    removeWalls();
}

void SquareMaze::removeWalls() {
    int randX, randY, rand;
    int toUnion;
    while (maze.size(0) != w*h) {
        randX = std::rand() % w; 
        randY = (std::rand() % h) * w;
        rand = randX + randY;

        // right perimeter
        if (randX < w - 1) {
            toUnion = rightMap.at(rand);
            if (maze.find(rand) != maze.find(toUnion)) {
                maze.setunion(rand, toUnion);
            }
            setWall(randX, randY, 0, false);
        }

        // bottom perimeter
        if (randY < h - 1) {
            toUnion = downMap.at(rand);
            if (maze.find(rand) != maze.find(toUnion)) {
                maze.setunion(rand, toUnion);
            }
            setWall(randX, randY, 1, false);
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0 && x + 1 >= w) {
        return false;
    } else if (dir == 1 && y + 1 >= h) {
        return false;
    } else if (dir == 2 && x - 1 < 0) {
        return false;
    } else if (dir == 3 && y - 1 < 0) {
        return false;
    }

    int newX = x; 
    int newY = y;

    if (dir == 0) {
        newX++;
    } else if (dir == 1) {
        newY++;
    } else if (dir == 2) {
        newX--;
    } else if (dir == 3) {
        newY--;
    }

    int coord = newX + (newY * w);
    if (walls.at(coord) == true) {
        return false;
    }

    return true;
}

void SquareMaze::setWall (int x, int y, int dir, bool exists) {
    if (dir == 0 && x + 1 >= w) {
        return;
    } else if (dir == 1 && y + 1 >= h) {
        return;
    }

    int newX = x; 
    int newY = y;

    if (dir == 0) {
        newX++;
    } else if (dir == 1) {
        newY++;
    }

    int coord = newX + (newY * w);
    walls[coord] = exists;
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> soln;
    return soln;

    std::queue<int> q;
    q.push(0); //origin aka root

    while (q.empty() == false) {
        break;
        int v = q.front();
        q.pop();
    }

    return soln;
}

cs225::PNG * SquareMaze::drawMaze() const {
    return NULL;
}

cs225::PNG * SquareMaze::drawMazeWithSolution() const {
    return NULL;
}
