#include "Engine.h"

Engine::Engine()
{
    WIDTH = 900;
    HEIGHT = 750;
    E_WIDTH = 75;
    E_HEIGHT = 75;
    SELECTION_TAB_WIDTH = 150;
    FPS = 60;
}

Engine::Engine(int w, int h, int e_w, int e_h, int stw, int fps)
{
    WIDTH = w;
    HEIGHT = h;
    E_WIDTH = e_w;
    E_HEIGHT = e_h;
    SELECTION_TAB_WIDTH = stw;
    FPS = fps;
}

void Engine::initObjects()
{
    elementWidth = (WIDTH - SELECTION_TAB_WIDTH) / E_WIDTH;
    elementHeight = HEIGHT / E_HEIGHT;
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Sand Falling Simulator");
    window.setFramerateLimit(FPS);
    em.initializeElementGrid(E_WIDTH, E_HEIGHT);

    // Set up the selection tab elements
    selectionTab.setSize(sf::Vector2f(SELECTION_TAB_WIDTH, HEIGHT));
    selectionTab.setOrigin(SELECTION_TAB_WIDTH, 0);
    selectionTab.setPosition(WIDTH, 0);
    selectionTab.setFillColor(sf::Color(25, 25, 25));
    
    selectedOutlineColor.r = 187;
    selectedOutlineColor.g = 165;
    selectedOutlineColor.b = 61;
    baseOutlineColor.r = 80;
    baseOutlineColor.g = 80;
    baseOutlineColor.b = 80;

    int middleDivider = SELECTION_TAB_WIDTH / 2;
    int padding = 10;
    int elementSelectorSize = middleDivider - (padding*2);
    int adjustedWidth = WIDTH - SELECTION_TAB_WIDTH;
    int yLevel = 0;
    // Update acid to the last element in the ElementType enum
    for(int i = 0; i < 8; ++i)
    {
        sf::RectangleShape elementSelector;
        elementSelector.setFillColor(getElementColor(ElementType(i)));
        elementSelector.setOutlineThickness(2);
        elementSelector.setOutlineColor(baseOutlineColor); // Gold color
        elementSelector.setSize(sf::Vector2f(elementSelectorSize, elementSelectorSize));
        if(i % 2 == 0)
        {
            elementSelector.setPosition(adjustedWidth + padding, padding + (padding + elementSelectorSize) * yLevel);
        }
        else
        {
            elementSelector.setPosition(adjustedWidth + padding + middleDivider, padding + (padding + elementSelectorSize) * yLevel);
            yLevel++;
        }
        elementSelectors.push_back(elementSelector);
    }
}

void Engine::setCurrentElement(sf::Vector2f mousePos)
{
    for(int i = 0; i < elementSelectors.size(); ++i)
    {
        if(mouse.isButtonPressed(sf::Mouse::Left))
        {
            if(elementSelectors[i].getGlobalBounds().contains(mousePos))
            {
                elementSelectors[currElement].setOutlineColor(baseOutlineColor);
                elementSelectors[currElement].setOutlineThickness(2);
                elementSelectors[i].setOutlineColor(selectedOutlineColor); // Gold color
                elementSelectors[i].setOutlineThickness(4);
                currElement = ElementType(i);
                return;
            }
        }
    }
}

