//
// Created by julien on 08/04/17.
//

#ifndef PICOMACHINE_TERRAIN_H
#define PICOMACHINE_TERRAIN_H


#include "GameObject.h"
#include "HeightMap.h"

struct Barycentre{
    int id;
    Vector barycentre;
};

/**
 * La class Terrain permet de gérer la map
 * Pendant l'initialisation, la class Terrain calcul les normales de chaque triangles qui la compose
 * Puis les stocks dans 2 tableaux (pour diviser le temps de recherche par 2)
 */
class Terrain : public GameObject{
public:
    Terrain(HeightMap& hMap, const Transform& trans);
    Terrain(std::string filename, std::string textureName, const Transform& trans);
    Terrain(Terrain& ter);

    /**
     * @param vec : La position du joueur sur le terrain
     * @return L'id du triangle sur lequel est positionné le joueur
     */
    int findTriangle(const Vector& vec);

    /**
     * @param pos : la position du joueur sur le terrain
     * @param idTri : l'id du triangle du joueur
     * @return La hauteur du joueur
     */
    float getHeight(const Vector& pos, int idTri);
    /**
     * @param pos : La position du joueur sur le terrain
     * @param idTri : l'id du triangle du joueur
     * @return La normale du triangle
     */
    Vector getNormal(int idTri);
private:

    std::vector<std::vector<Barycentre>> barycentres;
    std::vector<Point> hMap;
};

#endif //PICOMACHINE_TERRAIN_H
