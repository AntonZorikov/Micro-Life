#include "Particle.h"

sf::RenderWindow* Particle::window = nullptr;
float Particle::size = 0.0f;
sf::CircleShape Particle::shape;

sf::Color Particle::rcolor = sf::Color(255, 0, 0);
sf::Color Particle::gcolor = sf::Color(0, 255, 0);
sf::Color Particle::bcolor = sf::Color(255, 255, 0);
sf::Color Particle::ycolor = sf::Color(0, 255, 255);

void Particle::setWindow(sf::RenderWindow* window_) {
    window = window_;
}

int Particle::getX() const {
    return x;
}

int Particle::getY() const {
    return y;
}

float Particle::getXVelocity() {
    return xVelocity;
}

float Particle::getYVelocity() {
    return yVelocity;
}

void Particle::setXVelocity(float vel) {
    xVelocity = vel;
}

void Particle::setYVelocity(float vel) {
    yVelocity = vel;
}

ParticleType Particle::getType() {
    return type;
}

void Particle::push(float offsetX, float offsetY) {
    xVelocity += offsetX;
    yVelocity += offsetY;
}

void Particle::move() {
    x += xVelocity;
    y += yVelocity;
    xVelocity *= 0.6;
    yVelocity *= 0.6;

    if (x <= 0) {
        x = 0;
        xVelocity = 1;
    }
    else if (x >= window->getSize().x) {
        x = window->getSize().x;
        xVelocity = -1;
    }
    if (y <= 0) {
        y = 0;
        yVelocity = 1;
    }
    else if (y >= window->getSize().y) {
        y = window->getSize().y;
        yVelocity = -1;
    }
}

void Particle::draw() {
    if (type == ParticleType::RED) color = rcolor;
    else if (type == ParticleType::GREEN) color = gcolor;
    else if (type == ParticleType::CYAN) color = bcolor;
    else if (type == ParticleType::YELLOW) color = ycolor;

    shape.setRadius(size);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    window->draw(shape);
}

Particle::Particle(ParticleType type_, int x_, int y_) : x(x_), y(y_) {
    type = type_;
}
