#include "Game.hpp"
#include "Paddle.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
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
    for (auto& entity : m_Entities)
    {
        entity.second->update();
    }
}

void Game::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& entity : m_Entities)
    {
        entity.second->render();
    }

    m_Window.display();
}

void Game::run()
{
    createWindow();
    setupGL();
    createEntities();

    while (m_Window.isOpen())
    {
        handleInput();
        update();
        render();
    }
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

    GLenum glewInitStatus = glewInit();
    if (glewInitStatus == GLEW_OK)
        std::cout << "GLEW initialized successfully" << std::endl;
    else
        std::cout << "Failed to initialize GLEW: " << glewGetErrorString(glewInitStatus) << std::endl;

    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDisable(GL_DEPTH_TEST);
}

void Game::createEntities()
{
    m_Entities["Paddle"] = std::unique_ptr<Paddle>(new Paddle(10.f, 10.f, 50.f, 100.f));
}

Game::~Game()
{
    std::cout << "Cleaning up resources" << std::endl;

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
