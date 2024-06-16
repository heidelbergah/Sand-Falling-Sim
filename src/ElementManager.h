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

    void swap(sf::Vector2i indicies1, sf::Vector2i indicies2);
    void randomizeDirection(int& direction1, int& direction2);
    void resetDirtyElements();

    void sandRules(sf::Vector2i indicies);
    void waterRules(sf::Vector2i indicies);

public:
    ElementManager();

    void initializeElementGrid(int e_width, int e_height);

    void updateElements();
    
    void setElement(int xIndex, int yIndex, ElementType type);

    std::vector<std::vector<Element>>& getElements();
};

#endif
