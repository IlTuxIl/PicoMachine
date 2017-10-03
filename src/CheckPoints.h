//
// Created by julien on 23/05/17.
//

#ifndef PICOMACHINE_CHECKPOINTS_H
#define PICOMACHINE_CHECKPOINTS_H


#include <vec.h>
#include <vector>
/**
 * La class CheckPoints récupère un fichier texte qui contient toutes les positions des checkpoints ainsi
 * que l'angle de réapparition des joueurs
 */
class CheckPoints {
public:
    CheckPoints(std::string filename);
    /**
     * @param player : La position d'un joueur
     * @return l'indice du checkPoint en collision avec le joueur ou -1
     */
    int collideWith(const Point& player);
    Point& getCheckPoint(int i);
    int nbCheckPoint();
    float& getAngle(int i);
private:
    std::vector<Point> coord_;
    std::vector<float> angles_;
};


#endif //PICOMACHINE_CHECKPOINTS_H
