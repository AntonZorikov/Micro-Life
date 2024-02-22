#pragma once

#include "Particle.h"

struct Rule {
    float force;
    float radius;
};

class SimulationEngine {
private:
    Rule forces[4][4];
    std::vector<Particle> particles_r;
    std::vector<Particle> particles_g;
    std::vector<Particle> particles_b;
    std::vector<Particle> particles_y;

    void repelCells(std::vector<Particle>& particles_1, const std::vector<Particle>& particles_2, float force, float radius);

public:
    void generateNewRules();
    void changeRandomRule();
    void generateNewParticles();
    void step();
    void draw();

    SimulationEngine();
};
