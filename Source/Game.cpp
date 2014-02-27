#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>

Game::Game()
{

}

void Game::checkCollisions()
{
    auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
    auto ballPtr = static_cast<Ball*>(m_Entities["Ball"].get());

    float ballLeft = ballPtr->getX() - (ballPtr->getWidth());
    float ballTop = ballPtr->getY() - (ballPtr->getHeight());
    float ballBottom = ballTop + ballPtr->getHeight();
    float ballRight = ballLeft + ballPtr->getWidth();

    float paddleLeft = paddlePtr->getX();
    float paddleTop = paddlePtr->getY();
    float paddleBottom = paddleTop + paddlePtr->getHeight();
    float paddleRight = paddleLeft + paddlePtr->getWidth();

    bool intersecting = false;

    if (paddleRight < ballLeft ||
        paddleBottom < ballTop ||
        paddleLeft > ballRight ||
        paddleTop > paddleBottom)
    {
        intersecting = false;
    }
    else
    {
        intersecting = true;
    }

    if (intersecting)
        ballPtr->hitPaddle();
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

    renderText(320.f, 240.f, "Hello, World!", 1.f, 0.f, 1.f);
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
