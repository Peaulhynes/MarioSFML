#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <tuple>
#include <iostream>

class Quadtree
{

public:
    Quadtree();
    Quadtree(float x, float y, float halfDimensionX, float haldDimensionY);
    ~Quadtree();

    bool insert(float x, float y, std::string type);
    void subdivide();
    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> queryRange(float x, float y, float halfDimensionX, float halfDimensionY);
    void removeItem(float x, float y, float halfDimensionX, float halfDimensionY);
    /*
    float getX();
    float getY();
    float getHalfX();
    float getHalfY();
    void setXYHalf(float x, float y, float halfX, float halfY);*/

private:
    const int QT_NODE_CAPACITY = 4;

    float x;
    float y;
    float halfDimensionX;
    float halfDimensionY;

    std::vector<float> pointsX;
    std::vector<float> pointsY;
    std::vector<std::string> type;

    Quadtree* northWest;
    Quadtree* northEast;
    Quadtree* southWest;
    Quadtree* southEast;
};

#endif // !QUADTREE_H