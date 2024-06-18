#include "Element.h"

Element::Element()
{
    eType = none;
    xIndex = 0;
    yIndex = 0;
    colorShade = rand() % 3;
}

Element::Element(ElementType type, int xIndex, int yIndex, int colorShade)
{
    eType = type;
    this->xIndex = xIndex;
    this->yIndex = yIndex;
    this->colorShade = colorShade;
}

void Element::changeElementType(ElementType type)
{
    eType = type;
}

ElementType Element::getElementType() const
{
    return eType;
}

sf::Vector2i Element::getIndicies() const
{
    return sf::Vector2i(xIndex, yIndex);
}

int Element::getColorShade() const
{
    return colorShade;
}
