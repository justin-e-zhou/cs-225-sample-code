#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

// The main function is used to call all the
// functions necessary to create solved and 
// unsolved mazes.
int main()
{
    // Write your own main here
    int a, b;
    printf("Enter the width and height of the maze to create\n");
    printf("Width: ");
    scanf("%d", &a);
    printf("\nHeight: ");
    scanf("%d", &b);
    printf("\n");
    SquareMaze maze2;
    maze2.makeMaze(a, b);
    cs225::PNG* mazePNG2 = maze2.drawMaze();
    mazePNG2->writeToFile("regular.png");
    cs225::PNG* mazePNG2Sol = maze2.drawMazeWithSolution();
    mazePNG2Sol->writeToFile("regularSolved.png");
}
