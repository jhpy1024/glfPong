#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

#include <GL/gl.h>
#include <GL/glut.h>

Game::Game()
{

}

void Game::update(int delta)
{
    for (auto& entity : m_Entities)
        entity.second->update(delta);
}

void Game::render()
{
    for (auto& entity : m_Entities)
        entity.second->render();
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
