/*
 * Element indicies start from top left. For example, index (0, 0)
 * is the top left most position an element can be.
 *
 * Additionally, when indexing an element, the y index comes first.
 * For example, index [4][6] grabs the element at y index 4, x index 6
 */

#include "ElementManager.h"

ElementManager::ElementManager()
{
    
}

void ElementManager::swap(sf::Vector2i indicies1, sf::Vector2i indicies2)
{
    dirtyElements[indicies1.y][indicies1.x] = true;
    dirtyElements[indicies2.y][indicies2.x] = true;
    ElementType temp = elements[indicies1.y][indicies1.x].getElementType();
    elements[indicies1.y][indicies1.x].changeElementType(elements[indicies2.y][indicies2.x].getElementType());
    elements[indicies2.y][indicies2.x].changeElementType(temp);
}

void ElementManager::swap(sf::Vector2i indicies1, sf::Vector2i indicies2, ElementType e1, ElementType e2)
{
    dirtyElements[indicies1.y][indicies1.x] = true;
    dirtyElements[indicies2.y][indicies2.x] = true;
    elements[indicies1.y][indicies1.x].changeElementType(e1);
    elements[indicies2.y][indicies2.x].changeElementType(e2);
}

void ElementManager::randomizeDirection(int& direction1, int& direction2)
{
    direction1 = -1;
    if(rand() % 2) {
        direction1 = 1;
    }
    direction2 = direction1 * -1;
}

void ElementManager::resetDirtyElements()
{
    for(int y = 0; y < dirtyElements.size(); ++y)
    {
        for(int x = 0; x < dirtyElements[0].size(); ++x)
        {
            dirtyElements[y][x] = false;
        }
    }
}

void ElementManager::initializeElementGrid(int e_width, int e_height)
{
    for(int y = 0; y < e_height; ++y)
    {
        std::vector<Element> rowElements;
        std::vector<bool> rowDirty;
        for(int x = 0; x < e_width; ++x)
        {
            rowElements.push_back(Element(none, x, y, rand() % 3));
            rowDirty.push_back(false);
        }
        elements.push_back(rowElements);
        dirtyElements.push_back(rowDirty);
    }
}

void ElementManager::sandRules(sf::Vector2i indicies)
{
    int direction1, direction2;
    randomizeDirection(direction1, direction2);
    int x = indicies.x, y = indicies.y;
    if(y != elements.size()-1) // Bounds checking
    {
        // If element below is empty, move to it
        if(elements[y+1][x].getElementType() == none)
            swap(indicies, sf::Vector2i(x, y+1));
        else if(x != elements[0].size()-1 || x != 0) // Bounds checking
        {
            // If either left or right and below is empty, move to it
            if(elements[y+1][x+direction1].getElementType() == none)
                swap(indicies, sf::Vector2i(x+direction1, y+1));
            else if(elements[y+1][x+direction2].getElementType() == none)
                swap(indicies, sf::Vector2i(x+direction2, y+1));
        }
    }
}

void ElementManager::waterRules(sf::Vector2i indicies)
{
    int direction1, direction2;
    randomizeDirection(direction1, direction2);
    int x = indicies.x, y = indicies.y;
    if(y != elements.size()-1) // Bounds checking
    {
        // If element below is empty, move to it.
        if(elements[y+1][x].getElementType() == none)
            swap(indicies, sf::Vector2i(x, y+1));
        else if(x != elements[0].size()-1 || x != 0) // Bounds checking
        {
            // Same as sand, but check directly to left and right as well
            if(elements[y+1][x+direction1].getElementType() == none)
                swap(indicies, sf::Vector2i(x+direction1, y+1));
            else if(elements[y+1][x+direction2].getElementType() == none)
                swap(indicies, sf::Vector2i(x+direction2, y+1));
            else if(elements[y][x+direction1].getElementType() == none)
                swap(indicies, sf::Vector2i(x+direction1, y));
            else if(elements[y][x+direction2].getElementType() == none)
                swap(indicies, sf::Vector2i(x+direction2, y));
        }
    }
}

void ElementManager::updateElements()
{
    resetDirtyElements();
    for(int y = 0; y < elements.size(); ++y)
    {
        for(int x = 0; x < elements[0].size(); ++x)
        {
            // If the current position has already been affected, don't affect it again
            if(dirtyElements[y][x])
                continue;

            Element currElement = elements[y][x];
            switch(currElement.getElementType())
            {
                case none:
                case wood:
                    // Do nothing, just stay stationary
                    break;
                case sand:
                    sandRules(currElement.getIndicies());
                    break;
                case water:
                    waterRules(currElement.getIndicies());
                    break;
            }
        }
    }

}

void ElementManager::setElement(int xIndex, int yIndex, ElementType type)
{
    elements[yIndex][xIndex].changeElementType(type);
}

std::vector<std::vector<Element>>& ElementManager::getElements()
{
    return elements;
}
