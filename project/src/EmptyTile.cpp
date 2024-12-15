#include <SFML/Graphics.hpp>
#include "../include/EmptyTile.hpp"

string EmptyTile::display() const {
    return revealed ? (adjacentBombs != 0 ? to_string(adjacentBombs) : "#") : (flagged ? "F" : ".");
}

void EmptyTile::draw(sf::RenderWindow& window, float posX, float posY) const {
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