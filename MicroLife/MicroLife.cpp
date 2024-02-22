#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "SimulationEngine.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <thread>


const int windowWidth = 1200, windowHeight = 800;



int main()
{
    std::srand(std::time(0));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Micro Life");
    Particle::setSize(1);
    Particle::setWindow(&window);


    SimulationEngine engine;
    engine.generateNewRules();
    engine.generateNewParticles();
    

    int tic = 0;
    bool isTic = false;

    while (window.isOpen())
    {
        tic++;
        if (tic >= 10 && isTic) {
            std::cout << tic << std::endl;
            tic = 0;
            engine.changeRandomRule();
            std::cout << "!" << std::endl;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                engine.generateNewRules();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                isTic = !isTic;
            }

        }

        engine.step();

        window.clear();
        engine.draw();
        window.display();

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}