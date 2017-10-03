#include "HeightMap.h"
#include "ReadPicture.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

HeightMap::HeightMap() {
    mesh = Mesh(GL_TRIANGLES);
}

Mesh HeightMap::genCookieCutter(int height, int width) {
    this->height = height;
    this->width = width;
    int cptX = 0;
    int cptY = 0;
    int cptZ = 0;

    ReadPicture hm("data/test2.txt");
    int* data = hm.getData();

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Point p;
            p.x = i * 5;
            p.y = j * 5;
            p.z = (float) (data[j + i * width] % 50);
            map.push_back(p);
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Vector normal;
//            std::cout << Vector(map[i*width + (j+1)]) << Vector(map[(i+1)*width + j]) << std::endl;
//            std::cout << cross(Vector(0, -1, data[j + (i+1) * width]), Vector(1, 0, data[(j+1) + i * width])) << std::endl;

            Vector vec1;
            Vector vec2;
            Vector vecBase = Vector(map[i * width + j])/5;
            if(i < height - 1 && j < width -1) {
                vec1 = Vector(map[i * width + (j + 1)]) / 5 - vecBase;
                vec2 = Vector(map[(i + 1) * width + j]) / 5 - vecBase;
                normal = cross(vec2, vec1);
            }
            else{
                vec1 = Vector(map[i * width + (j - 1)]) / 5 - vecBase;
                vec2 = Vector(map[(i-1) * width + j]) / 5 - vecBase;
                normal = cross(vec2, vec1);
            }
//            std:: cout << vec1 << " " << vec2 << std::endl;
            if(i < height - 1 && j < width - 1)
                normal = cross(Vector(0, -1, data[j + (i+1) * width]!=0?1:0), Vector(1, 0, data[(j+1) + i * width]!=0?1:0));
            else if(i == height - 1 && j == width -1)
                normal = cross(Vector(0, -1, 0), Vector(1, 0, 0));
            else if(i == height - 1)
                normal = cross(Vector(0, -1, 0), Vector(1, 0, 0));
            else if(j == height - 1)
                normal = cross(Vector(0, -1, 0), Vector(1, 0, 0));
            else {
                std::cout << "erreur" << std::endl;
                normal = Vector(0, 0, 1);
            }
            normals.push_back(normal);
        }
    }

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << normals[j + i * width];
        }
        std:: cout << std::endl;
    }

    vector<int> indices;
    
    for(int i = 0; i < (width-1); i++){
        cptY = 0 ;
        cptZ = 0;
        for(int j = 0; j < (height-1); j++){
            cptX = 0;
            cptZ++;
            for(int k = 0; k < 2; k++){
                //j * width + cptX + i //x
                //width * cptY + i + 1 //y
                //width * cptZ + i // z
                indices.push_back(j * width + cptX + i);
                indices.push_back(width * cptZ + i); 
                indices.push_back(width * cptY + i + 1);
                
                cptX++;
                if(k == 0)
                    cptY++;
            }
        }
        cptY++;
    }
    
    for(int i = 0; i < indices.size(); i++){
        mesh.vertex(map[indices[i]].x, map[indices[i]].y, map[indices[i]].z);
    }

    return mesh;
}
