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
    void createText();

    void handleCollisions();

private:
    const unsigned WIDTH;
    const unsigned HEIGHT;
    const std::string TITLE;

    sf::RenderWindow m_Window;

    std::map<std::string, std::unique_ptr<Entity>> m_Entities;

    sf::Font m_Font;
    sf::Text m_Text;
};

#endif // GAME_HPP
