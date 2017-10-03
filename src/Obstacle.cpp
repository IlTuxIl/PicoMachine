//
// Created by julien on 28/05/17.
//

#include <texture.h>
#include "Obstacle.h"

Obstacle::Obstacle(std::string filename, std::string texturename, const Transform &transform_){
    mesh = read_mesh(filename.data());
    if(texturename != "")
        texture_ = read_texture(1, texturename.data());
    else
        mesh.default_color(Color(0.8f, 0.8f, 0.8f));
    transform = transform_;
    init();
}

Obstacle::Obstacle(Mesh& mesh_, GLuint& tex_, const Transform &transform_){
    mesh = mesh_;
    texture_ = tex_;
    transform = transform_;
    init();
}

/**
 * La fonction init() récupere les valeurs min et max du mesh (dans le repère monde)
 * puis génère l'OBB.
 */
void Obstacle::init() {
    float xMin, xMax, yMin, yMax;
    xMin = 999;
    xMax = -999;
    yMin = 999;
    yMax = -999;

    for(vec3 p : mesh.positions()){
        Point tmp = transform(Point(p));
        if(tmp.x < xMin)
            xMin = tmp.x;
        if(tmp.x > xMax)
            xMax = tmp.x;
        if(tmp.y < yMin)
            yMin = tmp.y;
        if(tmp.y > yMax)
            yMax = tmp.y;
    }

    float angle = 0;//-atan2(transform(Vector(1,0,0)).x, transform(Vector(1,0,0)).y);
    collider = OBB2D(vec2(xMin + (xMax-xMin)/2, yMin + (yMax-yMin)/2), (xMax-xMin), (yMax-yMin), angle);
}

bool Obstacle::collide(const OBB2D& player) {
    return collider.overlaps(player);
}
