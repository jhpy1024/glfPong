#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(unsigned width, unsigned height, const std::string& title);

    void run();

    void handleInput();
    void update();
    void render();

private:
    void createWindow();
    void setupGL();
    void cleanUp();

private:
    const unsigned WIDTH;
    const unsigned HEIGHT;
    const std::string TITLE;

    sf::Window m_Window;
};

#endif // GAME_HPP