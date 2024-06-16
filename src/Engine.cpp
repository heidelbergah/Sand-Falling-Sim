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

    if(mouse.isButtonPressed(sf::Mouse::Left))
    {
        em.setElement(int(currMousePos.x / elementWidth), int(currMousePos.y / elementHeight), sand);
    }
    else if(mouse.isButtonPressed(sf::Mouse::Right))
    {
        em.setElement(int(currMousePos.x / elementWidth), int(currMousePos.y / elementHeight), water);
    }
    else if(mouse.isButtonPressed(sf::Mouse::Middle))
    {
        em.setElement(int(currMousePos.x / elementWidth), int(currMousePos.y / elementHeight), wood);
    }
}

void Engine::update()
{
    em.updateElements();
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
            switch(currElement.getElementType())
            {
                case none:
                    element.setFillColor(sf::Color::Black);
                    break;
                case sand:
                    element.setFillColor(sf::Color::Yellow);
                    break;
                case water:
                    element.setFillColor(sf::Color::Blue);
                    break;
                case wood:
                    element.setFillColor(sf::Color::Green);
                    break;

            }
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
