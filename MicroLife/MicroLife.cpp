#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "SimulationEngine.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <thread>
#include <functional>
#include "imgui.h"
#include "imgui-SFML.h"

const int windowWidth = 1200, windowHeight = 800;
bool pause = false;
int selectMouseOption = -1, mouseForce = 30, mouseDistance = 200, ruleChangeTime;
float minForce = -2.f, maxForce = 2.f;
int minRadius = 0, maxRadius = 300, minCount = 0, maxCount = 4000, rndRuleChangeMin = 0, rndRuleChangeMax = 500;
float rColor[3] = { 1.0f, 0, 0 };
float gColor[3] = { 0, 1.0f, 0 };
float bColor[3] = { 0, 1.0f, 1.0f };
float yColor[3] = { 1.0f, 1.0f, 0 };


int main()
{
    std::srand(std::time(0));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Micro Life");
    ImGui::SFML::Init(window);
    window.setFramerateLimit(60);
    Particle::size = 0.5f;
    Particle::setWindow(&window);
    SimulationEngine engine;

    engine.generateNewRules();
    engine.generateNewParticles();

    int tic = 0;
    bool isTic = false;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        tic++;

        if (!pause) {
            if (tic >= ruleChangeTime && isTic) {
                tic = 0;
                engine.changeRandomRule();
            }
            engine.step();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectMouseOption == 0) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                engine.attractTo(mousePosFloat, mouseForce, mouseDistance);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectMouseOption == 1) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                engine.attractTo(mousePosFloat, -mouseForce, mouseDistance);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectMouseOption == 2) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                Particle cell(ParticleType::RED, mousePosFloat.x, mousePosFloat.y);
                engine.createParticle(cell);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectMouseOption == 3) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                Particle cell(ParticleType::GREEN, mousePosFloat.x, mousePosFloat.y);
                engine.createParticle(cell);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectMouseOption == 4) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                Particle cell(ParticleType::CYAN, mousePosFloat.x, mousePosFloat.y);
                engine.createParticle(cell);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectMouseOption == 5) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                Particle cell(ParticleType::YELLOW, mousePosFloat.x, mousePosFloat.y);
                engine.createParticle(cell);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                for (unsigned i = 0; i < 4; i++) {
                    for (unsigned j = 0; j < 4; j++) {
                        std::cout << i << " " << j << " " << engine.forces[i][j].force << " " << engine.forces[i][j].radius << std::endl;
                    }
                }
            }
        }

        window.clear();

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Settings");
        ImGui::Checkbox("Stop simulation", &pause);
        ImGui::Checkbox("Rule changes", &isTic);
        ImGui::SliderInt("RuleChangesTime", &ruleChangeTime, rndRuleChangeMin, rndRuleChangeMax);
        if (ImGui::Button("Generate new rules")) {
            engine.generateNewRules();
        }
        if (ImGui::Button("Clear Rules")) {
            for (unsigned i = 0; i < 4; i++) {
                for (unsigned j = 0; j < 4; j++) {
                    engine.forces[i][j].force = 0;
                    engine.forces[i][j].radius = 0;
                }
            }
        }
        ImGui::SliderInt("Max rule force", &engine.maxRuleForce, 0, maxForce * 100);
        ImGui::SliderInt("Max rule radius", &engine.maxRuleRadius, minRadius, maxRadius);

        if (ImGui::Button("Generate new particles")) {
            engine.generateNewParticles();
        }
        if (ImGui::Button("Clear")) {
            engine.clear();
        }

        ImGui::SliderFloat("ParticleSize", &Particle::size, 0.f, 5.f);


        ImGui::Separator();
        if (ImGui::CollapsingHeader("Tools")) {

            ImGui::Text("Tool options:");
            if (ImGui::RadioButton("None", selectMouseOption == -1)) {
                selectMouseOption = -1;
            }
            if (ImGui::RadioButton("Attract particles", selectMouseOption == 0)) {
                selectMouseOption = 0;
            }
            if (ImGui::RadioButton("Repel particles", selectMouseOption == 1)) {
                selectMouseOption = 1;
            }

            ImGui::SliderInt("Force", &mouseForce, 0, 100);
            ImGui::SliderInt("Distance", &mouseDistance, 0, 400);

            if (ImGui::RadioButton("Create red particles", selectMouseOption == 2)) {
                selectMouseOption = 2;
            }
            if (ImGui::RadioButton("Create green particles", selectMouseOption == 3)) {
                selectMouseOption = 3;
            }
            if (ImGui::RadioButton("Create blue particles", selectMouseOption == 4)) {
                selectMouseOption = 4;
            }
            if (ImGui::RadioButton("Create yellow particles", selectMouseOption == 5)) {
                selectMouseOption = 5;
            }
        }

        if (ImGui::CollapsingHeader("Red")) {
            ImGui::SliderInt("Red count", &engine.rCount, minCount, maxCount);
            ImGui::ColorEdit3("RColor", rColor);
            ImGui::SliderFloat("RxR Force", &engine.forces[0][0].force, minForce, maxForce);
            ImGui::SliderFloat("RxG Force", &engine.forces[0][1].force, minForce, maxForce);
            ImGui::SliderFloat("RxB Force", &engine.forces[0][2].force, minForce, maxForce);
            ImGui::SliderFloat("RxY Force", &engine.forces[0][3].force, minForce, maxForce);

            ImGui::SliderFloat("RxR Radius", &engine.forces[0][0].radius, minRadius, maxRadius);
            ImGui::SliderFloat("RxG Radius", &engine.forces[0][1].radius, minRadius, maxRadius);
            ImGui::SliderFloat("RxB Radius", &engine.forces[0][2].radius, minRadius, maxRadius);
            ImGui::SliderFloat("RxY Radius", &engine.forces[0][3].radius, minRadius, maxRadius);
        }

        if (ImGui::CollapsingHeader("Green")) {
            ImGui::SliderInt("Green count", &engine.gCount, minCount, maxCount);
            ImGui::ColorEdit3("GColor", gColor);
            ImGui::SliderFloat("GxR Force", &engine.forces[1][0].force, minForce, maxForce);
            ImGui::SliderFloat("GxG Force", &engine.forces[1][1].force, minForce, maxForce);
            ImGui::SliderFloat("GxB Force", &engine.forces[1][2].force, minForce, maxForce);
            ImGui::SliderFloat("GxY Force", &engine.forces[1][3].force, minForce, maxForce);

            ImGui::SliderFloat("GxR Radius", &engine.forces[1][0].radius, minRadius, maxRadius);
            ImGui::SliderFloat("GxG Radius", &engine.forces[1][1].radius, minRadius, maxRadius);
            ImGui::SliderFloat("GxB Radius", &engine.forces[1][2].radius, minRadius, maxRadius);
            ImGui::SliderFloat("GxY Radius", &engine.forces[1][3].radius, minRadius, maxRadius);
        }

        if (ImGui::CollapsingHeader("Blue")) {
            ImGui::SliderInt("Blue count", &engine.bCount, minCount, maxCount);
            ImGui::ColorEdit3("BColor", bColor);
            ImGui::SliderFloat("BxR Force", &engine.forces[2][0].force, minForce, maxForce);
            ImGui::SliderFloat("BxG Force", &engine.forces[2][1].force, minForce, maxForce);
            ImGui::SliderFloat("BxB Force", &engine.forces[2][2].force, minForce, maxForce);
            ImGui::SliderFloat("BxY Force", &engine.forces[2][3].force, minForce, maxForce);

            ImGui::SliderFloat("BxR Radius", &engine.forces[2][0].radius, minRadius, maxRadius);
            ImGui::SliderFloat("BxG Radius", &engine.forces[2][1].radius, minRadius, maxRadius);
            ImGui::SliderFloat("BxB Radius", &engine.forces[2][2].radius, minRadius, maxRadius);
            ImGui::SliderFloat("BxY Radius", &engine.forces[2][3].radius, minRadius, maxRadius);
        }

        if (ImGui::CollapsingHeader("Yellow")) {
            ImGui::SliderInt("Yellow count", &engine.yCount, minCount, maxCount);
            ImGui::ColorEdit3("YColor", yColor);
            ImGui::SliderFloat("YxR Force", &engine.forces[3][0].force, minForce, maxForce);
            ImGui::SliderFloat("YxG Force", &engine.forces[3][1].force, minForce, maxForce);
            ImGui::SliderFloat("YxB Force", &engine.forces[3][2].force, minForce, maxForce);
            ImGui::SliderFloat("YxY Force", &engine.forces[3][3].force, minForce, maxForce);

            ImGui::SliderFloat("YxR Radius", &engine.forces[3][0].radius, minRadius, maxRadius);
            ImGui::SliderFloat("YxG Radius", &engine.forces[3][1].radius, minRadius, maxRadius);
            ImGui::SliderFloat("YxB Radius", &engine.forces[3][2].radius, minRadius, maxRadius);
            ImGui::SliderFloat("YxY Radius", &engine.forces[3][3].radius, minRadius, maxRadius);
        }

        Particle::rcolor = sf::Color(static_cast<sf::Uint8>(rColor[0] * 255),
                                     static_cast<sf::Uint8>(rColor[1] * 255),
                                     static_cast<sf::Uint8>(rColor[2] * 255));

        Particle::gcolor = sf::Color(static_cast<sf::Uint8>(gColor[0] * 255),
                                     static_cast<sf::Uint8>(gColor[1] * 255),
                                     static_cast<sf::Uint8>(gColor[2] * 255));

        Particle::bcolor = sf::Color(static_cast<sf::Uint8>(bColor[0] * 255),
                                     static_cast<sf::Uint8>(bColor[1] * 255),
                                     static_cast<sf::Uint8>(bColor[2] * 255));

        Particle::ycolor = sf::Color(static_cast<sf::Uint8>(yColor[0] * 255),
                                     static_cast<sf::Uint8>(yColor[1] * 255),
                                     static_cast<sf::Uint8>(yColor[2] * 255));


        ImGui::End();
        ImGui::SFML::Render(window);
        engine.draw();
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}