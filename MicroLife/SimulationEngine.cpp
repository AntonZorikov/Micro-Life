#include "SimulationEngine.h"
#include <cstdlib>
#include <ctime>

void SimulationEngine::repelCells(std::vector<Particle>& particles_1, const std::vector<Particle>& particles_2, float force, float radius) {
    for (auto& particle_1 : particles_1) {
        float fx = 0, fy = 0;
        for (const auto& particle_2 : particles_2) {
            float dx = particle_2.getX() - particle_1.getX();
            float dy = particle_2.getY() - particle_1.getY();
            float distanceSquared = dx * dx + dy * dy;

            if (distanceSquared > 0 && distanceSquared < radius * radius) {
                float distance = std::sqrtf(distanceSquared);
                float F = force / distance;

                fx += F * dx;
                fy += F * dy;
            }
        }
        particle_1.push(fx * 0.5f, fy * 0.5f);
        particle_1.move();
    }
}

void SimulationEngine::generateNewRules() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {
            forces[i][j].force = ((rand() % 200) - 100) / 200.f;
            forces[i][j].radius = rand() % 300;
        }
    }
}

void SimulationEngine::changeRandomRule() {
    forces[rand() % 4][rand() % 4].force = ((rand() % 200) - 100) / 200.f;
    forces[rand() % 4][rand() % 4].radius = rand() % 300;
}

void SimulationEngine::generateNewParticles() {
    for (unsigned i = 0; i < 1000; i++) {
        ParticleType type = ParticleType::CYAN;
        if (rand() % 4 == 0) {
            type = ParticleType::RED;
            Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
            particles_r.push_back(cell);
        }
        else if (rand() % 4 == 1) {
            type = ParticleType::CYAN;
            Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);  
            particles_b.push_back(cell);
        }
        else if (rand() % 4 == 2) {
            type = ParticleType::YELLOW;
            Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
            particles_y.push_back(cell);
        }
        else {
            type = ParticleType::GREEN;
            Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
            particles_g.push_back(cell);
        }
    }
}

void SimulationEngine::step() {
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {
            std::vector<Particle>* c1 = &particles_r;
            std::vector<Particle>* c2 = &particles_r;
            if (i == 0) c1 = &particles_r;
            if (i == 1) c1 = &particles_g;
            if (i == 2) c1 = &particles_b;
            if (i == 3) c1 = &particles_y;

            if (j == 0) c2 = &particles_r;
            if (j == 1) c2 = &particles_g;
            if (j == 2) c2 = &particles_b;
            if (j == 3) c2 = &particles_y;
            repelCells(*c1, *c2, forces[i][j].force, forces[i][j].radius);
        }
    }
}

void SimulationEngine::draw() {
    for (unsigned i = 0; i < particles_r.size(); i++) {
        particles_r[i].draw();
    }
    for (unsigned i = 0; i < particles_g.size(); i++) {
        particles_g[i].draw();
    }
    for (unsigned i = 0; i < particles_b.size(); i++) {
        particles_b[i].draw();
    }
    for (unsigned i = 0; i < particles_y.size(); i++) {
        particles_y[i].draw();
    }
}

SimulationEngine::SimulationEngine() {
    generateNewRules();
    generateNewParticles();
}
