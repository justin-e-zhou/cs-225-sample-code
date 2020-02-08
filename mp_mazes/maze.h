  
/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"
class SquareMaze {
    public:

        SquareMaze();
        void makeMaze(int width, int height);
        void makeNonCreativeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        bool canTravel(int x, int y, int dir);
        std::vector<int> solveMaze();
        cs225::PNG* drawMaze() const;
        cs225::PNG* drawMazeWithSolution();
        cs225::PNG* drawCreative();

        struct point {
            int _x, _y;
            point() :
                _x(0), _y(0) {}
            point(int x, int y) :
                _x(x), _y(y) {}
        };

    private:
        int _width;
        int _height;
        std::vector<bool> rightWalls;
        std::vector<bool> downWalls;
        std::vector<point> points;

        void solveMazeHelper(std::pair<std::vector<int>,int>& best, std::vector<int>& path, point curr);
};
