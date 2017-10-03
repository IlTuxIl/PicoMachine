//
// Created by julien on 06/04/17.
//

#include "Player.h"

Player::Player(Transform transform, int id, Terrain& ter) : col(vec2(transform(Point(0,0,0)).x,transform(Point(0,0,0)).y), 0.65, 1.2, -3.14), terrain(ter){
    this->terrain = ter;
    mesh = read_mesh("data/mmachine.obj");
    this->transform = transform;
    type = GOTPlayer;
    this->id = id;
    if(id == 0){
        controller = new KeyboardController(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
        mesh.default_color(Color(1.0f, 0.f, 0.f));
    }
    else{
        controller = new KeyboardController('z', 's', 'q', 'd');
        mesh.default_color(Color(0.0f, 0.f, 1.f));
    }

    forward_ = true;
    switchable_ = true;
    active_ = true;
    speed_ = Vector(0.f, 0.f, 0.f);
    last_time_ = 0;
    position_ = transform(Point(0,0,0));
    direction_ = Vector(1.f, 0.f, 0.f);
    normal_ = Vector(0.f, 0.f, 0.f);
    //useful parameters to control the movement behavior
    acceleration_ = 0.0005f;
    turning_angle_ = 3.f;
    friction_ = vec2(0.02f, 0.1f);
    fallSpeed_ = 0.05f;
    isFalling_ = false;
}

void Player::reset(const Point &p) {
    position_ = p;
    isFalling_ = false;
    speed_ = Vector(0,0,0);
    transform = Transform(direction_, cross(normal_, direction_), normal_, position_ - Point());
}

void Player::setDirection(const Vector &dir) {
    direction_ = dir;
}

void Player::deplacement(){
    if(!active_) return ;

    //handle friction
    Vector linear = dot(speed_, direction_)*direction_ ;
    Vector lateral = speed_ - linear ;
    speed_ = speed_ - friction_.x * linear ;
    speed_ = speed_ - friction_.y * lateral ;

    //backward or forward
    if(forward_) {
        //handle accelerations
        if(controller->up()) {
            speed_ = speed_ + direction_ * acceleration_ ;
        }

        if(controller->down()) {
            speed_ = speed_ - direction_ * acceleration_ ;
            if(dot(speed_, direction_) < 0) {
                speed_ = Vector(0.f, 0.f, 0.f) ;
            }
        }

        //handle rotation
        if(controller->left()) {
            direction_ = Rotation(normal_, turning_angle_)(direction_) ;
        }
        if(controller->right()) {
            direction_ = Rotation(normal_, -turning_angle_)(direction_) ;
        }
    } else /*if(!isFalling_)*/{
        //handle accelerations
        if(controller->up()) {
            speed_ = speed_ + direction_ * acceleration_ ;
            if(dot(speed_, direction_) > 0) {
                speed_ = Vector(0.f, 0.f, 0.f) ;
            }
        }

        if(controller->down()) {
            speed_ = speed_ - direction_ * acceleration_ ;
        }

        //handle rotation
        if(controller->left()) {
            direction_ = Rotation(normal_, -turning_angle_)(direction_) ;
        }
        if(controller->right()) {
            direction_ = Rotation(normal_, turning_angle_)(direction_) ;
        }
    }

    //handle the switch breaking // moving backwards
    //control needs to be released then pushed again
    if(length(speed_) == 0.f) {
        if(switchable_) {
            if(controller->down()) {
                forward_ = false ;
            }
            if(controller->up()) {
                forward_ = true ;
            }
        }
    }

    switchable_ = !(
            controller->up()
            || controller->down()
            || controller->left()
            || controller->right()
    ) ;

    //compute new position position
    int time = SDL_GetTicks() ;

    //if(collision() == 1){
    //speed_ = -speed_;
    //}

    Point new_position = position_ + (time - last_time_) * speed_ ;

    //project
    //project(new_position) ;

    //update speed taking projection into account
    speed_ = (new_position - position_) / (time - last_time_) ;
    speed_ = speed_ - dot(speed_, normal_)*normal_ ;

    //update the position
    position_ = new_position ;

    //update time
    last_time_ = time ;

    Point posTerrain;
    int idTri;
    float posZ;
    project(posTerrain, idTri);


    posZ = terrain.getHeight(Vector(posTerrain), idTri);

    if(posZ <= 0 || isFalling_){
        speed_.z = speed_.z - fallSpeed_;
        isFalling_ = true;
    }
    else if(posZ >= position_.z){
        position_.z = posZ;
    }

    normal_ = terrain.getNormal(idTri);
    direction_ = normalize(direction_ - dot(direction_, normal_)*normal_) ;

    transform = Transform(direction_, cross(normal_, direction_), normal_, position_ - Point());
    float angle = -atan2(direction_.x, direction_.y);
    col.move(vec2(position_.x, position_.y), angle);
}

void Player::update(std::vector<Player*>& vec, std::vector<Obstacle*> &obs) {
    deplacement();
    collisionPlayer(vec);
    collisionObs(obs);
}

void Player::collisionPlayer(std::vector<Player*> &vec) {
    if(id == 0){

        Player* other = dynamic_cast<Player*>(vec[1]);
        if(col.overlaps(other->col)){
            Transform tOther = other->getTransform();
            speed_ = (Vector(position_, tOther(Point(0,0,0))) * distance(position_, tOther(Point(0,0,0)))) / -300;
            speed_.z = 0;
        }
    }

    if(id == 1){
        Player* other = dynamic_cast<Player*>(vec[0]);
        if(col.overlaps(other->col)){
            Transform tOther = other->getTransform();
            speed_ = (Vector(position_, tOther(Point(0,0,0))) * distance(position_, tOther(Point(0,0,0)))) / -300;
            speed_.z = 0;
        }
    }
}

void Player::collisionObs(std::vector<Obstacle*> &vec) {
    for(Obstacle* o : vec){
        if(o->collide(col)){
            Transform tOther = o->getTransform();
            speed_ = (Vector(position_, tOther(Point(0,0,0))) * distance(position_, tOther(Point(0,0,0)))) / -1000;
            speed_.z = 0;
        }
    }
}

void Player::project(Point& pos, int& idTri){
    Transform VTT = terrain.getTransform().inverse() * transform;
    pos = VTT(Point(0,0,0));
    idTri = terrain.findTriangle(Vector(pos));
}