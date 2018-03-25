// main.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Square.h"
#include <vector>

int main()
{
    // Set window dimensions and FPS
    int windowWidth = 1024;
    int windowHeight = 768;
    const unsigned int FPS = 60;
    
    // Make a window that is 1024 x 768 pixels and has title "N-Body System"
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
        "N-Body System");
    window.setFramerateLimit(FPS);
    window.setVerticalSyncEnabled(true);
    //window.setKeyRepeatEnabled(false);

    // Create a vector to hold the circles
    CircleVect circles;

    // Create a Square
    Square square(sf::Vector2f(700.f, 500.f), 10.f, 100.f, sf::Color::Blue);

    // frame delay for spawning circles
    bool circleSpawned = false;
    size_t frameDelay = 10;
    int fD = 0;
    bool paused = false;

    /*** Main loop ***/
    while (window.isOpen())
    {
        /*** Handle player input ***/
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::P)
                    paused = !paused; // toggle paused
            }

        } // end while(window.pollEvent(event))

        if (!paused || sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
        {
            // Check for keyboard input
            sf::FloatRect squPosition = square.getPosition();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                && squPosition.left > 0)
                // Square can move left
                square.moveLeft();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                squPosition.left + squPosition.width < windowWidth)
                // Square can move right
                square.moveRight();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                squPosition.top + squPosition.height < windowHeight)
                // Square can move down
                square.moveDown();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                squPosition.top > 0)
                // Square can move up
                square.moveUp();

            /*** Spawning of circles ***/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                && !circleSpawned)
            {
                //Create a new circle
                circles.push_back(Circle());
                circleSpawned = true;
            }

            if (circleSpawned)
            {
                fD++;
                if (fD > frameDelay)
                {
                    circleSpawned = false;
                    fD = 0;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                circles.clear();

            /*** Handle collision of Circle with Square ***/
            for (CircleIt circle = circles.begin(); circle != circles.end(); circle++)
            {
                float circCenterX = circle->getCenter().x;
                float circCenterY = circle->getCenter().y;
                sf::FloatRect circPosition = circle->getPosition();
                bool canMoveLeft = true, canMoveRight = true;
                bool canMoveUp = true, canMoveDown = true;

                if (isCollision(*circle, square))
                {
                    // Top and bottom of square
                    if (circCenterY < squPosition.top && circle->getVelocity().y > 0)
                    {
                        circle->reboundTopBottom();
                        canMoveDown = false;
                    }
                    if (circCenterY > squPosition.top + squPosition.height &&
                        circle->getVelocity().y < 0)
                    {
                        circle->reboundTopBottom();
                        canMoveUp = false;
                    }
                    // Sides of square
                    if (circCenterX < squPosition.left && circle->getVelocity().x > 0)
                    {
                        circle->reboundSides();
                        canMoveRight = false;
                    }

                    if (circCenterX > squPosition.left + squPosition.width &&
                        circle->getVelocity().x < 0)
                    {
                        circle->reboundSides();
                        canMoveLeft = false;
                    }
                }
                /*** Handle Collision of circle with screen ***/
                // Top or bottom:
                if (circPosition.top < 0)
                {
                    circle->reboundTopBottom();
                    canMoveUp = false;
                }
                if (circPosition.top + circPosition.height > windowHeight)
                {
                    circle->reboundTopBottom();
                    canMoveDown = false;
                }
                // Sides:
                if (circPosition.left < 0)
                {
                    circle->reboundSides();
                    canMoveLeft = false;
                }
                if (circPosition.left + circPosition.width > windowWidth)
                {
                    circle->reboundSides();
                    canMoveRight = false;
                }

                /*** Handle collision of circle with other circles ***/
                for (CircleIt nextCircle = circle + 1; nextCircle != circles.end();
                    nextCircle++)
                {
                    if (isCollision(*circle, *nextCircle))
                    {
                        reboundCircles(*circle, *nextCircle);
                        if (circle->getCenter().x < nextCircle->getCenter().x)
                            canMoveRight = false;
                        else
                            canMoveLeft = false;
                        if (circle->getCenter().y < nextCircle->getCenter().y)
                            canMoveDown = false;
                        else
                            canMoveUp = false;
                        //nextCircle->move();
                        //nextCircle->update();
                    }
                }

                // move current circle
                if (canMoveUp && circle->getVelocity().y < 0 ||
                    canMoveDown && circle->getVelocity().y > 0)
                    circle->moveY();
                if (canMoveLeft && circle->getVelocity().x < 0 ||
                    canMoveRight && circle->getVelocity().x > 0)
                    circle->moveX();

                /*** Update circle ***/
                circle->update();

            } // end circle for loop

            // Update square
            square.update();

        } // end if(!paused)

        // clear the frame
        window.clear(sf::Color::Black);

        /*** Draw the frame ***/
        // Circles:
        for (Circle &circle : circles)
            window.draw(circle.getShape());
        // Square:
        window.draw(square.getShape());

        // Show everything we just drew
        window.display();
    
    } // end main loop

    return 0;
}

