#include "Element.h"

Element::Element()
{
    eType = none;
    xIndex = 0;
    yIndex = 0;
}

Element::Element(ElementType type, int xIndex, int yIndex)
{
    eType = type;
    this->xIndex = xIndex;
    this->yIndex = yIndex;
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
