//
// Created by Kaylee Dial on 3/9/22.
//

#include "Maze.h"
#include <iostream>
using namespace std;

// constructor
Maze::Maze(int layers, int height, int width) {
    mLayers = layers;
    mHeight = height;
    mWidth = width;

    // set pointers within maze array
    maze = new int**[layers];
    for (int i = 0; i < layers; ++i) {
        maze[i] = new int* [height];
        for (int j = 0; j < height; ++j) {
            maze[i][j] = new int[width];
        }
    }
}

// destructor
Maze::~Maze() {
    for (int i = 0; i < mLayers; i++) {
        // delete cell [i][j]
        for (int j = 0; j < mHeight; j++) {
            delete[] maze[i][j];
        }
        // delete layer[i]
        delete[] maze[i];
    }
    // delete maze
    delete[] maze;
}

// print function
string Maze::toString() const {
    stringstream outStr;

    // put 'X' and '_' for 1s and 0s
    outStr << "Solve Maze:" << endl;
    // loop through layers
    for (int i = 0; i < mLayers; ++i) {
        outStr << "Layer " << i + 1 << endl;
        // loop though height
        for (int j = 0; j < mHeight; ++j) {
            // loop through width
            for (int k = 0; k < mWidth; ++k) {
                if (maze[i][j][k] == 1) {
                    outStr << " " << 'X';
                } else {
                    outStr << " " << '_';
                }
            }
            outStr << endl;
        }
    }

    // Prints the maze solution
    if (isFinished) {
        outStr << endl << "Solution:" << endl;
        // loop through layers
        for (int i = 0; i < mLayers; ++i) {
            outStr << "Layer " << i + 1 << endl;
            // loop through height
            for (int j = 0; j < mHeight; ++j) {
                // loop through width
                for (int k = 0; k < mWidth; ++k) {
                    //string cellChar = "";
                    if (maze[i][j][k] == OPEN) {
                        outStr << " " << '_';
                    } else if (maze[i][j][k] == BLOCKED) {
                        outStr << " " << 'X';
                    }
                    else if (maze[i][j][k] == UP) {
                        outStr << " " << 'U';
                    }
                    else if (maze[i][j][k] == DOWN) {
                        outStr << " " << 'D';
                    }
                    else if (maze[i][j][k] == RIGHT) {
                        outStr << " " << 'R';
                    }
                    else if (maze[i][j][k] == LEFT) {
                        outStr << " " << 'L';
                    }
                    else if (maze[i][j][k] == IN) {
                        outStr << " " << 'I';
                    }
                    else if (maze[i][j][k] == OUT) {
                        outStr << " " << 'O';
                    }
                    else if (maze[i][j][k] == VISITED) {
                        outStr << " " << '*';
                    }
                    else if (maze[i][j][k] == EXIT) {
                        outStr << " " << 'E';
                    } else {
                        outStr << " " << '?';
                    }
                }
                outStr << endl;
            }
        }
    } else {
        outStr << endl;
        outStr << "No Solution Exists!";
    }
    return outStr.str();
}

// set value in maze
void Maze::setValue(int height, int width, int layer, int value) {
    maze[layer][height][width] = value;
}

// starter function to find the maze path
bool Maze::find_maze_path() {
    isFinished = false;

    // set value on last spot = EXIT
    setValue(mHeight - 1, mWidth - 1, mLayers - 1, EXIT);

    // call recursive function
    return findMazePath_R(0, 0, 0);
}

// recursive function to find the maze path
bool Maze::findMazePath_R(int height, int width, int layer) {
    bool isSolvable;

    // check if maze is solvable
    if (height < 0 || layer < 0 || width < 0) {
        isSolvable = false;
        return isSolvable;
    }
    if (height + 1 > mHeight || layer + 1 > mLayers || width + 1 > mWidth) {
        isSolvable = false;
        return isSolvable;
    }

    // if cell == EXIT
    if (maze[layer][height][width] == EXIT) {
        isFinished = true;
        isSolvable = true;
        return isSolvable;
    }

    // if cell == OPEN
    if (maze[layer][height][width] != OPEN) {
        isSolvable = false;
        return isSolvable;
    }

    // mark visited cells
    maze[layer][height][width] = VISITED;

    // if cell == LEFT
    if (findMazePath_R(height, width - 1, layer)) {
        if (isFinished) {
            maze[layer][height][width] = LEFT;
        }
        isSolvable = true;
        return isSolvable;
    }
    // if cell == RIGHT
    else if (findMazePath_R(height, width + 1, layer)) {
        if (isFinished) {
            maze[layer][height][width] = RIGHT;
        }
        isSolvable = true;
        return isSolvable;
    }
    // if cell == UP
    else if (findMazePath_R(height - 1, width, layer)) {
        if (isFinished) {
            maze[layer][height][width] = UP;
        }
        isSolvable = true;
        return isSolvable;
    }
    // if cell == DOWN
    else if (findMazePath_R(height + 1, width, layer)) {
        if (isFinished) {
            maze[layer][height][width] = DOWN;
        }
        isSolvable = true;
        return isSolvable;
    }
    // if cell == OUT
    else if (findMazePath_R(height, width, layer - 1)) {
        if (isFinished) {
            maze[layer][height][width] = OUT;
        }
        isSolvable = true;
        return isSolvable;
    }
    // if cell == IN
    else if (findMazePath_R(height, width, layer + 1)) {
        if (isFinished){
            maze[layer][height][width] = IN;
        }
        isSolvable = true;
        return isSolvable;
    }
    else {
        isSolvable = false;
        return isSolvable;
    }
}





