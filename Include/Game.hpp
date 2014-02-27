#ifndef GAME_HPP
#define GAME_HPP

#include "Entity.hpp"

#include <map>
#include <string>
#include <memory>

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

    void run();

private:
    void createEntities();

private:
    std::map<std::string, std::unique_ptr<Entity>> m_Entities;
};

#endif // GAME_HPP
