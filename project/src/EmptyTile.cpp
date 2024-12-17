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
        font.loadFromFile("../assets/fonts/Oswald-Bold.ttf"); //Carrega a fonte
        sf::Text text(to_string(adjacentBombs), font, 9);
        text.setPosition((int)posX+2.5, (int)posY-1); //Ajusta posição do texto
        text.setFillColor(number_color(adjacentBombs));
        window.draw(text);
    }

    if (flagged) {
        sf::Texture tex;
        tex.loadFromFile("../assets/images/flag_sprite.png"); //Carrega a imagem

        sf::Sprite sprite;
        sprite.setTexture(tex);
        sprite.setPosition(posX, posY);
        sprite.scale(0.02, 0.02);
        sprite.setOrigin(0.5, 0.5);

        window.draw(sprite);
    }
}

sf::Color EmptyTile::number_color(int number) const{ // especificacao igual ao do jogo original
    switch (number) {
        case 1: 
            return sf::Color::Blue;
        case 2: 
            return sf::Color::Green;
        case 3: 
            return sf::Color::Red;
        case 4: 
            return sf::Color(107, 63, 160); //roxo
        case 5: 
            return sf::Color(75, 54, 33); // Marrom
        case 6: 
            return sf::Color::Cyan;
        case 7: 
            return sf::Color::Black;
        case 8: 
            return sf::Color(128, 128, 128); // Cinza
        default: 
            return sf::Color::Black;
    }
}