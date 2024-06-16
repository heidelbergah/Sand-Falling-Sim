#ifndef ELEMENT_H
#define ELEMENT_H

/*
 * Element is a simple container. It has an
 * element type, x and y index, and that's it. The
 * Element class is not resposible for anything other
 * than holding its own information
 */

#include "SFML/Graphics.hpp"

enum ElementType
{
    none,
    sand,
    water,
    wood
};

class Element
{
private:
    ElementType eType;
    int xIndex, yIndex;

public:
    Element();

    Element(ElementType eType, int xIndex, int yIndex);

    void changeElementType(ElementType eType);

    ElementType getElementType() const;

    sf::Vector2i getIndicies() const;
};

#endif
