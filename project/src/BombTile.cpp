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
        sf::Texture tex;
        tex.loadFromFile("../assets/images/flag_sprite.png"); //Carrega a imagem

        sf::Sprite sprite;
        sprite.setTexture(tex);
        sprite.setPosition(posX, posY);
        sprite.scale(0.03, 0.03);
        sprite.setOrigin(0.5, 0.5);

        window.draw(sprite);
    }
}