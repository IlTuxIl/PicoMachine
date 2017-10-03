//
// Created by julien on 23/05/17.
//

#include "CheckPoints.h"
#include "fstream"

CheckPoints::CheckPoints(std::string filename) {
    std::ifstream file(filename, std::ios::in);
    //image I/O
    int nbCheckPoints;
    file >> nbCheckPoints;
    coord_ = std::vector<Point>(nbCheckPoints);
    angles_ = std::vector<float>(nbCheckPoints);

    for(int i = 0; i < nbCheckPoints; i++){
        file >> coord_[i].x >> coord_[i].y >> coord_[i].z >> angles_[i];
//        std::cout << coord_[i] << std::endl;
    }

    file.close(); //close stream.
}

int CheckPoints::collideWith(const Point &player) {
    int i = 0;

    int width = 5;
    int height = 5;


    for(Point p : coord_){
        if(player.x < p.x + width && player.x > p.x - width && player.y < p.y + height && player.y > p.y - height){
            return i;
        }
        i++;
    }
    return -1;
}

int CheckPoints::nbCheckPoint(){
    return coord_.size();
}

Point& CheckPoints::getCheckPoint(int i) {
    return coord_[i];
}

float& CheckPoints::getAngle(int i){
    return angles_[i];
}