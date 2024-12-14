#pragma once
#include "Tile.hpp"

using namespace std;

class BombTile : public Tile
{
    public:
        string display() const override {
            return revealed ? "*" : (flagged ? "F" : ".");
        }

        void draw(sf::RenderWindow& window, float posX, float posY) const override {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
            shape.setPosition(posX, posY);
            shape.setFillColor(revealed ? sf::Color::Red : sf::Color::Blue);
            window.draw(shape);
        }
};

//Todos os métodos da classe são inline, portanto, não há a necessidade de um arquivo de implementação .cpp