void Engine::processInput()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
    }

    // Mapping to pixel coords will help keep mouse position accurate to world view.
    sf::Vector2f currMousePos = window.mapPixelToCoords(mouse.getPosition(window));
    
    setCurrentElement(currMousePos); // Set the current element based on any recieved input

    // Spawn in currently selected element
    if(mouse.isButtonPressed(sf::Mouse::Left))
    {
        int radius = 1;
        int chanceToSpawn = 3; // 1/3 chance for element to actually spawn
        // Keeping the element selection tab to the right of the world view allows us to keep the same
        // formula for calculating the x and y index. If the tab were to the left, we would have to subtract
        // the current mouse position with the selection tab width.
        int xIndex = int(currMousePos.x / elementWidth), yIndex = int(currMousePos.y / elementHeight);
        for(int y = yIndex - radius; y < yIndex + radius; ++y)
        {
            for(int x = xIndex - radius; x < xIndex + radius; ++x)
            {
                // Stop from attempting to spawn elements out of range
                if(x < 0 || x >= E_WIDTH || y < 0 || y >= E_HEIGHT)
                    break;
                if(rand() % chanceToSpawn == 0)
                    em.setElement(x, y, currElement);
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        
    }
}

void Engine::update()
{
    em.updateElements();
}

void Engine::staticColorShade(sf::Color& color, int colorShade) const
{
    if(colorShade == 0)
    {
        int darkeningFactor = 10;
        color.r -= darkeningFactor;
        color.g -= darkeningFactor;
        color.b -= darkeningFactor;
    }
    else if(colorShade == 2)
    {
        int lighteningFactor = 10;
        color.r += lighteningFactor;
        color.g += lighteningFactor;
        color.b += lighteningFactor;
    }
}
    
void Engine::dynamicColorShade(sf::Color& color) const
{
    int colorShade = rand() % 3;
    staticColorShade(color, colorShade);
}
    
sf::Color Engine::getElementColor(ElementType et)
{
    switch(et)
    {
        case none:
            return sf::Color(0, 0, 0);
            break;
        case sand:
            return sf::Color(236, 204, 162);
            break;
        case water:
            return sf::Color(35, 187, 213);
            break;
        case wood:
            return sf::Color(133, 94, 66);
            break;
        case fire:
            return sf::Color(226, 88, 34);
            break;
        case steam:
            return sf::Color(199, 213, 224);
            break;
        case steel:
            return sf::Color(122, 127, 128);
            break;
        case acid:
            return sf::Color(56, 100, 10);
            break;
    }
    return sf::Color(0, 0, 0);
}

void Engine::render()
{
    std::vector<std::vector<Element>> elements = em.getElements();
    window.clear();
    
    for(int y = 0; y < elements.size(); ++y)
    {
        for(int x = 0; x < elements[0].size(); ++x)
        {
            Element currElement = elements[y][x];
            sf::RectangleShape element(sf::Vector2f(elementWidth, elementHeight));
            int colorShade = elements[y][x].getColorShade();
            sf::Color elementColor;
            switch(currElement.getElementType())
            {
                case none:
                    elementColor = getElementColor(none);
                    break;
                case sand:
                    elementColor = getElementColor(sand);
                    staticColorShade(elementColor, colorShade);
                    break;
                case water:
                    elementColor = getElementColor(water);
                    staticColorShade(elementColor, colorShade);
                    break;
                case wood:
                    elementColor = getElementColor(wood);
                    staticColorShade(elementColor, colorShade);
                    break;
                case fire:
                    elementColor = getElementColor(fire);
                    dynamicColorShade(elementColor);
                    break;
                case steam:
                    elementColor = getElementColor(steam);
                    staticColorShade(elementColor, colorShade);
                    break;
                case steel:
                    elementColor = getElementColor(steel);
                    staticColorShade(elementColor, colorShade);
                    break;
                case acid:
                    elementColor = getElementColor(acid);
                    dynamicColorShade(elementColor);
                    break;
            }
            element.setFillColor(elementColor);
            element.setPosition(elementWidth * currElement.getIndicies().x, elementHeight * currElement.getIndicies().y);
            window.draw(element);
        }
    }
    
    // Selection tab rendering
    window.draw(selectionTab);
    for(sf::RectangleShape shape : elementSelectors)
    {
        window.draw(shape);
    }
    
    // Display everything
    window.display();
}

void Engine::run()
{
    initObjects();

    while(window.isOpen())
    {
        processInput();
        
        update();

        render();
    }
}
