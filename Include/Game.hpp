#ifndef GAME_HPP
#define GAME_HPP

#include "Entity.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

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
    // =====================

    void update(int delta);
    void render();
    void renderGameOver();

    void run();

private:
    void createEntities();

    // == Collision detection ==
    void checkCollisions();
    void paddleBallCollisions(Paddle* paddle, Ball* ball);
    void ballWallCollisions(Ball* ball);
    // =========================

    void renderText(float x, float y, const std::string& text, float r, float g, float b);
    void renderLivesText();

    void resetGame();

private:
    std::map<std::string, std::unique_ptr<Entity>> m_Entities;

    unsigned m_Lives;
    unsigned m_Score;

    bool m_GameOver;
};

#endif // GAME_HPP
