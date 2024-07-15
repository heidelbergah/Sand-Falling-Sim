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
    wood,
    fire,
    steam,
    steel,
    acid,
    gunpowder,
    slime
};

class Element
{
private:
    ElementType eType;
    int xIndex, yIndex, colorShade;

public:
    /**
     * Base constructor. Simply sets a base value for each member variable
     */
    Element();

    /**
     * Sets a specified value for each member variable
     */
    Element(ElementType eType, int xIndex, int yIndex, int colorShade);

    /**
     * Changes the current element type to a specified element type
     */
    void changeElementType(ElementType eType);

    /**
     * Returns the element type
     */
    ElementType getElementType() const;

    /**
     * Returns the indicies of the element
     */
    sf::Vector2i getIndicies() const;

    /**
     * Returns the color shade for the element to be drawn. The color shade ranges
     * from 0-2, 0 being the lighest shade, 2 being the darkest. This helps give elements
     * a more natural looking appearance
     */
    int getColorShade() const;
};

#endif
