#include "GUI/GameWindow.h"
#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace {
const sf::Color ButtonColor(35, 55, 85, 235);
const sf::Color ButtonHoverColor(55, 90, 130, 245);
}

GameWindow::GameWindow()
    : window(sf::VideoMode({1280, 720}), "Fadi and His Friends"),
      background(backgroundTexture) {
    window.setFramerateLimit(60);

    if (!backgroundTexture.loadFromFile("assets/images/mapsAndRooms/Malmö_University_Street_Scene.png")) {
        std::cerr << "Could not load the main menu background." << std::endl;
    }
    if (!libraryTexture.loadFromFile("assets/images/mapsAndRooms/library.png")) {
        std::cerr << "Could not load the library image." << std::endl;
    }
    if (!subwayTexture.loadFromFile("assets/images/mapsAndRooms/malmö_subway.png")) {
        std::cerr << "Could not load the subway image." << std::endl;
    }

    background.setTexture(backgroundTexture, true);
    const auto textureSize = backgroundTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        background.setScale({
            static_cast<float>(window.getSize().x) / textureSize.x,
            static_cast<float>(window.getSize().y) / textureSize.y
        });
    }

    fontLoaded = font.openFromFile("assets/fonts/arial.ttf");
    if (!fontLoaded) {
        fontLoaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");
    }
}

void GameWindow::run() {
    startMainMenu();
}

void GameWindow::startMainMenu() {
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        const auto mousePosition = sf::Mouse::getPosition(window);
        const sf::FloatRect startButtonBounds({460.f, 390.f}, {360.f, 75.f});
        const sf::FloatRect exitButtonBounds({460.f, 490.f}, {360.f, 75.f});
        const bool startHovered = startButtonBounds.contains(
            {static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)});
        const bool exitHovered = exitButtonBounds.contains(
            {static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)});

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (startHovered) {
                startGame();
                return;
            }
            if (exitHovered) {
                window.close();
                return;
            }
        }

        window.clear(sf::Color(25, 30, 45));
        if (backgroundTexture.getSize().x > 0) {
            window.draw(background);
        }

        sf::RectangleShape overlay({1280.f, 720.f});
        overlay.setFillColor(sf::Color(0, 0, 0, 105));
        window.draw(overlay);

        sf::RectangleShape startButton(startButtonBounds.size);
        startButton.setPosition(startButtonBounds.position);
        startButton.setFillColor(startHovered ? ButtonHoverColor : ButtonColor);
        window.draw(startButton);

        sf::RectangleShape exitButton(exitButtonBounds.size);
        exitButton.setPosition(exitButtonBounds.position);
        exitButton.setFillColor(exitHovered ? ButtonHoverColor : ButtonColor);
        window.draw(exitButton);

        if (fontLoaded) {
            sf::Text title(font, "FADI AND HIS FRIENDS", 52);
            title.setPosition({315.f, 145.f});
            title.setFillColor(sf::Color::White);
            window.draw(title);

            sf::Text startText(font, "START GAME", 28);
            startText.setPosition({565.f, 410.f});
            window.draw(startText);

            sf::Text exitText(font, "EXIT", 28);
            exitText.setPosition({615.f, 510.f});
            window.draw(exitText);
        }

        window.display();
    }
}

