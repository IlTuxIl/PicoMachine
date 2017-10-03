//
// Created by julien on 08/04/17.
//

#include "Terrain.h"
#include "texture.h"
#include <cmath>

using std::vector;

vector<Barycentre> calculeBarycentre(Mesh mesh, int part){
    std::vector<Barycentre> ret;
    for(int i = 0; i < mesh.triangle_count(); i++){

        TriangleData triangle = mesh.triangle(i);
        Barycentre tmp;
        tmp.barycentre = Vector(triangle.a + triangle.b + triangle.c)/3;
        tmp.id = i;
        switch(part){
            case 0:
                if(tmp.barycentre.x <= 0)
                    ret.push_back(tmp);
                break;
            case 1:
                if(tmp.barycentre.x > 0)
                    ret.push_back(tmp);
                break;
            default:
                std::cout << "erreur" << std::endl;
                break;
        }
    }
    return ret;
}

int Terrain::findTriangle(const Vector &vec) {
    int ret = -1;
    float distanceMin = 99999;
    int cpt = 0;

    vector<Barycentre> barycentres_;

    if(vec.x <= 0.010283)
        barycentres_ = barycentres[0];
    else
        barycentres_ = barycentres[1];

    for(Barycentre barycentre : barycentres_){
        cpt = barycentre.id;
        if(barycentre.barycentre.z < 0) {
            continue;
        }
        else {
            float xMax = -999;
            float yMax = -999;
            float xMin = 999;
            float yMin = 999;
            float tmp;
            tmp = fmaxf(mesh.triangle(cpt).a.x, mesh.triangle(cpt).b.x);
            xMax = fmaxf(tmp, mesh.triangle(cpt).c.x);

            tmp = fminf(mesh.triangle(cpt).a.x, mesh.triangle(cpt).b.x);
            xMin = fminf(tmp, mesh.triangle(cpt).c.x);

            tmp = fmaxf(mesh.triangle(cpt).a.y, mesh.triangle(cpt).b.y);
            yMax = fmaxf(tmp, mesh.triangle(cpt).c.y);

            tmp = fminf(mesh.triangle(cpt).a.y, mesh.triangle(cpt).b.y);
            yMin = fminf(tmp, mesh.triangle(cpt).c.y);


            if (distance(Point(vec), Point(barycentre.barycentre)) <= distanceMin && vec.x && vec.x >= xMin && vec.x <= xMax && vec.y >= yMin && vec.y <= yMax) {
                distanceMin = distance(Point(vec), Point(barycentre.barycentre));
                ret = cpt;
            }
        }
    }
    return ret;
}

Terrain::Terrain(std::string filename, std::string textureName, const Transform& trans) {
    texture_ = read_texture(0, textureName.data());
    mesh = read_mesh(filename.data());
    transform = trans;

    this->barycentres.push_back(calculeBarycentre(mesh, 0));
    this->barycentres.push_back(calculeBarycentre(mesh, 1));
}

Terrain::Terrain(HeightMap& hMap, const Transform& trans) {
    mesh = hMap.mesh;
    transform = trans;
    this->hMap = hMap.map;

    this->barycentres.push_back(calculeBarycentre(mesh, 0));
    this->barycentres.push_back(calculeBarycentre(mesh, 1));
}

Terrain::Terrain(Terrain& ter) {
    mesh = ter.getMesh();
    this->hMap = ter.hMap;
}

float Terrain::getHeight(const Vector &pos, int idTri) {

    if(idTri > 0 && idTri < mesh.triangle_count()) {
        TriangleData triangles = mesh.triangle(idTri);

        float zMin;
        float zMax;
        float yMin;
        float yMax;
        float tmp;
        float ret;

        tmp = fmaxf(triangles.a.z, triangles.b.z);
        zMax = fmaxf(tmp, triangles.c.z);
        tmp = fminf(triangles.a.z, triangles.b.z);
        zMin = fminf(tmp, triangles.c.z);

        tmp = fmaxf(triangles.a.y, triangles.b.y);
        yMax = fmaxf(tmp, triangles.c.y);
        tmp = fminf(triangles.a.y, triangles.b.y);
        yMin = fminf(tmp, triangles.c.y);

        ret = (pos.y - yMin) / (yMax - yMin);

        ret = ret * zMax + (1-ret) * zMin;
        return ret;
    }
    else
        return -100;
}

Vector Terrain::getNormal(int idTri) {

    if(idTri > 0 && idTri < mesh.triangle_count()) {
        TriangleData triangle = mesh.triangle(idTri);
        Vector tmp = normalize(cross(Vector(triangle.b - triangle.a), Vector(triangle.c - triangle.a)));
        if (__isnanf(tmp.x) || __isnanf(tmp.y) || __isnanf(tmp.z))
            return Vector(0, 0, 1);
        if(tmp.z < 0.5)
            return Vector(0,0,1);
        return tmp;
    }else
        return Vector(0,0,1);
}