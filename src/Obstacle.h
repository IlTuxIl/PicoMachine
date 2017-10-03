//
// Created by julien on 28/05/17.
//

#ifndef PICOMACHINE_OBSTACLE_H
#define PICOMACHINE_OBSTACLE_H


#include "GameObject.h"
#include "OBB2D.h"

/**
 * La classe Obstacle permet de gérer les obstacles.
 * Les obstacles génèrent leurs colliders à partir du Mesh
 */
class Obstacle : public GameObject{
public:
    Obstacle(std::string filename, std::string texturename, const Transform& transform);
    Obstacle(Mesh& mesh_, GLuint& texture, const Transform& transform);
    /**
     * La fonction collide utilise des OBB car ils sont nécessaire aux joueurs et déjà implémenté
     * @param pos : La position d'un joueur
     * @return true si collision, false sinon
     */
    bool collide(const OBB2D& pos);

private:
    /**
     * La fonction init permet de générer un OBB à partir du mesh
     */
    void init();
    OBB2D collider;
};

#endif //PICOMACHINE_OBSTACLE_H
