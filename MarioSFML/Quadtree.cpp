#include "Quadtree.h"
#include <iostream>

Quadtree::Quadtree() {
    this->x = 0.f;
    this->y = 0.f;
    this->halfDimensionX = 0.f;
    this->halfDimensionY = 0.f;
    this->northWest = NULL;
    this->northEast = NULL;
    this->southWest = NULL;
    this->southEast = NULL;

}

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

float Quadtree::getX() {
    return x;
}
float Quadtree::getY() {
    return y;
}
float Quadtree::getHalfX() {
    return halfDimensionX;
}
float Quadtree::getHalfY() {
    return halfDimensionY;
}
void Quadtree::setXYHalf(float x, float y, float halfX, float halfY) {
    this->x = x;
    this->y = y;
    this->halfDimensionX = halfX;
    this->halfDimensionY = halfY;
}

bool Quadtree::insert(float x, float y, std::string type) {

    // Ignore objects that do not belong in this quad tree
    if (!(x >= this->x - this->halfDimensionX && x <= this->x + this->halfDimensionX && y >= this->y - this->halfDimensionY && y <= this->y + this->halfDimensionY)) {
        //std::cout << "insert not in \n";
        return false; // object cannot be added
    }
    // If there is space in this quad tree and if doesn't have subdivisions, add the object here
    if ((int)pointsX.size() < QT_NODE_CAPACITY && northWest == NULL)
    {
        //std::cout << "insert add \n";
        pointsX.push_back(x);
        pointsY.push_back(y);
        this->type.push_back(type);
        return true;
    }

    // Otherwise, subdivide and then add the point to whichever node will accept it
    if (northWest == NULL) {
        //std::cout << "insert sub \n";
        subdivide();
    }


    //We have to add the points/data contained into this quad array to the new quads if we only want 
    //the last node to hold the data 

    if (northWest->insert(x, y, type)) {
        //std::cout << "insert nw \n"; 
        return true;
    }
    if (northEast->insert(x, y, type)) {
        //std::cout << "insert ne \n"; 
        return true;
    }
    if (southWest->insert(x, y, type)) {
        //std::cout << "insert sw \n"; 
        return true;
    }
    if (southEast->insert(x, y,type)) {
        //std::cout << "insert se \n"; 
        return true;
    }



    // Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
    return false;
}

void Quadtree::subdivide() {
    //std::cout << (x - (halfDimension / 2)) << " x " << (y + (y / 2)) << " y " << halfDimension / 2 << " \n";
    northWest = new Quadtree((x - (halfDimensionX / 2)), (y - (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
    northEast = new Quadtree((x + (halfDimensionX / 2)), (y - (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
    southWest = new Quadtree((x - (halfDimensionX / 2)), (y + (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
    southEast = new Quadtree((x + (halfDimensionX / 2)), (y + (halfDimensionY / 2)), halfDimensionX / 2, halfDimensionY/2);
}

std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> Quadtree::queryRange(float x, float y, float halfDimensionX, float halfDimensionY) {
    // Prepare an array of results
    std::vector<float> pointsInRangeX;
    std::vector<float> pointsInRangeY;
    std::vector<std::string> type;
    
    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res;
    res = std::make_tuple(pointsInRangeX, pointsInRangeY, type);

   // std::cout << this->x - this->halfDimensionX << " x " << this->y - this->halfDimensionY  << " y "<< std::endl;
  
    // Automatically abort if the range does not intersect this quad
    if (!(x >= this->x - this->halfDimensionX && x <= this->x + this->halfDimensionX && y >= this->y - this->halfDimensionY && y <= this->y + this->halfDimensionY)) {
        //std::cout << "query empty \n";
        return res; // empty list
    }
    //std::cout << pointsX.size() << "\n";
    // Check objects at this quad level
    for (int p = 0; p < (int)pointsX.size(); p++)
    {
        //std::cout << pointsX[p] << std::endl;
        if ((pointsX[p] >= x - halfDimensionX && pointsX[p] <= x + halfDimensionX && pointsY[p] >= y - halfDimensionY && pointsY[p] < y + halfDimensionY)) {
            pointsInRangeX.push_back(x);
            pointsInRangeY.push_back(y);
            type.push_back(this->type[p]);
            //std::cout << "adddddddddddddd" << std::endl;
        }
    }



    // Terminate here, if there are no children
    if (northWest == NULL) {
        //std::cout << "query no child \n";
        res = std::make_tuple(pointsInRangeX, pointsInRangeY,type);
        // std::cout << std::get<0>(res).size() << "\n";
        return res;
    }


    // Otherwise, add the points from the children
    std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> resNW = northWest->queryRange(x, y, halfDimensionX, halfDimensionY);
    std::vector<float> temp = std::get<0>(resNW);
    //std::cout << temp[0] << "\n";
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

    //std::tuple <std::vector<float>, std::vector<float>> resTemp = std::make_tuple(pointsInRangeX, pointsInRangeY);
    //res = std::make_tuple(res, resTemp);
    res = std::make_tuple(pointsInRangeX, pointsInRangeY, type);
    //std::cout << "query added \n";
    return res;
}

void Quadtree::removeItem(float x, float y, float halfDimensionX, float halfDimensionY) {

     // Automatically abort if the range does not intersect this quad
    if (!(x >= this->x - this->halfDimensionX && x <= this->x + this->halfDimensionX && y >= this->y - this->halfDimensionY && y <= this->y + this->halfDimensionY)) {
        return; // empty
    }

    // Check objects at this quad level
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


    // Otherwise, remove the points from the children
    northWest->removeItem(x, y, halfDimensionX, halfDimensionY);

    northEast->removeItem(x, y, halfDimensionX, halfDimensionY);

    southWest->removeItem(x, y, halfDimensionX, halfDimensionY);

    southEast->removeItem(x, y, halfDimensionX, halfDimensionY);

}