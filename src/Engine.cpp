#include "Engine.h"

Engine::Engine()
{
    WIDTH = 750;
    HEIGHT = 750;
    E_WIDTH = 75;
    E_HEIGHT = 75;

    FPS = 60;
}

Engine::Engine(int w, int h, int e_w, int e_h, int fps)
{
    WIDTH = w;
    HEIGHT = h;
    E_WIDTH = e_w;
    E_HEIGHT = e_h;
    FPS = fps;
}

void Engine::initObjects()
{
    elementWidth = WIDTH / E_WIDTH;
    elementHeight = HEIGHT / E_HEIGHT;
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Sand Falling Simulator");
    window.setFramerateLimit(FPS);
    em.initializeElementGrid(E_WIDTH, E_HEIGHT);
}

void Engine::setCurrentElement()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        currElement = sand;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        currElement = water;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        currElement = wood;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        currElement = fire;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        currElement = steam;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
    {
        currElement = steel;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
    {
        currElement = acid;
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

    setCurrentElement(); // Set the current element based on any recieved input

    // Mapping to pixel coords will help keep mouse position accurate to world view.
    sf::Vector2f currMousePos = window.mapPixelToCoords(mouse.getPosition(window));

    if(mouse.isButtonPressed(sf::Mouse::Left))
    {
        int radius = 1;
        int chanceToSpawn = 3; // 1/3 chance for element to actually spawn
        int xIndex = int(currMousePos.x / elementWidth), yIndex = int(currMousePos.y / elementHeight);
        for(int y = yIndex - radius; y < yIndex + radius; ++y)
        {
            for(int x = xIndex - radius; x < xIndex + radius; ++x)
            {
                if(rand() % chanceToSpawn == 0)
                    em.setElement(x, y, currElement);
            }
        }
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
                    elementColor = sf::Color::Black;
                    break;
                case sand:
                    elementColor = sf::Color(236, 204, 162);
                    staticColorShade(elementColor, colorShade);
                    break;
                case water:
                    elementColor = sf::Color(35, 187, 213);
                    staticColorShade(elementColor, colorShade);
                    break;
                case wood:
                    elementColor = sf::Color(133, 94, 66);
                    staticColorShade(elementColor, colorShade);
                    break;
                case fire:
                    elementColor = sf::Color(226, 88, 34);
                    dynamicColorShade(elementColor);
                    break;
                case steam:
                    elementColor = sf::Color(199, 213, 224);
                    staticColorShade(elementColor, colorShade);
                    break;
                case steel:
                    elementColor = sf::Color(122, 127, 128);
                    staticColorShade(elementColor, colorShade);
                    break;
                case acid:
                    elementColor = sf::Color(56, 100, 10);
                    dynamicColorShade(elementColor);
                    break;
            }
            element.setFillColor(elementColor);
            element.setPosition(elementWidth * currElement.getIndicies().x, elementHeight * currElement.getIndicies().y);
            window.draw(element);
        }
    }

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
