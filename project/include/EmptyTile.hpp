#pragma once
#include "Tile.hpp"

using namespace std;

class EmptyTile : public Tile
{
    private:
        int adjacentBombs;

    public:
        EmptyTile() : adjacentBombs(0) {} //Construtor
        virtual ~EmptyTile() {} //Destrutor


        string display() const override {
            return revealed ? (adjacentBombs != 0 ? to_string(adjacentBombs) : "#") : (flagged ? "F" : ".");
        }

        void draw(sf::RenderWindow& window, float posX, float posY) const override {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
            shape.setPosition(posX, posY);
            shape.setFillColor(revealed ? sf::Color::White : sf::Color::Blue);
            window.draw(shape);

            if (revealed && adjacentBombs > 0) {
                sf::Font font;
                font.loadFromFile("../assets/fonts/RobotoCondensed-Regular.ttf"); //Carrega a fonte
                sf::Text text(to_string(adjacentBombs), font, 14);
                text.setPosition(sf::Vector2f(posX, posY)); //Ajusta posição do texto
                text.setFillColor(sf::Color::Black); //Cor do texto
                window.draw(text);
            }
    }

        //Getters
        int getAdjacentBombs() { return adjacentBombs; }

        //Setters
        void setAdjacentBombs(int bombs) { adjacentBombs = bombs; }
};

//Todos os métodos da classe são inline, portanto, não há a necessidade de um arquivo de implementação .cpp