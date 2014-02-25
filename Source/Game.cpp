#include "Game.hpp"

#include <GL/glu.h>

#include <iostream>

Game::Game(unsigned width, unsigned height, const std::string& title)
    : WIDTH(width)
    , HEIGHT(height)
    , TITLE(title)
{

}

void Game::handleInput()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_Window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update()
{

}

void Game::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Window.display();
}

void Game::run()
{
    createWindow();
    setupGL();

    while (m_Window.isOpen())
    {
        handleInput();
        update();
        render();
    }

    cleanUp();
}

void Game::createWindow()
{
    std::cout << "Creating window" << std::endl;

    m_Window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Close);
    m_Window.setFramerateLimit(60);
}

void Game::setupGL()
{
    std::cout << "Setting up OpenGL and GLEW" << std::endl;

    glewInit();

    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_DEPTH_TEST);
}

void Game::cleanUp()
{
    std::cout << "Cleaning up resources" << std::endl;

    glDisableClientState(GL_VERTEX_ARRAY);
}
