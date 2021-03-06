#include <iostream>
#include <ctime>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include "Game.hpp"

int oldTimeSinceStart = 0;

Game game;

void keyPressed(unsigned char key, int x, int y)
{
    game.keyPressed(key, x, y);
}

void specialKeyPressed(int key, int x, int y)
{
    game.specialKeyPressed(key, x, y);
}

void specialKeyReleased(int key, int x, int y)
{
    game.specialKeyReleased(key, x, y);
}

void mousePressed(int button, int state, int x, int y)
{
    game.mousePressed(button, state, x, y);
}

void update(int delta)
{
    game.update(delta);
}

void render()
{
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;

    update(delta);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    game.render();

    glutSwapBuffers();
}

void createWindow()
{
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("glfPong");
}

void initGlew()
{
    auto status = glewInit();
    if (status != GLEW_OK)
        std::cerr << glewGetErrorString(status) << std::endl;
}

void setupCallbacks()
{
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    glutSpecialUpFunc(&specialKeyReleased);
    glutMouseFunc(&mousePressed);
    glutSpecialFunc(&specialKeyPressed);
    glutSpecialUpFunc(&specialKeyReleased);
    glutDisplayFunc(&render);
    glutIdleFunc(&render);
}

void setupGL()
{
    // Top left = (0, 0)
    gluOrtho2D(0, 640, 480, 0);

    glDisable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_POINT_SMOOTH);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);

    createWindow();
    initGlew();
    setupCallbacks();
    setupGL();

    game.run();
    glutMainLoop();

    return 0;
}
