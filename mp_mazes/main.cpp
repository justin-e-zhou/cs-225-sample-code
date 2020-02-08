#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    /*
    SquareMaze maze;
    maze.makeNonCreativeMaze(30, 30);
    cs225::PNG* mazePNG = maze.drawCreative();
    mazePNG->writeToFile("creative.png");
*/
    SquareMaze maze2;
    maze2.makeMaze(200, 200);
    //maze2.solveMaze();
    cs225::PNG* mazePNG2 = maze2.drawMaze();
    mazePNG2->writeToFile("regular.png");
    cs225::PNG* mazePNG2Sol = maze2.drawMazeWithSolution();
    mazePNG2Sol->writeToFile("regularSolved.png");
}
