#include <texture.h>
#include "app.h"
#include "Scene.h"

class Play : public App{
  public:
    // constructeur : donner les dimensions de l'image, et eventuellement la version d'openGL.
    Play( ) :
            App(1024, 640)
    {}

    int init( )
    {

        Mesh obs = read_mesh("data/Barriere.obj");
        GLuint tex = read_texture(0, "data/TextureBarriere.png");

        CheckPoints cp("data/CheckPoints");

        map = new Terrain("data/Map.obj", "data/TextureFinal.png", Translation(0,0,0));
        p1 = new Player(Translation(0.75, -56.33, 0.2), 0, *map);
        p2 = new Player(Translation(0.75, -54.33, 0.2), 1, *map);

        Obstacle* tmp;
        for(int i = 0; i < 3; i++) {
            tmp = new Obstacle(obs, tex, Translation(11.8, 1.5 + (i*4), 7.5) * RotationX(90) * RotationY(90));
            obstacles.push_back(tmp);
        }
        for(int i = 0; i < 6; i++){
            tmp = new Obstacle(obs, tex, Translation(11.1 - (4 * i),11.4,7.5) * RotationX(90));
            obstacles.push_back(tmp);
        }
        for(int i = 0; i < 3; i++) {
            tmp = new Obstacle(obs, tex, Translation(-11.8, 1.5 + (i*4), 7.5) * RotationX(90) * RotationY(90));
            obstacles.push_back(tmp);
        }


        scene.addPlayer(p1);
        scene.addPlayer(p2);
        scene.addTerrain(map);
        for(int i = 0; i < obstacles.size(); i++)
            scene.addObstacle(obstacles[i]);

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre

        glClearDepth(1.f);                          // profondeur par defaut
        glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
        glEnable(GL_DEPTH_TEST);                    // activer le ztest

        return 0;   // ras, pas d'erreur
    }

    // destruction des objets de l'application
    int quit( ){
        delete(p1);
        delete(p2);
        delete(map);
		for(int i = 0; i < obstacles.size(); i++)
			delete(obstacles[i]);
        return 0;
    }

    int render( ){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.update();
        scene.render();
        return 1;
    }

  protected:

    Player* p1;
    Player* p2;
    Terrain* map;
    std::vector<Obstacle*> obstacles;
    Scene scene;
};

int main( int argc, char **argv ){
    Play app;
    app.run();
    return 0;
}
