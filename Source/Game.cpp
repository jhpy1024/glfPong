#include "Game.hpp"
#include "Paddle.hpp"

#include <GL/gl.h>

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

}

void Game::specialKeyReleased(int key, int x, int y)
{

}

void Game::mousePressed(int button, int state, int x, int y)
{

}
