#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

class Food
{
    private:
        int blockSize;
        int widthInBlocks;
        int heightInBlocks;

        sf::Vector2i position;
        sf::RectangleShape shape;

    public:
        Food(int blockSize, int widthInBlocks, int heightInBlocks, const std::deque<sf::Vector2i>& snakeBody);

        void respawn(const std::deque<sf::Vector2i>& snakeBody);
        void render(sf::RenderWindow& window);
        const sf::Vector2i& getPosition() const;
};
