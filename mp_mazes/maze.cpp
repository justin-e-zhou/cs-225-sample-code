/* Your code here! */
#include "maze.h"
#include <vector>
#include <algorithm>
#include "dsets.h"
#include <ctime>
#include <queue>

using std::queue;

SquareMaze::SquareMaze() { }

void SquareMaze::makeMaze(int width, int height) {
    //set maze parameters
    _width = width;
    _height = height;
    for(int y = 0; y < _height; ++y) {
        for(int x = 0; x < _width; ++x) {
            points.push_back(point(x, y));
            points.push_back(point(x, y));
            rightWalls.push_back(true);
            downWalls.push_back(true);
        }
    }
    srand((unsigned int)std::time(0));
    std::random_shuffle(points.begin(), points.end());  //shuffle vector of points
    DisjointSets dset;
    dset.addelements(_width * _height); //initialize disjointed set
    for(auto i : points) {  //for each point in the vector of points
        int x = i._x;       //use random generator to determine which wall to remove
        int y = i._y;
        int coord = y * _width + x;
        int removeWall = rand() % 2;

        if(removeWall) {    //remove down wall
            if(y != (_height - 1) &&  //test if able to remove bottom wall
            dset.find(coord) != dset.find(coord + _width)) {
                dset.setunion(coord, coord + _width);
                downWalls[coord] = false;
            } else if(y == _height - 1) {
                downWalls[coord] = false;
            }
            else if(x != (_width - 1) &&   //else remove right wall
            dset.find(coord) != dset.find(coord + 1)) {
                dset.setunion(coord, coord + 1);
                rightWalls[coord] = false;
            } else if(x == _width - 1) {
                rightWalls[coord] = false;
            }
        } else {    //else remove right wall
            if(x != (_width - 1) &&   //test if able to remove right wall,
            dset.find(coord) != dset.find(coord + 1)) {
                dset.setunion(coord, coord + 1);
                rightWalls[coord] = false;
            } else if(x == _height - 1) {
                rightWalls[coord] = false;
            }
            else if(y != (_height - 1) &&  //else remove bottom wall
            dset.find(coord) != dset.find(coord + _width)) {
                dset.setunion(coord, coord + _width);
                downWalls[coord] = false;
            }
            else if(y == _height - 1) {
                downWalls[coord] = false;
            }
        }
    }
}

