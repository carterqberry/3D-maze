//
// Created by Kaylee Dial on 3/9/22.
//

#ifndef INC_3DMAZE_MAZE_H
#define INC_3DMAZE_MAZE_H
#include "MazeInterface.h"
#include <sstream>

using namespace std;

class Maze : public MazeInterface {
public:
    Maze(int layers, int height, int width);
    ~Maze();

    int*** maze;
    enum mazeStatus {
        OPEN,
        BLOCKED,
        VISITED,
        EXIT,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        OUT,
        IN
    };

    // print maze
    string toString() const;

    // set value in the maze
    void setValue(int height, int width, int layer, int value);

    // starter function to find maze path
    bool find_maze_path();

    // recursive function to find maze path
    bool findMazePath_R(int height, int width, int layer);

    // friend
    friend ostream& operator<<(ostream& os, Maze& op) {
        return os << op.toString();
    }

private:
    int mHeight, mWidth, mLayers;
    bool isFinished = false;
};
#endif //INC_3DMAZE_MAZE_H
