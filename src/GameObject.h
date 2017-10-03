//
// Created by julien on 06/04/17.
//

#ifndef PICOMACHINE_GAMEOBJECT_H
#define PICOMACHINE_GAMEOBJECT_H

#include <orbiter.h>
#include "mesh.h"
#include "wavefront.h"
#include "draw.h"

enum GOType{
    GOTPlayer,
    GOTObstacle,
    GOTTerrain
};

/**
 * La class GameObject permet de gérer tous les types d'objets d'une scène : les joueurs, les obstacles et la map
 */
class GameObject {

public:
    GameObject(){};
    GameObject(std::string filename, Transform transform);
    GameObject(Mesh& mesh, Transform transform);
    virtual void update(std::vector<GameObject*>& vec);
    Mesh& getMesh();
    GLuint& getTexture();
    Transform& getTransform();
    GOType getType();

protected:
    Mesh mesh;
    GLuint texture_;
    Transform transform;
    GOType type;
};


#endif //PICOMACHINE_GAMEOBJECT_H
