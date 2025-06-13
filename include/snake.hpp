#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

class Snake 
{
    private:    
        void move();

        int blockSize;
        std::deque<sf::Vector2i> body;
        sf::Vector2i direction;
        bool directionChangedThisFrame = false;
        bool needsToGrow = false;

    public:
        Snake(int blockSize);

        void update();
        void render(sf::RenderWindow& window);
        void setDirection(sf::Vector2i dir);
        void grow();
        bool checkCollision();

        const sf::Vector2i& getHeadPosition() const;
        const std::deque<sf::Vector2i>& getBody() const;
};
