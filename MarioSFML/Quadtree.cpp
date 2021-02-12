#include "Quadtree.h"

Quadtree::Quadtree() {
    this->x = 0.f;
    this->y = 0.f;
    this->halfDimension = 0.f;
    this->northWest = NULL;
    this->northEast = NULL;
    this->southWest = NULL;
    this->southEast = NULL;

}

Quadtree::Quadtree(float x, float y, float halfDimension) {
    this->x = x;
    this->y = y;
    this->halfDimension = halfDimension;
    this->northWest = NULL;
    this->northEast = NULL;
    this->southWest = NULL;
    this->southEast = NULL;
}

float Quadtree::getX() {
    return x;
}
float Quadtree::getY() {
    return y;
}
float Quadtree::getHalf() {
    return halfDimension;
}
void Quadtree::setXYHalf(float x, float y, float half) {
    this->x = x;
    this->y = y;
    this->halfDimension = half;
}

bool Quadtree::insert(float x, float y) {

    // Ignore objects that do not belong in this quad tree
    if (!(x >= this->x - this->halfDimension && x <= this->x + this->halfDimension && y >= this->y - this->y / 2 && y <= this->y + this->y / 2)) {
        //std::cout << "insert not in \n";
        return false; // object cannot be added
    }
    // If there is space in this quad tree and if doesn't have subdivisions, add the object here
    if (pointsX.size() < QT_NODE_CAPACITY && northWest == NULL)
    {
        //std::cout << "insert add \n";
        pointsX.push_back(x);
        pointsY.push_back(y);
        return true;
    }

    // Otherwise, subdivide and then add the point to whichever node will accept it
    if (northWest == NULL) {
        //std::cout << "insert sub \n";
        subdivide();
    }


    //We have to add the points/data contained into this quad array to the new quads if we only want 
    //the last node to hold the data 

    if (northWest->insert(x, y)) {
        //std::cout << "insert nw \n"; 
        return true;
    }
    if (northEast->insert(x, y)) {
        //std::cout << "insert ne \n"; 
        return true;
    }
    if (southWest->insert(x, y)) {
        //std::cout << "insert sw \n"; 
        return true;
    }
    if (southEast->insert(x, y)) {
        //std::cout << "insert se \n"; 
        return true;
    }



    // Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
    return false;
}

void Quadtree::subdivide() {
    //std::cout << (x - (halfDimension / 2)) << " x " << (y + (y / 2)) << " y " << halfDimension / 2 << " \n";
    northWest = new Quadtree((x - (halfDimension / 2)), (y - (y / 2)), halfDimension / 2);
    northEast = new Quadtree((x + (halfDimension / 2)), (y - (y / 2)), halfDimension / 2);
    southWest = new Quadtree((x - (halfDimension / 2)), (y + (y / 2)), halfDimension / 2);
    southEast = new Quadtree((x + (halfDimension / 2)), (y + (y / 2)), halfDimension / 2);
}

std::tuple <std::vector<float>, std::vector<float>> Quadtree::queryRange(float x, float y, float halfDimension) {
    // Prepare an array of results
    std::vector<float> pointsInRangeX;
    std::vector<float> pointsInRangeY;

    std::tuple <std::vector<float>, std::vector<float>> res;
    res = std::make_tuple(pointsInRangeX, pointsInRangeY);

    // Automatically abort if the range does not intersect this quad
    if (!(x >= this->x - this->halfDimension && x <= this->x + this->halfDimension && y >= this->y - this->y / 2 && y <= this->y + this->y / 2)) {
        //std::cout << "query empty \n";
        return res; // empty list
    }

    // Check objects at this quad level
    for (int p = 0; p < pointsX.size(); p++)
    {
        if ((pointsX[p] >= this->x - this->halfDimension && pointsX[p] <= this->x + this->halfDimension && pointsY[p] >= this->y - this->y / 2 && pointsY[p] <= this->y + this->y / 2)) {
            //std::cout << "query in \n";
            pointsInRangeX.push_back(x);
            pointsInRangeY.push_back(y);
        }
    }



    // Terminate here, if there are no children
    if (northWest == NULL) {
        //std::cout << "query no child \n";
        res = std::make_tuple(pointsInRangeX, pointsInRangeY);
        return res;
    }


    // Otherwise, add the points from the children
    std::tuple <std::vector<float>, std::vector<float>> resNW = northWest->queryRange(x, y, halfDimension);
    std::vector<float> temp = std::get<0>(resNW);
    //std::cout << temp[0] << "\n";
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resNW);
        pointsInRangeY.push_back(temp[0]);
    }

    std::tuple <std::vector<float>, std::vector<float>> resNE = northEast->queryRange(x, y, halfDimension);
    temp = std::get<0>(resNE);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resNE);
        pointsInRangeY.push_back(temp[0]);
    }

    std::tuple <std::vector<float>, std::vector<float>> resSW = southWest->queryRange(x, y, halfDimension);
    temp = std::get<0>(resSW);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resSW);
        pointsInRangeY.push_back(temp[0]);
    }

    std::tuple <std::vector<float>, std::vector<float>> resSE = southEast->queryRange(x, y, halfDimension);
    temp = std::get<0>(resSE);
    if (temp.size() > 0) {
        pointsInRangeX.push_back(temp[0]);
        temp = std::get<1>(resSE);
        pointsInRangeY.push_back(temp[0]);
    }

    //std::tuple <std::vector<float>, std::vector<float>> resTemp = std::make_tuple(pointsInRangeX, pointsInRangeY);
    //res = std::make_tuple(res, resTemp);
    res = std::make_tuple(pointsInRangeX, pointsInRangeY);
    //std::cout << "query added \n";
    return res;
}