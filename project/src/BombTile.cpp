#include <SFML/Graphics.hpp>
#include "../include/BombTile.hpp"

string BombTile::display() const {
    return revealed ? "*" : (flagged ? "F" : ".");
}

void BombTile::draw(sf::RenderWindow& window, float posX, float posY) const {
    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
    shape.setPosition(posX, posY);
    shape.setFillColor(revealed ? sf::Color::Red : sf::Color::Blue);
    window.draw(shape);

    if (flagged) {
        sf::Font font;
        font.loadFromFile("../assets/fonts/RobotoCondensed-Regular.ttf"); //Carrega a fonte
        sf::Text text("F", font, 14);
        text.setPosition(sf::Vector2f(posX, posY));
        window.draw(text);
    }
}