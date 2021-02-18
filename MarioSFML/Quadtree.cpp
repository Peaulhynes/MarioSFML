#include "Quadtree.h"

Quadtree::Quadtree(float x, float y, float halfDimensionX, float halfDimensionY) {
    this->x = x;
    this->y = y;
    this->halfDimensionX = halfDimensionX;
    this->halfDimensionY = halfDimensionY;
    this->northWest = nullptr;
    this->northEast = nullptr;
    this->southWest = nullptr;
    this->southEast = nullptr;
}

Quadtree::~Quadtree() {
    delete northWest;
    northWest = nullptr;
    delete northEast;
    northEast = nullptr;
    delete southWest;
    southWest = nullptr;
    delete southEast;
    southEast = nullptr;
}

/* Insert the coordinates and the type of the item with which the player can collide */
bool Quadtree::insert(float x, float y, std::string type) {

    // Ignore items that do not belong in this quad tree
    if (!(x >= this->x - this->halfDimensionX && x <= this->x + this->halfDimensionX && y >= this->y - this->halfDimensionY && y <= this->y + this->halfDimensionY)) {

        return false; // item cannot be added
    }
    // If there is space in this quad tree and if doesn't have subdivisions, add the item here
    if ((int)pointsX.size() < QT_NODE_CAPACITY && northWest == NULL)
    {

        pointsX.push_back(x);
        pointsY.push_back(y);
        this->type.push_back(type);
        return true;
    }

    // Otherwise, subdivide and then add the item to whichever node will accept it
    if (northWest == NULL) {

        subdivide();
    }

    //We have to add the items contained into this quad array to the new quads if we only want 
    //the last node to hold the item 

    if (northWest->insert(x, y, type)) {

        return true;
    }
    if (northEast->insert(x, y, type)) {

        return true;
    }
    if (southWest->insert(x, y, type)) {

        return true;
    }
    if (southEast->insert(x, y,type)) {

        return true;
    }

    // Otherwise, the item cannot be inserted for some unknown reason (this should never happen)
    return false;
}

/* Create quadtree children */
void Quadtree::subdivide() {

    northWest = new Quadtree((x - (halfDimensionX / 2)), (y - (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
    northEast = new Quadtree((x + (halfDimensionX / 2)), (y - (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
    southWest = new Quadtree((x - (halfDimensionX / 2)), (y + (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
    southEast = new Quadtree((x + (halfDimensionX / 2)), (y + (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
}

/* Get items that collide inside certain coordinates */
std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> Quadtree::queryRange(float x, float y, float halfDimensionX, float halfDimensionY) {

    std::vector<float> pointsInRangeX;
    std::vector<float> pointsInRangeY;
    std::vector<std::string> type;
    
    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res;
    res = std::make_tuple(pointsInRangeX, pointsInRangeY, type);


  
    // Automatically abort if the range does not intersect this quad
    if (!(x >= this->x - this->halfDimensionX && x <= this->x + this->halfDimensionX && y >= this->y - this->halfDimensionY && y <= this->y + this->halfDimensionY)) {

        return res; // empty 
    }

    // Check items at this quad level
    for (int p = 0; p < (int)pointsX.size(); p++)
    {

        if ((pointsX[p] >= x - halfDimensionX && pointsX[p] <= x + halfDimensionX && pointsY[p] >= y - halfDimensionY && pointsY[p] < y + halfDimensionY)) {
            pointsInRangeX.push_back(x);
            pointsInRangeY.push_back(y);
            type.push_back(this->type[p]);

        }
    }

    // Terminate here, if there are no children
    if (northWest == NULL) {

        res = std::make_tuple(pointsInRangeX, pointsInRangeY,type);

        return res;
    }

    // Otherwise, add the items from the children
    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> resNW = northWest->queryRange(x, y, halfDimensionX, halfDimensionY);
    std::vector<float> temp = std::get<0>(resNW);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resNW);
        pointsInRangeY.push_back(temp[0]);
        std::vector<std::string> temp = std::get<2>(resNW);
        type.push_back(temp[0]);
    }

    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> resNE = northEast->queryRange(x, y, halfDimensionX, halfDimensionY);
    temp = std::get<0>(resNE);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resNE);
        pointsInRangeY.push_back(temp[0]);
        std::vector<std::string> temp = std::get<2>(resNE);
        type.push_back(temp[0]);
    }

    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> resSW = southWest->queryRange(x, y, halfDimensionX,halfDimensionY);
    temp = std::get<0>(resSW);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resSW);
        pointsInRangeY.push_back(temp[0]);
        std::vector<std::string> temp = std::get<2>(resSW);
        type.push_back(temp[0]);
    }

    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> resSE = southEast->queryRange(x, y, halfDimensionX, halfDimensionY);
    temp = std::get<0>(resSE);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resSE);
        pointsInRangeY.push_back(temp[0]);
        std::vector<std::string> temp = std::get<2>(resSE);
        type.push_back(temp[0]);
    }


    res = std::make_tuple(pointsInRangeX, pointsInRangeY, type);

    return res;
}

/* Removes an item from the list of collisions thanks to its coordinates */
void Quadtree::removeItem(float x, float y, float halfDimensionX, float halfDimensionY) {

     // Automatically abort if the range does not intersect this quad
    if (!(x >= this->x - this->halfDimensionX && x <= this->x + this->halfDimensionX && y >= this->y - this->halfDimensionY && y <= this->y + this->halfDimensionY)) {
        return; // empty
    }

    // Check items at this quad level
      for (int p = 0; p < (int)pointsX.size(); p++)
    {
        if ((pointsX[p] >= x - halfDimensionX && pointsX[p] <= x + halfDimensionX && pointsY[p] >= y - halfDimensionY && pointsY[p] <= y + halfDimensionY)) {
            pointsX.erase(pointsX.begin() + p);
            pointsY.erase(pointsY.begin() + p);
            type.erase(type.begin() + p);
        }
    }

    // Terminate here, if there are no children
    if (northWest == NULL) {
        return;
    }

    // Otherwise, remove the items from the children
    northWest->removeItem(x, y, halfDimensionX, halfDimensionY);

    northEast->removeItem(x, y, halfDimensionX, halfDimensionY);

    southWest->removeItem(x, y, halfDimensionX, halfDimensionY);

    southEast->removeItem(x, y, halfDimensionX, halfDimensionY);

}