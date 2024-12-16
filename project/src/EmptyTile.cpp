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
        text.setFillColor(number_color(adjacentBombs));
        window.draw(text);
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