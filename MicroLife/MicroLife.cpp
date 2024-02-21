#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <iostream>
#include <thread>


const int windowWidth = 1200, windowHeight = 800;

enum CellType {
    RED,
    GREEN,
    CYAN,
    YELLOW
};

void drawCircle(sf::RenderWindow& window, int x, int y, float size, sf::Color color) {
    sf::CircleShape shape(size);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    window.draw(shape);
}


class Cell {
private:
    static sf::RenderWindow* window;
    static float size;
    static sf::CircleShape shape;

    float x, y, xVelocity = 0, yVelocity = 0;
    CellType type;
    sf::Color color;

public:
    static void setWindow(sf::RenderWindow* window_) {
        window = window_;
    }

    static void setSize(float size_) {
        size = size_;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    float getXVelocity() {
        return xVelocity;
    }

    float getYVelocity() {
        return yVelocity;
    }

    void setXVelocity(float vel) {
        xVelocity = vel;
    }

    void setYVelocity(float vel) {
        yVelocity = vel;
    }

    CellType getType() {
        return type;
    }

    void push(float offcetX, float offcetY) {
        xVelocity += offcetX;
        yVelocity += offcetY;
    }

    void move() {
        x += xVelocity;
        y += yVelocity;
        xVelocity *= 0.6;
        yVelocity *= 0.6;

        if (x <= 0) {
            x = 0;
            xVelocity = 1;
        }
        else if (x >= windowWidth) {
            x = windowWidth;
            xVelocity = -1;
        }
        if (y <= 0) {
            y = 0;
            yVelocity = 1;
        }
        else if (y >= windowHeight) {
            y = windowHeight;
            yVelocity = -1;
        }
    }

    void draw() {
        shape.setPosition(x, y);
        shape.setFillColor(color);
        window->draw(shape);
    }

    Cell(CellType type_, int x_, int y_) : x(x_), y(y_) {
        shape.setRadius(size);
        type = type_;
        if (type == CellType::RED) color = sf::Color::Red;
        else if (type == CellType::GREEN) color = sf::Color::Green;
        else if (type == CellType::CYAN) color = sf::Color::Cyan;
        else if (type == CellType::YELLOW) color = sf::Color::Yellow;
    }
};

sf::RenderWindow* Cell::window = nullptr;
float Cell::size = 0.0f;
sf::CircleShape Cell::shape;

struct Rule {
    float force;
    float radius;
};

class PhysicEngine {
private:
    std::vector<Rule> rules;
public:
    void repelCells(std::vector<Cell>& cells_1, const std::vector<Cell>& cells_2, float force, float radius) {
        for (auto& cell_1 : cells_1) {
            float fx = 0, fy = 0;
            for (const auto& cell_2 : cells_2) {
                float dx = cell_2.getX() - cell_1.getX();
                float dy = cell_2.getY() - cell_1.getY();
                float distanceSquared = dx * dx + dy * dy;

                if (distanceSquared > 0 && distanceSquared < radius * radius) {
                    float distance = std::sqrtf(distanceSquared);
                    float F = force / distance;

                    fx += F * dx;
                    fy += F * dy;
                }
            }
            cell_1.push(fx * 0.5f, fy * 0.5f);
            cell_1.move();
        }
    }


    void clearRule() {
        rules.clear();
    }
};

CellType intToCellType(int i) {
    if (i == 0) {
        return CellType::RED;
    }
    else if (i == 1) {
        return CellType::GREEN;
    }
    else if (i == 2) {
        return CellType::CYAN;
    }
    else if (i == 3) {
        return CellType::YELLOW;
    }
}


int main()
{
    std::srand(std::time(0));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Micro Life");
    Cell::setSize(1);
    Cell::setWindow(&window);
    std::vector<Cell> cells_r;
    std::vector<Cell> cells_g;
    std::vector<Cell> cells_b;
    std::vector<Cell> cells_y;

    PhysicEngine engine;
    Rule forces[4][4];
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {
            forces[i][j].force = ((rand() % 200) - 100) / 200.f;
            forces[i][j].radius = rand() % 300;
        }
    }

    //Rule rule1(intToCellType(0), intToCellType(0), 0.1);
    //Rule rule2(intToCellType(1), intToCellType(0), -0.01);
    //Rule rule3(intToCellType(0), intToCellType(1), 0.01);
    //engine.addRule(rule1);
    //engine.addRule(rule2);
    //engine.addRule(rule3);


    for (unsigned i = 0; i < 2000; i++) {
        CellType type = CellType::CYAN;
        if (rand() % 4 == 0) {
            type = CellType::RED;
            Cell cell(type, rand() % windowWidth, rand() % windowHeight);
            cells_r.push_back(cell);
        }
        else if (rand() % 4 == 1) {
            type = CellType::CYAN;
            Cell cell(type, rand() % windowWidth, rand() % windowHeight);
            cells_r.push_back(cell);
        }
        else if (rand() % 4 == 2) {
            type = CellType::YELLOW;
            Cell cell(type, rand() % windowWidth, rand() % windowHeight);
            cells_r.push_back(cell);
        }
        else {
            type = CellType::GREEN;
            Cell cell(type, rand() % windowWidth, rand() % windowHeight);
            cells_g.push_back(cell);
        }
        /*else if (rand() % 4 == 2) type = CellType::CYAN;
        else if (rand() % 4 == 3) type = CellType::YELLOW;*/

    }

    int tic = 0;
    bool isTic = false;

    while (window.isOpen())
    {
        tic++;
        if (tic >= 10 && isTic) {
            std::cout << tic << std::endl;
            tic = 0;
            forces[rand() % 5][rand() % 5].force = ((rand() % 200) - 100) / 200.f;
            forces[rand() % 5][rand() % 5].radius = rand() % 300;
            std::cout << "!" << std::endl;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                engine.clearRule();
                for (unsigned i = 0; i < 4; i++) {
                    for (unsigned j = 0; j < 4; j++) {
                        forces[i][j].force = ((rand() % 200) - 100) / 200.f;
                        forces[i][j].radius = rand() % 300;

                    }
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                isTic = !isTic;
            }

        }

        for (unsigned i = 0; i < 4; i++) {
            for (unsigned j = 0; j < 4; j++) {
                std::vector<Cell> *c1 = &cells_r;
                std::vector<Cell> *c2 = &cells_r;
                if (i == 0) c1 = &cells_r;
                if (i == 1) c1 = &cells_g;
                if (i == 2) c1 = &cells_b;
                if (i == 3) c1 = &cells_y;

                if (j == 0) c2 = &cells_r;
                if (j == 1) c2 = &cells_g;
                if (j == 2) c2 = &cells_b;
                if (j == 3) c2 = &cells_y;
                engine.repelCells(*c1, *c2, forces[i][j].force, forces[i][j].radius);
            }
        }

        window.clear();
        for (unsigned i = 0; i < cells_r.size(); i++) {
            cells_r[i].draw();
        }
        for (unsigned i = 0; i < cells_g.size(); i++) {
            cells_g[i].draw();
        }
        for (unsigned i = 0; i < cells_b.size(); i++) {
            cells_b[i].draw();
        }
        for (unsigned i = 0; i < cells_y.size(); i++) {
            cells_y[i].draw();
        }
        window.display();

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}