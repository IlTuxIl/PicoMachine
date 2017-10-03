//
// Created by julien on 06/04/17.
//

#ifndef PICOMACHINE_SCENE_H
#define PICOMACHINE_SCENE_H

#include "GameObject.h"
#include "Player.h"
#include "Terrain.h"
#include "CheckPoints.h"
#include "Obstacle.h"
#include <vector>
#include <orbiter.h>

/**
 * La class Scene permet de gérer tous les GameObjects de la scene (fonction update et render)
 * De plus la class Scene gére la logique de jeu (score, sortie de la caméra, chute, ...)
 */

class Scene {

public:
    Scene();
    ~Scene();
    void addObstacle(Obstacle* newObject);
    void addPlayer(Player* newPlayer);
    void addTerrain(Terrain* newTerrain);


    /**
     * La fonction update gére la logique de jeu puis appel les fonctions update de tous les GameObjects.
     */
    void update();
    /**
     * La fonction render gére l'affichage de tous les GameObjects via
     * 2 shaders : terrain.glsl et player.glsl
     */
    void render();
    void setCamera(Orbiter camera);
private:

    std::vector<Player*> players;
    Terrain* terrain;
    std::vector<Obstacle*> obstacles;
    Orbiter camera;
    bool fin;
    int winner;
    float timeFin;
    CheckPoints checkPoints;
    int lastPoint;
    int nextPoint;
    int nbCheckPoints;
    int enTete;
    int scoreP1, scoreP2;
    bool flag;
    void displayScore();

};

#endif //PICOMACHINE_SCENE_H
