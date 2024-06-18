#ifndef ENGINE_H
#define ENGINE_H

#include "Element.h"
#include "ElementManager.h"
#include <vector>
#include <iostream>

class Engine
{
private:
    sf::RenderWindow window;
    int WIDTH, HEIGHT, E_WIDTH, E_HEIGHT; // Suffix E is for how many elements go per WIDTH or height
    int FPS;
    int elementWidth, elementHeight;
    ElementType currElement = sand;

    ElementManager em;

    sf::Mouse mouse;

    /**
     * Sets the current element type based on user input
     */
    void setCurrentElement();

    /**
     * Changes the shade of the element color depending on its associated colorShade.
     * Used for elements like sand, wood, etc.
     */
    void staticColorShade(sf::Color& color, int colorShade) const;
    
    /**
     * Changes the shade of the element color depending on a random number.
     * Used for elements like fire, acid, etc.
     */
    void dynamicColorShade(sf::Color& color) const;
public:
    /**
     * Base constructor. Sets base values for member variables
     */
    Engine();

    /**
     * Sets members variables to specified values
     */
    Engine(int w, int h, int e_w, int e_h, int fps);

    /**
     * Initializes all member objects. Meant to be run one time at the start
     * of the program (called inside the run method)
     */
    void initObjects();

    /**
     * Processes all user input
     */
    void processInput();

    /**
     * Updates all logic of the program
     */
    void update();

    /**
     * Renders all renderable objects to the screen(s)
     */
    void render();

    /**
     * Runs the entire program. Calls all the above methods in a while loop.
     * Meant to be called once in the main.cpp file
     */
    void run();
};

#endif
