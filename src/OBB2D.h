//
// Created by julien on 06/04/17.
//

#ifndef PICOMACHINE_OBB2D_H
#define PICOMACHINE_OBB2D_H

#include "mesh.h"

/**
 * La class OBB2D permet de gérer les collisions entre les 2 joueurs
 */
class OBB2D {
private:
    vec2 corner[4];
    vec2 axis[2];

    vec2 centre;
    double origin[2];

    double height;
    double width;

    bool overlaps1Way(const OBB2D& other) const;
    void computeAxes();
    Mesh mesh;
public:
    OBB2D(){};
    OBB2D(const vec2& center, const double w, const double h, double angle);
    void move(const vec2& center, const float angle);
    bool overlaps(const OBB2D& other) const;
    Mesh& getMesh();
    Transform getPos();

};

#endif //PICOMACHINE_OBB2D_H
