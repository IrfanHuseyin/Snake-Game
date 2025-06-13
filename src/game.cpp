#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game()
    : window(sf::VideoMode(widthInBlocks * blockSize, heightInBlocks * blockSize), "Snake"),
      snake(blockSize), food(blockSize, widthInBlocks, heightInBlocks, snake.getBody()) 
{
    isGameOver = false;
    window.setFramerateLimit(10);
    window.setMouseCursorVisible(false);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!font.loadFromFile("assets/font/snake.ttf"))
    {
        std::cerr << "Unable to load font!" << std::endl;
    }
    if (!eatBuffer.loadFromFile("assets/audio/snake.wav")) 
    {
        std::cerr << "Failed to load snake.wav!" << std::endl;
    }
    
    eatSound.setBuffer(eatBuffer);

    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    score = 0;
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Blue);
    gameOverText.setStyle(sf::Text::Bold);

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString(" ");

    promptText.setFont(font);
    promptText.setString("Enter to Play Again\nEsc to Quit");
    promptText.setCharacterSize(50);
    promptText.setFillColor(sf::Color::Blue);
    promptText.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameOverText.setPosition((widthInBlocks * blockSize) / 2.0f, (heightInBlocks * blockSize) / 3.0f);

    sf::FloatRect promptRect = promptText.getLocalBounds();
    promptText.setOrigin(promptRect.width / 2, promptRect.height / 2);
    promptText.setPosition((widthInBlocks * blockSize) / 2.0f, (heightInBlocks * blockSize) / 2.0f + 60);
}

void Game::run() 
{
    while (window.isOpen()) 
    {
        handleInput();

        if (!isGameOver)
        {
            window.setMouseCursorVisible(false);
            update();
        }
        else
        {
            window.setMouseCursorVisible(true);
        }

        render();
    }
}

void Game::handleInput() 
{   
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            else if (isGameOver) 
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    reset();
                }
            }
            else 
            {
                switch (event.key.code) 
                {
                    case sf::Keyboard::Up:    snake.setDirection({0, -1}); break;
                    case sf::Keyboard::Down:  snake.setDirection({0, 1}); break;
                    case sf::Keyboard::Left:  snake.setDirection({-1, 0}); break;
                    case sf::Keyboard::Right: snake.setDirection({1, 0}); break;
                    default: break;
                }
            }
        }
    }
}

void Game::update() 
{
    if (isGameOver)
        return;

    snake.update();

    sf::Vector2i head = snake.getHeadPosition();
    if (head.x < 0 || head.x >= widthInBlocks || head.y < 0 || head.y >= heightInBlocks) 
    {
        isGameOver = true;
        return;
    }
    if (snake.checkCollision()) 
    {
        isGameOver = true;
        return;
    }

    checkFoodCollision();
}

void Game::render() 
{
    window.clear(sf::Color::Black);
    snake.render(window);
    food.render(window);
    window.draw(scoreText);

    if (isGameOver)
    {
        window.draw(gameOverText);
        window.draw(promptText);
    }
    
    window.display();
}

void Game::checkFoodCollision()
{
    if (snake.getHeadPosition() == food.getPosition())
    {
        snake.grow();     
        score++;
        scoreText.setString(" " + std::to_string(score));
        food.respawn(snake.getBody());   
        eatSound.play();
    }
}

void Game::reset() 
{
    snake = Snake(blockSize);
    food = Food(blockSize, widthInBlocks, heightInBlocks, snake.getBody());
    isGameOver = false;
    score = 0;
    scoreText.setString(" ");
}
