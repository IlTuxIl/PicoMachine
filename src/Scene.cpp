//
// Created by julien on 06/04/17.
//

#include "Scene.h"

Scene::Scene() : checkPoints("data/CheckPoints"){
    players = std::vector<Player*>();
    obstacles = std::vector<Obstacle*>();
    lastPoint = 0;
    nextPoint = 1;
    nbCheckPoints = checkPoints.nbCheckPoint();
    fin = false;
    scoreP1 = 4;
    scoreP2 = 4;
    flag = false;
}

Scene::~Scene() {
    players.clear();
    obstacles.clear();
}

void Scene::addObstacle(Obstacle* newObject) {
    obstacles.push_back(newObject);
}

void Scene::addPlayer(Player* newObject) {
    players.push_back(newObject);
}

void Scene::addTerrain(Terrain *newTerrain){
    terrain = newTerrain;
}

void Scene::update() {
    if(fin){
        /**
         * SDL_GetTicks() provoque une erreur sous valgrind (Conditional jump or move depends on uninitialised value(s))
         * lors du 1er passage dans la boucle
         */
        if(SDL_GetTicks() > timeFin + 1000 && flag) {

            if(winner == 0){
                scoreP1 ++;
                scoreP2 --;
            }
            else{
                scoreP1 --;
                scoreP2 ++;
            }
            if (scoreP1 == 0 || scoreP2 == 0){
                lastPoint = 0;
                scoreP1 = 4;
                scoreP2 = 4;

                if(winner == 0)
                    std::cout << "Rouge gagne !" << std::endl;
                else
                    std::cout << "Bleu gagne !" << std::endl;

            }
            Point cp = checkPoints.getCheckPoint(lastPoint);
            float angle = checkPoints.getAngle(lastPoint);
//            std::cout << lastPoint << " " << cp << " " << angle << std::endl;

            Point p1, p2;

            if(angle == 180 || angle == 0) {
                p1 = Point (0, -1, 0);
                p2 = Point(0, 1, 0);
            }
            else{
                p1 = Point(-1, 0, 0);
                p2 = Point(1, 0, 0);
            }

            players[0]->reset(cp + p1);
            players[0]->setDirection(RotationZ(angle)(Vector(1,0,0)));
            players[1]->reset(cp + p2/*(players[0]->getTransform() * Translation(0,2,0))(Point(0,0,0))*/);
            players[1]->setDirection(RotationZ(angle)(Vector(1,0,0)));
            fin = false;

            displayScore();
        }
    }
    else {
        for (int i = 0; i < players.size(); i++) {

            players[i]->update(players, obstacles);
            Transform model = players[i]->getTransform();
            Transform view = camera.view();
            Transform projection = camera.projection(1024, 640, 45);

            Transform mvp = projection * view * model;
            Point p = mvp(Point(0, 0, 0));

            Transform mTerrain = terrain->getTransform();
            Transform projPlayerTerrain = mTerrain.inverse() * players[i]->getTransform();

            //CheckPoints
            int curCheckPoint = checkPoints.collideWith(projPlayerTerrain(Point(0,0,0)));
            if (curCheckPoint == nextPoint) {
                lastPoint = curCheckPoint;
                nextPoint++;
                if(nextPoint == nbCheckPoints)
                    nextPoint = 0;
                enTete = i;
            }
            //Detection sortie camera
            if ((p.x > 1 || p.x < -1 || p.y > 1 || p.y < -1) && SDL_GetTicks() > 2000){
                timeFin = SDL_GetTicks();
                fin = true;
                winner = enTete;
                flag = true;
            }
            //Detection sortie terrain
            if(model(Point(0, 0, 0)).z < -25){
                timeFin = SDL_GetTicks();
                if(i == 0)
                    winner = 1;
                else
                    winner = 0;
                fin = true;
                flag = true;
            }
        }
    }
}

void Scene::render() {

    Transform j1 = players[0]->getTransform();
    Transform j2 = players[1]->getTransform();

    Point med = center(j1(Point(0,0,0)), j2(Point(0,0,0)));

    med.z = fmaxf((j1(Point(0,0,0))).z, (j2(Point(0,0,0))).z);

    if(!fin)
        camera.lookat(med, 20);
    else{
        med = players[winner]->getTransform()(Point(0,0,0));
        camera.lookat(med, 20);
    }
    for(int i = 0; i < players.size(); i++) {
        vector<Point> vec;
        vector<Vector> vecDir;
        if(i == 0){
            vec.push_back(j2(Point(0,0,0)));
            vecDir.push_back(j2(Vector(1,0,0)));
        }
        else{
            vec.push_back(j1(Point(0,0,0)));
            vecDir.push_back(j1(Vector(1,0,0)));
        }
        players[i]->getMesh().drawPlayer(players[i]->getTransform(), camera.view(), camera.projection(1024, 640, 45), true, 0, vec, vecDir);
    }
    vector<Point> vec;
    vector<Vector> vecDir;
    vec.push_back(j1(Point(0,0,0)));
    vec.push_back(j2(Point(0,0,0)));
    vecDir.push_back(j1(Vector(1,0,0)));
    vecDir.push_back(j2(Vector(1,0,0)));
    terrain->getMesh().drawTerrain(terrain->getTransform(), camera.view(), camera.projection(1024, 640, 45), true, terrain->getTexture(), vec, vecDir);
    for(int i = 0; i < obstacles.size(); i++){
        obstacles[i]->getMesh().drawObstacle(obstacles[i]->getTransform(), camera.view(), camera.projection(1024, 640, 45), true, obstacles[i]->getTexture(), vec, vecDir);
//        draw(obstacles[i]->collider.getMesh(), Translation(0,0,8), camera);
    }
}

void Scene::setCamera(Orbiter camera){
    this->camera = camera;
}

void Scene::displayScore() {
    std::cout << "Rouge : " << scoreP1 << " Bleu : " << scoreP2 << std::endl;
}
