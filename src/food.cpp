#include "food.hpp"
#include <cstdlib>
#include <ctime>
#include <deque>

Food::Food(int blockSize, int widthInBlocks, int heightInBlocks, const std::deque<sf::Vector2i>& snakeBody)
    : blockSize(blockSize), widthInBlocks(widthInBlocks), heightInBlocks(heightInBlocks)
{
    shape.setSize(sf::Vector2f(blockSize - 1, blockSize - 1));
    shape.setFillColor(sf::Color::Red);

    respawn(snakeBody);
}

void Food::respawn(const std::deque<sf::Vector2i>& snakeBody)
{
    bool valid = false;

    while (!valid)
    {
        position.x = std::rand() % widthInBlocks;
        position.y = std::rand() % heightInBlocks;

        valid = true;
        for (const auto& segment : snakeBody)
        {
            if (segment == position)
            {
                valid = false;
                break;
            }
        }
    }

    shape.setPosition(position.x * blockSize, position.y * blockSize);
}

void Food::render(sf::RenderWindow& window)
{
    shape.setPosition(static_cast<float>(position.x) * blockSize, static_cast<float>(position.y) * blockSize);
    window.draw(shape);
}

const sf::Vector2i& Food::getPosition() const
{
    return position;
}
