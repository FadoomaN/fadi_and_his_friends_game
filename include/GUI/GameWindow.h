#pragma once
#include <SFML/Graphics.hpp>



class GameWindow {
public:
    GameWindow();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Texture libraryTexture;
    sf::Texture subwayTexture;
    sf::Sprite background;
    sf::Font font;
    bool fontLoaded = false;

    void startMainMenu();
    void startGame();
};