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

    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuf);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertBuf);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

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
    glEnableClientState(GL_COLOR_ARRAY);
    glDisable(GL_DEPTH_TEST);

    m_Vertices = { 10.f, 10.f, 0.f, 630.f, 10.f, 0.f, 310.f, 470.f, 0.f };

    glGenBuffers(1, &m_VertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

    m_Colors = { 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f };
    glGenBuffers(1, &m_ColorBuf);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Colors.size(), &m_Colors[0], GL_STATIC_DRAW);
}

void Game::cleanUp()
{
    std::cout << "Cleaning up resources" << std::endl;

    glDeleteBuffers(1, &m_VertBuf);
    glDeleteBuffers(1, &m_ColorBuf);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
