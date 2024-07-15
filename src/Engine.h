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
    int WIDTH, HEIGHT, E_WIDTH, E_HEIGHT; // Prefix E is for how many elements go per WIDTH or height
    int SELECTION_TAB_WIDTH;
    int FPS;
    int elementWidth, elementHeight;
    ElementType currElement = none;
    ElementManager em;
    sf::Mouse mouse;
    std::vector<sf::RectangleShape> elementSelectors;
    sf::RectangleShape selectionTab;

    sf::Color selectedOutlineColor, baseOutlineColor;

    /**
     * Spawns elements within a certain radius and chance to spawn
     */
    void spawnElements(int radius, int chanceToSpawn, sf::Vector2f mousePos);

    /**
     * Sets the current element type based on user input
     */
    void setCurrentElement(sf::Vector2f mousePos);

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

    /**
     * Given the elementType or elementType index, will return
     * the base color associated with that element;
     */
    sf::Color getElementColor(ElementType et);

    /**
     * Sets every element in elementManager to type "none",
     * essentially clearing the screen
     */
    void clearScreen();

public:
    /**
     * Base constructor. Sets base values for member variables
     */
    Engine();

    /**
     * Sets members variables to specified values
     */
    Engine(int w, int h, int e_w, int e_h, int stw, int fps);

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
