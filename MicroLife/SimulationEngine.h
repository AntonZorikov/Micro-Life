#pragma once

#include "Particle.h"

struct Rule {
    float force;
    float radius;
};

class SimulationEngine {
private:
    std::vector<Particle> particles_r;
    std::vector<Particle> particles_g;
    std::vector<Particle> particles_b;
    std::vector<Particle> particles_y;

    void repelCells(std::vector<Particle>& particles_1, const std::vector<Particle>& particles_2, float force, float radius);

public:
    Rule forces[4][4];
    int rCount = 600;
    int gCount = 600;
    int bCount = 600;
    int yCount = 600;
    int maxRuleForce = 200;
    int maxRuleRadius = 300;

    void generateNewRules();
    void changeRandomRule();
    void generateNewParticles();
    void step();
    void draw();
    void attractTo(sf::Vector2f pos, float force, float radius);
    void clear();
    void createParticle(Particle particle);

    SimulationEngine();
};
