#pragma once

#include <SFML/Graphics.hpp>

enum ParticleType {
    RED,
    GREEN,
    CYAN,
    YELLOW
};

class Particle {
public:
    static float size;
    static sf::CircleShape shape;

    float x, y, xVelocity = 0, yVelocity = 0;
    ParticleType type;
    sf::Color color;

public:
    static sf::RenderWindow* window;

    static void setWindow(sf::RenderWindow* window_);
    static void setSize(float size_);

    int getX() const;
    int getY() const;
    float getXVelocity();
    float getYVelocity();
    void setXVelocity(float vel);
    void setYVelocity(float vel);
    ParticleType getType();
    void push(float offsetX, float offsetY);
    void move();
    void draw();

    Particle(ParticleType type_, int x_, int y_);
};
