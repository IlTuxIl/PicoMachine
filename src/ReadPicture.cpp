
#include "ReadPicture.h"
#include "fstream"
#define WIDTH 256
#define HEIGHT 256

using namespace std;


ReadPicture::ReadPicture(const char* fileName){

    imageData = new int [HEIGHT * WIDTH]; // create new array size: height of image.
    ifstream file(fileName, ios::in);
    //image I/O
    int tmp;

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            file >> tmp;
            imageData[j + i * WIDTH] = tmp;
        }

    }

    file.close(); //close stream.

}

ReadPicture::~ReadPicture(){
    delete imageData;
}

int* ReadPicture::getData(){
    return imageData;
}