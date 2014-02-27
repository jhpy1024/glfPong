#ifndef GAME_HPP
#define GAME_HPP

class Game
{
public:
    Game();

    // == Input callbacks ==
    void keyPressed(unsigned char key, int x, int y);
    void specialKeyPressed(int key, int x, int y);
    void specialKeyReleased(int key, int x, int y);
    void mousePressed(int button, int state, int x, int y);

    void update(int delta);
    void render();
};

#endif // GAME_HPP
