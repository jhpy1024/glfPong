#include <iostream>

#include <GL/glut.h>

int oldTimeSinceStart = 0;

void handleInput(unsigned char key, int x, int y)
{

}

void update(int delta)
{

}

void render()
{
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;

    update(delta);

    glClearColor(1.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Test");
    glutKeyboardFunc(&handleInput);
    glutDisplayFunc(&render);
    glutIdleFunc(&render);
    glutMainLoop();

    return 0;
}
