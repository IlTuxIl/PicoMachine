#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include <vector>
#include "mesh.h"

using std::vector;

/**
 * Non utilisé !
 * La classe HeightMap permet de générer un Mesh à partir d'un fichier texte
 */
class HeightMap{
    
  public:
    HeightMap();
    Mesh getMesh();
    Mesh genCookieCutter(int height, int width);

    int height;
    int width;
    Mesh mesh;
    vector<Point> map;
    vector<Vector> normals;
};

#endif
