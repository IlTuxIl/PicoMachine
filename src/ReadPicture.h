//
// Created by julien on 06/04/17.
//

#ifndef PICOMACHINE_READPICTURE_H
#define PICOMACHINE_READPICTURE_H

#include <fstream>
/**
 * Class obsolète
 * La class ReadPicture est nécessaire à HeightMap pour récupérer les données
 */
class ReadPicture {
public:
    ReadPicture(const char* fileName); //Constructor
    ~ReadPicture(); //Deconstructor
    int* getData();
private:
    int* imageData;
};

#endif //PICOMACHINE_READPICTURE_H