void GameWindow::startGame() {
    std::string locationMessage = "Choose a location";
    sf::Clock transitionClock;
    bool showingLibrary = false;
    bool showingSubway = false;
    bool transitioning = false;
    bool fadingIn = false;
    float transitionAlpha = 0.f;
    sf::Texture* transitionTarget = nullptr;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return;
            }
            if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                background.setTexture(backgroundTexture, true);
                return;
            }
            if (event->is<sf::Event::MouseButtonPressed>() &&
                event->getIf<sf::Event::MouseButtonPressed>()->button ==
                    sf::Mouse::Button::Left) {
                const auto mousePosition = sf::Mouse::getPosition(window);
                const sf::Vector2f clickPosition(
                    static_cast<float>(mousePosition.x),
                    static_cast<float>(mousePosition.y));

                const sf::FloatRect universityHotspot({20.f, 475.f}, {210.f, 170.f});
                const sf::FloatRect malmoCHotspot({1120.f, 450.f}, {145.f, 155.f});
                const sf::FloatRect backButton({1040.f, 650.f}, {200.f, 45.f});

                if (!transitioning && !showingLibrary && !showingSubway &&
                    universityHotspot.contains(clickPosition)) {
                    locationMessage = "University selected - library is next";
                    transitionTarget = &libraryTexture;
                    transitioning = true;
                    fadingIn = false;
                    transitionAlpha = 0.f;
                    transitionClock.restart();
                } else if (!transitioning && !showingLibrary && !showingSubway &&
                           malmoCHotspot.contains(clickPosition)) {
                    locationMessage = "Malmo C";
                    transitionTarget = &subwayTexture;
                    transitioning = true;
                    fadingIn = false;
                    transitionAlpha = 0.f;
                    transitionClock.restart();
                } else if (!transitioning && (showingLibrary || showingSubway) &&
                           backButton.contains(clickPosition)) {
                    locationMessage = "Street";
                    transitionTarget = &backgroundTexture;
                    transitioning = true;
                    fadingIn = false;
                    transitionAlpha = 0.f;
                    transitionClock.restart();
                }
            }
        }

        if (transitioning) {
            const float transitionSpeed = 420.f;
            const float transitionAmount = transitionClock.restart().asSeconds() * transitionSpeed;

            if (!fadingIn) {
                transitionAlpha += transitionAmount;
                if (transitionAlpha >= 255.f) {
                    transitionAlpha = 255.f;
                    background.setTexture(*transitionTarget, true);
                    showingLibrary = transitionTarget == &libraryTexture;
                    showingSubway = transitionTarget == &subwayTexture;
                    fadingIn = true;
                }
            } else {
                transitionAlpha -= transitionAmount;
                if (transitionAlpha <= 0.f) {
                    transitionAlpha = 0.f;
                    transitioning = false;
                }
            }
        }

        const auto mousePosition = sf::Mouse::getPosition(window);
        const sf::Vector2f mousePositionFloat(
            static_cast<float>(mousePosition.x),
            static_cast<float>(mousePosition.y));
        const sf::FloatRect universityHotspot({20.f, 475.f}, {210.f, 170.f});
        const sf::FloatRect malmoCHotspot({1120.f, 450.f}, {145.f, 155.f});

        window.clear(sf::Color(30, 30, 40));
        window.draw(background);

        sf::RectangleShape hud({1280.f, 70.f});
        hud.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(hud);

        if (!showingLibrary && !showingSubway) {
            sf::CircleShape universityMarker(12.f);
            universityMarker.setPosition({108.f, 550.f});
            universityMarker.setFillColor(universityHotspot.contains(mousePositionFloat)
                ? sf::Color(80, 220, 130, 230)
                : sf::Color(255, 220, 70, 220));
            window.draw(universityMarker);

            sf::CircleShape malmoCMarker(12.f);
            malmoCMarker.setPosition({1182.f, 515.f});
            malmoCMarker.setFillColor(malmoCHotspot.contains(mousePositionFloat)
                ? sf::Color(80, 220, 130, 230)
                : sf::Color(255, 220, 70, 220));
            window.draw(malmoCMarker);
        } else {
            const sf::FloatRect backButton({1040.f, 650.f}, {200.f, 45.f});
            sf::RectangleShape backShape(backButton.size);
            backShape.setPosition(backButton.position);
            backShape.setFillColor(ButtonColor);
            window.draw(backShape);
        }

        if (fontLoaded) {
            sf::Text locationText(font, locationMessage, 22);
            locationText.setPosition({30.f, 20.f});
            window.draw(locationText);

            sf::Text helpText(font, showingLibrary
                ? "Library | Back to Street"
                : showingSubway
                    ? "Subway | Back to Street"
                    : "Click a marked location | ESC: menu", 20);
            helpText.setPosition({30.f, 675.f});
            window.draw(helpText);

            if (showingLibrary || showingSubway) {
                sf::Text backText(font, "BACK", 20);
                backText.setPosition({1110.f, 660.f});
                window.draw(backText);
            }
        }

        if (transitioning) {
            sf::RectangleShape fadeOverlay({1280.f, 720.f});
            fadeOverlay.setFillColor(sf::Color(0, 0, 0,
                static_cast<std::uint8_t>(transitionAlpha)));
            window.draw(fadeOverlay);
        }

        window.display();
    }
}
