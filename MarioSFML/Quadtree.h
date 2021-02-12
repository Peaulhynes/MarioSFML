#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
//#include <iostream>
#include<tuple>
#include <iostream>

class Quadtree
{
private:
    // Arbitrary constant to indicate how many elements can be stored in this quad tree node
    const int QT_NODE_CAPACITY = 4;

    // Axis-aligned bounding box stored as a center with half-dimensions
    // to represent the boundaries of this quad tree
    float x;
    float y;
    float halfDimension;

    // Points in this quad tree node
    std::vector<float> pointsX;
    std::vector<float> pointsY;

    // Children
    Quadtree* northWest;
    Quadtree* northEast;
    Quadtree* southWest;
    Quadtree* southEast;

public:
    // Methods
    Quadtree();
    Quadtree(float x, float y, float halfDimension);
   /* Quadtree operator=(const Quadtree q) {
        Quadtree res(q.x, q.y, q.halfDimension);
        return res;
    }*/
    bool insert(float x, float y);
    // create four children that fully divide this quad into four quads of equal area
    void subdivide();
    std::tuple <std::vector<float>, std::vector<float>> queryRange(float x, float y, float halfDimension);

    float getX();
    float getY();
    float getHalf();
    void setXYHalf(float x, float y, float half);
};

#endif // !QUADTREE_H