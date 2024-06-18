#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include "Element.h"
#include <vector>
#include <random>

class ElementManager
{
private:
    std::vector<std::vector<Element>> elements;
    std::vector<std::vector<bool>> dirtyElements;

    /**
     * Swap the element types of two elements given their indicies in the elements vector
     */
    void swap(sf::Vector2i indicies1, sf::Vector2i indicies2);
    
    /**
     * Set the element types of two elements given their indicies in the elements vector
     * and what their new element should be set to
     */
    void swap(sf::Vector2i indicies1, sf::Vector2i indicies2, ElementType e1, ElementType e2);
    
    /**
     * Given two integers that represent an x direction, set one to -1 and the other to 1 randomly
     */
    void randomizeDirection(int& direction1, int& direction2);
    
    /**
     * Resets the dirtyElements vector to all false
     */
    void resetDirtyElements();

    /**
     * The following [element]Rules functions are the set of rules
     * each element will follow when the updateElements function is run.
     * The indicies are provided to tell which element is currently being
     * updated.
     */
    void sandRules(sf::Vector2i indicies);
    void waterRules(sf::Vector2i indicies);
    void fireRules(sf::Vector2i indicies);
    void steamRules(sf::Vector2i indicies);
    void acidRules(sf::Vector2i indicies);

public:
    /**
     * Base constructor. Does nothing except initialize the object
     */
    ElementManager();

    /**
     * Sets the elements vector to equal the width and height of the provided
     * e_width and e_height, and fills every element with a "none" type element.
     * Additionally sets the dirtyElements vector to the same width and height,
     * but each element is set to false.
     */
    void initializeElementGrid(int e_width, int e_height);

    /**
     * Update each element according to its element rules in the elements vector
     */
    void updateElements();
    
    /**
     * Sets the element at the index to a specified element type
     */
    void setElement(int xIndex, int yIndex, ElementType type);

    /**
     * Returns a reference to the elements vector
     */
    std::vector<std::vector<Element>>& getElements();
};

#endif
