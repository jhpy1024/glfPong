#include <iostream>

#include <GL/glut.h>

void handleInput(unsigned char key, int x, int y)
{

}

void render()
{
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
    glutMainLoop();

    return 0;
}
