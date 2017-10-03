#include <vec.h>
#include <cmath>
#include "OBB2D.h"

bool OBB2D::overlaps1Way(const OBB2D& other) const {
    for (int a = 0; a < 2; ++a) {

        double t = dot(other.corner[0], axis[a]);

        double tMin = t;
        double tMax = t;

        for (int c = 1; c < 4; ++c) {
            t = dot(other.corner[c], axis[a]);

            if (t < tMin) {
                tMin = t;
            } else if (t > tMax) {
                tMax = t;
            }
        }

        if ((tMin > 1 + origin[a]) || (tMax < origin[a])) {
            return false;
        }
    }

    return true;
}

void OBB2D::computeAxes() {
    axis[0] = corner[1] - corner[0];
    axis[1] = corner[3] - corner[0];

    for (int a = 0; a < 2; ++a) {
        axis[a] = axis[a] / length2(axis[a]);
        origin[a] = dot(corner[0], axis[a]);
    }
}

Mesh& OBB2D::getMesh() {
    return mesh;
}

Transform OBB2D::getPos() {
    return Translation(centre.x, centre.y,1);
}

OBB2D::OBB2D(const vec2& center, const double w, const double h, double angle){
    height = h;
    width = w;
    centre = center;
    mesh = Mesh(GL_TRIANGLES);
    vec2 X( cos(angle), sin(angle));
    vec2 Y(-sin(angle), cos(angle));

    X = X * (w / 2);
    Y = Y * (h / 2);

    corner[0] = center - X - Y;
    corner[1] = center + X - Y;
    corner[2] = center + X + Y;
    corner[3] = center - X + Y;

    mesh.vertex(vec3(corner[0].x, corner[0].y, 1));
    mesh.vertex(vec3(corner[1].x, corner[1].y, 1));
    mesh.vertex(vec3(corner[2].x, corner[2].y, 1));
    mesh.vertex(vec3(corner[0].x, corner[0].y, 1));
    mesh.vertex(vec3(corner[2].x, corner[2].y, 1));
    mesh.vertex(vec3(corner[3].x, corner[3].y, 1));

    computeAxes();
}

void OBB2D::move(const vec2& center, const float angle) {

    centre = center;
    vec2 X( cos(angle), sin(angle));
    vec2 Y(-sin(angle), cos(angle));

    X = X * (width / 2);
    Y = Y * (height / 2);

    corner[0] = center - X - Y;
    corner[1] = center + X - Y;
    corner[2] = center + X + Y;
    corner[3] = center - X + Y;

    mesh.vertex(0, vec3(corner[0].x, corner[0].y, 1));
    mesh.vertex(1, vec3(corner[1].x, corner[1].y, 1));
    mesh.vertex(2, vec3(corner[2].x, corner[2].y, 1));
    mesh.vertex(3, vec3(corner[0].x, corner[0].y, 1));
    mesh.vertex(4, vec3(corner[2].x, corner[2].y, 1));
    mesh.vertex(5, vec3(corner[3].x, corner[3].y, 1));

    computeAxes();
}

bool OBB2D::overlaps(const OBB2D& other) const {
    return overlaps1Way(other) && other.overlaps1Way(*this);
}