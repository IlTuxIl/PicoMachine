//
// Created by julien on 06/04/17.
//

#include "GameObject.h"

GameObject::GameObject(std::string filename, Transform transform) {
    mesh = read_mesh(filename.data());
    this->transform = transform;
    type = GOTTerrain;
}

GameObject::GameObject(Mesh& m, Transform transform) {
    mesh = m;
    this->transform = transform;
    type = GOTTerrain;
}

void GameObject::update(std::vector<GameObject*> &vec) {

}

GLuint& GameObject::getTexture() {
    return texture_;
}

Mesh& GameObject::getMesh() {
    return mesh;
}

Transform& GameObject::getTransform() {
    return transform;
}

GOType GameObject::getType() {
    return type;
}