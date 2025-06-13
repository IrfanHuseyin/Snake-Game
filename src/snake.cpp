#include "snake.hpp"

Snake::Snake(int blockSize) : blockSize(blockSize), direction(1, 0) 
{
    body.push_back({5, 5}); 
}

void Snake::update() 
{
    move();
    directionChangedThisFrame = false;
}

void Snake::move() 
{
    sf::Vector2i newHead = body.front() + direction;
    body.push_front(newHead);

    if (needsToGrow)
    {
        needsToGrow = false;
    }
    else
    {
        body.pop_back();
    }
}

void Snake::setDirection(sf::Vector2i dir) 
{
    if (directionChangedThisFrame)
        return;
    if (dir + direction != sf::Vector2i(0, 0)) 
    {
        direction = dir;
        directionChangedThisFrame = true;
    }
}

void Snake::render(sf::RenderWindow& window) 
{
    sf::RectangleShape segmentShape(sf::Vector2f(blockSize - 1, blockSize - 1));
    segmentShape.setFillColor(sf::Color::Green);

    for (const auto& segment : body) 
    {
        segmentShape.setPosition(segment.x * blockSize, segment.y * blockSize);
        window.draw(segmentShape);
    }
}

void Snake::grow() 
{
    needsToGrow = true;
}

bool Snake::checkCollision() 
{
    const sf::Vector2i& head = body.front();
    for (size_t i = 1; i < body.size(); ++i) 
    {
        if (body[i] == head)
            return true;
    }
    return false;
}

const sf::Vector2i& Snake::getHeadPosition() const 
{
    return body.front();
}

const std::deque<sf::Vector2i>& Snake::getBody() const
{
    return body;
}
