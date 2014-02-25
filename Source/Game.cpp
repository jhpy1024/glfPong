#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
        paddlePtr->moveUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        auto paddlePtr = static_cast<Paddle*>(m_Entities["Paddle"].get());
        paddlePtr->moveDown();
    }
}

void Game::update()
{
    for (auto& entity : m_Entities)
    {
        entity.second->update();
    }

    handleCollisions();
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

void Game::handleCollisions()
{
    // == Paddle position/size
    float pX = m_Entities["Paddle"]->getX();
    float pY = m_Entities["Paddle"]->getY();
    float pW = m_Entities["Paddle"]->getWidth();
    float pH = m_Entities["Paddle"]->getHeight();

    // == Ball position/size
    float bX = m_Entities["Ball"]->getX();
    float bY = m_Entities["Ball"]->getY();
    float bW = m_Entities["Ball"]->getWidth();
    float bH = m_Entities["Ball"]->getHeight();

    sf::FloatRect paddleRect;
    sf::FloatRect ballRect;

    paddleRect.left = pX;
    paddleRect.top = pY + pH;
    paddleRect.width = pW;
    paddleRect.height = -pH;

    ballRect.left = bX - bW;
    ballRect.top = bY + bH;
    ballRect.width = bW;
    ballRect.height = -bH;

    if (paddleRect.intersects(ballRect))
    {
        auto ballPtr = static_cast<Ball*>(m_Entities["Ball"].get());
        ballPtr->hitPaddle();
    }
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
    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_DEPTH_TEST);
}

void Game::createEntities()
{
    m_Entities["Paddle"] = std::unique_ptr<Paddle>(new Paddle(10.f, 10.f, 15.f, 150.f));
    m_Entities["Ball"] = std::unique_ptr<Ball>(new Ball(WIDTH / 2.f, HEIGHT / 2.f, 10.f));
}

Game::~Game()
{
    std::cout << "Cleaning up resources" << std::endl;

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
