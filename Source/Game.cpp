#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Utils.hpp"

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>

Game::Game()
    : m_Lives(3)
    , m_Score(0)
{

}

void Game::paddleBallCollisions(Paddle* paddle, Ball* ball)
{
    float ballLeft = ball->getX() - ball->getWidth();
    float ballTop = ball->getY() - ball->getHeight();
    float ballBottom = ballTop + ball->getHeight();
    float ballRight = ballLeft + ball->getWidth();

    float paddleLeft = paddle->getX();
    float paddleTop = paddle->getY();
    float paddleBottom = paddleTop + paddle->getHeight();
    float paddleRight = paddleLeft + paddle->getWidth();

    bool intersecting = false;

    if (paddleRight < ballLeft ||
        paddleBottom < ballTop ||
        paddleLeft > ballRight ||
        paddleTop > ballBottom)
    {
        intersecting = false;
    }
    else
    {
        intersecting = true;
    }

    if (intersecting)
    {
        ball->hitPaddle();
        ++m_Score;
    }
}

void Game::checkCollisions()
{
    auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
    auto ballPtr = static_cast<Ball*>(m_Entities["Ball"].get());

    paddleBallCollisions(paddlePtr, ballPtr);
}

void Game::update(int delta)
{
    for (auto& entity : m_Entities)
        entity.second->update(delta);

    checkCollisions();
}

void Game::render()
{
    for (auto& entity : m_Entities)
        entity.second->render();

    renderText(320.f, 20.f, "Score: " + util::toString(m_Score), 0.f, 1.f, 1.f);
    renderText(320.f, 40.f, "Lives: " + util::toString(m_Lives), 0.f, 1.f, 1.f);
}

void Game::createEntities()
{
    m_Entities["Paddle"] = std::unique_ptr<Paddle>(new Paddle(10.f, 10.f, 15.f, 150.f));
    m_Entities["Ball"] = std::unique_ptr<Ball>(new Ball(320.f, 240.f, 10.f));
}

void Game::run()
{
    createEntities();
}

// == Input callbacks ==
void Game::keyPressed(unsigned char key, int x, int y)
{

}

void Game::specialKeyPressed(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    {
        auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
        paddlePtr->moveUp();
    }
    break;
    case GLUT_KEY_DOWN:
    {
        auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
        paddlePtr->moveDown();
    }
    break;
    default:
        break;
    }
}

void Game::specialKeyReleased(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
    {
        auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
        paddlePtr->stopMoving();
    }
    break;
    default:
        break;
    }
}

void Game::mousePressed(int button, int state, int x, int y)
{

}

// (x, y) = center of text
void Game::renderText(float x, float y, const std::string& text, float r, float g, float b)
{
    void* font = GLUT_BITMAP_HELVETICA_18;

    glColor3f(r, g, b);
    glRasterPos2f(x - (glutBitmapLength(font, (const unsigned char*) text.c_str())) / 2.f, y + glutBitmapHeight(font) / 2.f);

    glutBitmapString(font, (const unsigned char*) text.c_str());
}
