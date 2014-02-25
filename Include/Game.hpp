#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#include <vector>
#include <memory>

class Game
{
public:
    Game(unsigned width, unsigned height, const std::string& title);
    ~Game();

    void run();

    void handleInput();
    void update();
    void render();

private:
    void createWindow();
    void setupGL();
    void createEntities();

private:
    const unsigned WIDTH;
    const unsigned HEIGHT;
    const std::string TITLE;

    sf::Window m_Window;

    std::map<std::string, std::unique_ptr<Entity>> m_Entities;
};

#endif // GAME_HPP