void SquareMaze::makeNonCreativeMaze(int width, int height) {
    _width = width;
    _height = height;
    double slope = (double)_height / (double)_width;
    for(int y = 0; y < _height; ++y) {
        for(int x = 0; x < _width; ++x) {
            if(y + 1 < x * (-slope) + _height) {
                points.push_back(point(x, y));
                points.push_back(point(x, y));
            }
            rightWalls.push_back(true);
            downWalls.push_back(true);
        }
    }
    srand((unsigned int)std::time(0));
    std::random_shuffle(points.begin(), points.end());  //shuffle vector of points
    DisjointSets dset;
    dset.addelements(_width * _height); //initialize disjointed set
    for(auto i : points) {  //for each point in the vector of points
        int x = i._x;       //use random generator to determine which wall to remove
        int y = i._y;
        int coord = y * _width + x;
        int removeWall = rand() % 2;
        if(removeWall) {    //remove down wall
            if(y != (_height - 1) &&  //test if able to remove bottom wall
            dset.find(coord) != dset.find(coord + _width)) {
                dset.setunion(coord, coord + _width);
                downWalls[coord] = false;
            } else if(y == _height - 1) {
                downWalls[coord] = false;
            }
            else if(x != (_width - 1) &&   //else remove right wall
            dset.find(coord) != dset.find(coord + 1)) {
                dset.setunion(coord, coord + 1);
                rightWalls[coord] = false;
            } else if(x == _width - 1) {
                rightWalls[coord] = false;
            }
        } else {    //else remove right wall
            if(x != (_width - 1) &&   //test if able to remove right wall,
            dset.find(coord) != dset.find(coord + 1)) {
                dset.setunion(coord, coord + 1);
                rightWalls[coord] = false;
            } else if(x == _height - 1) {
                rightWalls[coord] = false;
            }
            else if(y != (_height - 1) &&  //else remove bottom wall
            dset.find(coord) != dset.find(coord + _width)) {
                dset.setunion(coord, coord + _width);
                downWalls[coord] = false;
            }
            else if(y == _height - 1) {
                downWalls[coord] = false;
            }
        }
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if(dir) {   //set down wall at (x,y) if dir == 1
        downWalls[y * _width + x] = exists;
    } else {    //else set right wall at (x,y)
        rightWalls[y * _width + x] = exists;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) {
    switch(dir) {
        case 0: //right
            return (x != _width - 1) && !rightWalls[y * _width + x];
        case 1: //down
            return (y != _height - 1) && !downWalls[y * _width + x];
        case 2: //left
            return (x != 0) && !rightWalls[y * _width + x - 1];
        case 3: //up
            return (y != 0) && !downWalls[(y - 1) * _width + x];
    }
    return false;
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> solved;
    std::vector<std::pair<std::vector<int>,int>> pathpairs;
    std::vector<int> path;
    SquareMaze::point start(0, 0);
    unsigned int longestIdx = 0;
    unsigned int longestSize = 0;
    int smallestx;

    //std::cout << "solving maze...\nmaze is " << _width << " x " << _height << std::endl;

    path.push_back(1); //temp direction to indicate start of maze
    std::pair<std::vector<int>,int> best(std::vector<int>(),_width);
    solveMazeHelper(best, path, start);
    auto ret = best.first;
    ret.erase(ret.begin());
    return ret;
}

void SquareMaze::solveMazeHelper(std::pair<std::vector<int>,int>& best, std::vector<int>& path1, point curr1) {
    queue<std::pair<vector<int>,point>> q;
    q.push(std::pair<vector<int>,point>(path1,curr1));
    int x;
    int y;
    int prevDir;
    int prevCellDir;
    std::vector<int> path;
    std::pair<std::vector<int>,point> params;
    int sols = 0;
    int n_dir;
    do {
        params = q.front();
        q.pop();
        point curr = params.second;
        path = params.first;
        x = curr._x;
        y = curr._y;
        prevDir = path[path.size() - 1];
        prevCellDir = (prevDir + 2) & 3;
        SquareMaze::point temp;

        if(y == _height - 1) {  //if at the bottom row
            if (x < best.second && path.size() == best.first.size()) {
                    best = std::pair<std::vector<int>,int>(path,curr._x);
                }  //push path to paths
            if (path.size() > best.first.size()) {
                best = std::pair<std::vector<int>,int>(path,curr._x);
            }
            if (++sols == _width) return;
        }
        for (int i: {1,0,3}) {
            n_dir = (prevDir + i)&3;
            if (!canTravel(x,y,n_dir)) continue;
            temp = curr;
            switch (n_dir)
            {
            case 0:
                ++temp._x;
                break;
            case 1:
                ++temp._y;
                break;
            case 2:
                --temp._x;
                break;
            case 3:
                --temp._y;
                break;
            default:
                break;
            }
            path.push_back(n_dir);
            q.push(std::pair<vector<int>,point>(path,temp));
            path.pop_back();
        }
    } while (!q.empty());
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* maze = new cs225::PNG(_width * 10 + 1, _height * 10 + 1);
    cs225::HSLAPixel black(0, 1.0, 0, 1.0);
    
    //make black border
    for(unsigned int x = 0; x < maze->width(); ++x) {    //draw top and bottom border
        cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(x, 0);
        if(x < 1 || x > 9) {    //don't draw entrance
            *pixel = black;
        }
        pixel = &const_cast<cs225::PNG *>(maze)->getPixel(x, maze->height() - 1);
        *pixel = black;
    }
    for(unsigned int y = 0; y < maze->height(); ++y) {   //draw left and right border
        cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(0, y);
        *pixel = black;
        pixel = &const_cast<cs225::PNG *>(maze)->getPixel(maze->width() - 1, y);
        *pixel = black;
    }

    //draw rest of the walls
    for(int y = 0; y < _height; ++y) {
        for(int x = 0; x < _width; ++x) {
            int coord = y * _width + x;
            if(rightWalls[coord]) {
                for(int i = y * 10; i < y * 10 + 11; ++i) {
                    cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(x * 10 + 10, i);
                    *pixel = black;
                }
            }
            if(downWalls[coord]) {
                for(int i = x * 10; i < x * 10 + 11; ++i) {
                    cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(i, y * 10 + 10);
                    *pixel = black;
                }
            }
        }
    }
    return maze;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    cs225::PNG* maze = drawMaze();  //get base maze png
    std::vector<int> path = solveMaze();    //path vector
    cs225::HSLAPixel red(0, 1, 0.5, 1); //helper variables
    cs225::HSLAPixel white;
    unsigned int x = 0;
    unsigned int y = 0;

    for(auto i: path) { //iterate through path
        switch (i) {
        case 0: //if right, draw red line from middle of current cell to middle of next cell
            for(int i = 0; i <= 10; ++i) {
                maze->getPixel(x * 10 + 5 + i, y * 10 + 5) = red;
            }
            x += 1;
            break;
        case 1: //down
            for(int i = 0; i <= 10; ++i) {
                maze->getPixel(x * 10 + 5, y * 10 + 5 + i) = red;
            }
            y += 1;
            break;
        case 2: //left
            for(int i = 0; i <= 10; ++i) {
                maze->getPixel(x * 10 + 5 - i, y * 10 + 5) = red;
            }
            x -= 1;
            break;
        case 3: //up
            for(int i = 0; i <= 10; ++i) {
                maze->getPixel(x * 10 + 5, y * 10 + 5 - i) = red;
            }
            y -= 1;
            break;
        }
    }
    for(int i = 1; i < 10; ++i) {
        maze->getPixel(x * 10 + i, (y + 1) * 10) = white;
    }
    return maze;
}

cs225::PNG* SquareMaze::drawCreative() {
    cs225::PNG* maze = new cs225::PNG(_width * 10 + 1, _height * 10 + 1);
    cs225::HSLAPixel black(0, 1.0, 0, 1.0);
    
    //make black border
    for(unsigned int x = 0; x < maze->width(); ++x) {    //draw top and bottom border
        cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(x, 0);
        if(x < 1 || x > 9) {    //don't draw entrance
            *pixel = black;
        }
        //pixel = &const_cast<cs225::PNG *>(maze)->getPixel(x, maze->height() - 1);
        //*pixel = black;
    }
    for(unsigned int y = 0; y < maze->height(); ++y) {   //draw left and right border
        cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(0, y);
        *pixel = black;
        //pixel = &const_cast<cs225::PNG *>(maze)->getPixel(maze->width() - 1, y);
        //*pixel = black;
    }

    //draw rest of the walls
    for(int y = 0; y < _height; ++y) {
        for(int x = 0; x < _width; ++x) {
            double slope = (double) _height / (double) _width;
            int coord = y * _width + x;
            if(y < x * (-slope) + _height) {
                if(rightWalls[coord]) {
                    for(int i = y * 10; i < y * 10 + 11; ++i) {
                        cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(x * 10 + 10, i);
                        *pixel = black;
                    }
                }
                if(downWalls[coord]) {
                    for(int i = x * 10; i < x * 10 + 11; ++i) {
                        cs225::HSLAPixel* pixel = &const_cast<cs225::PNG *>(maze)->getPixel(i, y * 10 + 10);
                        *pixel = black;
                    }
                }
            }
        }
    }
    return maze;
}