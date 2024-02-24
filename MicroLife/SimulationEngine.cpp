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
            forces[i][j].force = ((rand() % maxRuleForce) - std::ceil(maxRuleForce / 2)) / maxRuleForce;
            forces[i][j].radius = rand() % maxRuleRadius;
        }
    }
}

void SimulationEngine::changeRandomRule() {
    forces[rand() % 4][rand() % 4].force = ((rand() % maxRuleForce) - std::ceil(maxRuleForce / 2)) / maxRuleForce;
    forces[rand() % 4][rand() % 4].radius = rand() % maxRuleRadius;
}

void SimulationEngine::generateNewParticles() {
    clear();
    for (unsigned i = 0; i < rCount; i++) {
        ParticleType type = ParticleType::RED;
        Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
        particles_r.push_back(cell);
    }
    for (unsigned i = 0; i < gCount; i++) {
        ParticleType type = ParticleType::GREEN;
        Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
        particles_g.push_back(cell);
    }
    for (unsigned i = 0; i < bCount; i++) {
        ParticleType type = ParticleType::CYAN;
        Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
        particles_b.push_back(cell);
    }
    for (unsigned i = 0; i < yCount; i++) {
        ParticleType type = ParticleType::YELLOW;
        Particle cell(type, rand() % Particle::window->getSize().x, rand() % Particle::window->getSize().y);
        particles_y.push_back(cell);
    }
}

void SimulationEngine::step() {
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {
            std::vector<Particle>* c1;
            std::vector<Particle>* c2;
            if (i == 0) c1 = &particles_r;
            else if (i == 1) c1 = &particles_g;
            else if (i == 2) c1 = &particles_b;
            else c1 = &particles_y;

            if (j == 0) c2 = &particles_r;
            else if (j == 1) c2 = &particles_g;
            else if (j == 2) c2 = &particles_b;
            else c2 = &particles_y;
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

void SimulationEngine::attractTo(sf::Vector2f pos, float force, float radius) {
    for (auto particle = particles_r.begin(); particle != particles_r.end(); particle++) {
        float fx = 0, fy = 0;
        float dx = pos.x - particle->getX();
        float dy = pos.y - particle->getY();
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared > 0 && distanceSquared < radius * radius) {
            float distance = std::sqrtf(distanceSquared);
            float F = force / distance;

            fx += F * dx;
            fy += F * dy;
        }
        particle->push(fx * 0.5f, fy * 0.5f);
        particle->move();
    }
    for (auto particle = particles_g.begin(); particle != particles_g.end(); particle++) {
        float fx = 0, fy = 0;
        float dx = pos.x - particle->getX();
        float dy = pos.y - particle->getY();
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared > 0 && distanceSquared < radius * radius) {
            float distance = std::sqrtf(distanceSquared);
            float F = force / distance;

            fx += F * dx;
            fy += F * dy;
        }
        particle->push(fx * 0.5f, fy * 0.5f);
        particle->move();
    }
    for (auto particle = particles_b.begin(); particle != particles_b.end(); particle++) {
        float fx = 0, fy = 0;
        float dx = pos.x - particle->getX();
        float dy = pos.y - particle->getY();
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared > 0 && distanceSquared < radius * radius) {
            float distance = std::sqrtf(distanceSquared);
            float F = force / distance;

            fx += F * dx;
            fy += F * dy;
        }
        particle->push(fx * 0.5f, fy * 0.5f);
        particle->move();
    }
    for (auto particle = particles_y.begin(); particle != particles_y.end(); particle++) {
        float fx = 0, fy = 0;
        float dx = pos.x - particle->getX();
        float dy = pos.y - particle->getY();
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared > 0 && distanceSquared < radius * radius) {
            float distance = std::sqrtf(distanceSquared);
            float F = force / distance;

            fx += F * dx;
            fy += F * dy;
        }
        particle->push(fx * 0.5f, fy * 0.5f);
        particle->move();
    }
}

void SimulationEngine::clear() {
    particles_r.clear();
    particles_g.clear();
    particles_b.clear();
    particles_y.clear();
}

void SimulationEngine::createParticle(Particle particle) {
    if (particle.getType() == ParticleType::RED) {
        particles_r.push_back(particle);
    }
    else if (particle.getType() == ParticleType::GREEN) {
        particles_g.push_back(particle);
    }
    else if (particle.getType() == ParticleType::CYAN) {
        particles_b.push_back(particle);
    }
    else {
        particles_y.push_back(particle);
    }
}

SimulationEngine::SimulationEngine() {
    generateNewRules();
    generateNewParticles();
}
