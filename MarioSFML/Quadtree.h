#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <tuple>
#include <iostream>

class Quadtree
{

public:
    Quadtree(float x, float y, float halfDimensionX, float haldDimensionY);
    ~Quadtree();

    /* Insert the coordinates and the type of the item with which the player can collide */
    bool insert(float x, float y, std::string type);

    /* Create quadtree children */
    void subdivide();

    /* Get items that collide inside certain coordinates */
    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> queryRange(float x, float y, float halfDimensionX, float halfDimensionY);
    
    /* Removes an item from the list of collisions thanks to its coordinates */
    void removeItem(float x, float y, float halfDimensionX, float halfDimensionY);

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