#ifndef ENGINE_H
#define ENGINE_H

#include "Element.h"
#include "ElementManager.h"
#include <vector>
#include <iostream>

class Engine
{
private:
    sf::RenderWindow window;
    int WIDTH, HEIGHT, E_WIDTH, E_HEIGHT; // Suffix E is for how many elements go per WIDTH or height
    int FPS;
    int elementWidth, elementHeight;

    ElementManager em;

    sf::Mouse mouse;
public:
    Engine();

    Engine(int w, int h, int e_w, int e_h, int fps);

    void initObjects();

    void processInput();

    void update();

    void render();

    void run();
};

#endif
