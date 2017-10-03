//
// Created by julien on 06/04/17.
//

#ifndef PICOMACHINE_PLAYER_H
#define PICOMACHINE_PLAYER_H


#include "GameObject.h"
#include "controller.hpp"
#include "OBB2D.h"
#include "Terrain.h"
#include "Obstacle.h"

/**
 * La classe Player permet de gérer les joueurs.
 * La fonction update gère la vitesse et les collisions
 * A chaque instant, la class Player se projete sur le terrain pour récupérer la normal et la hauteur
 * du triangle de lequel se trouve le joueur.
 */
class Player : public GameObject {
public:
    Player(Transform transform, int id, Terrain& terrain);
    /**
     * Déplace le joueur et gére les collisions
     * @param vec : la liste des joueurs pour les collisions
     * @param obs : la liste des obstacles pour les collisions
     */
    virtual void update(std::vector<Player*> &vec, std::vector<Obstacle*> &obs);
    /**
     * Respawn le joueur au point P
     */
    void reset(const Point& p);
    /**
     * Set la direction après respawn
     * @param dir
     */
    void setDirection(const Vector& dir );

    OBB2D col;
private:
    /**
     * Projection du joueur sur le terrain
     * @param OUT pos : La position du joueur sur le terrain
     * @param OUT idTri : Le triangle sur lequel le joueur se trouve
     */
    void project(Point& pos, int& idTri);
    void deplacement();
    void collisionPlayer(std::vector<Player*> &vec);
    void collisionObs(std::vector<Obstacle*> &vec);

    const Controller* controller;
    Terrain terrain;

    //physics
    bool active_ ;
    Vector speed_ ;
    int last_time_ ;
    void step() ;
    //elements

    Point position_ ;
    Vector direction_ ;
    Vector normal_ ;

    //parameters
    float fallSpeed_;
    float acceleration_ ;
    float turning_angle_ ;
    vec2 friction_ ;

    bool forward_ ;
    bool switchable_ ;
    int id;
    bool isFalling_;
};

#endif //PICOMACHINE_PLAYER_H
