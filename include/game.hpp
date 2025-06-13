#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "snake.hpp"
#include "food.hpp"

class Game 
{
    private:
        void handleInput();
        void update();
        void render();
        void checkFoodCollision();
        void reset();
        bool isGameOver;
        int score;
        sf::Font font;
        sf::Text gameOverText;
        sf::Text scoreText;
        sf::Text promptText;
        sf::SoundBuffer eatBuffer;
        sf::Sound eatSound;

        const int blockSize = 20;
        const int widthInBlocks = 40;
        const int heightInBlocks = 30;

        sf::RenderWindow window;
        Snake snake;
        Food food;

    public:
        Game();
        void run();
};
