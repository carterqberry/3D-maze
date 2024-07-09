#include <iostream>
#include <fstream>
#include "Maze.h"

using namespace std;

int main(int argc, char* argv[]) {
    // reading inputs / outputs
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    } else {
        cout << argv[1] << " opened successfully.\n";
    }
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    } else {
        cout << argv[2] << " opened successfully.\n";
    }

    int height = 0;
    int width = 0;
    int layers = 0;

    string row;
    getline(in, row);
    istringstream iss(row);
    iss >> height >> width >> layers;

    // make myMaze object
    Maze myMaze(layers, height, width);

    // loop through number of layers
    for (int l = 0; l < layers; l++) {
        // loop through height
        for (int h = 0; h < height; h++) {
            getline(in, row);
            string strNum;
            // if row is empty, get the next row
            if (row.empty()){
                getline(in, row);
            }
            // loop through width
            for (int w = 0; w < width; w++) {
                strNum = row.substr(0, 1);
                if (row.size() != 1) {
                    row = row.substr(2, row.size());
                }
                // set value in myMaze array
                myMaze.setValue(h, w, l, stoi(strNum));
            }
        }
    }
    // call starter find maze path function
    myMaze.find_maze_path();
    out << myMaze;

    return 0;
}
