#include <SFML/Graphics.hpp>
#include "../include/BombTile.hpp"

//Exibição em ascii
string BombTile::display() const {
    return revealed ? "*" : (flagged ? "F" : ".");
}

//Exibição gráfica
void BombTile::draw(sf::RenderWindow& window, float posX, float posY) const {
    //Quadradinho
    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
    shape.setPosition(posX, posY);
    shape.setFillColor(revealed ? sf::Color::Red : sf::Color::Blue);
    window.draw(shape);

    //Exibição caso o tile tenha uma bandeira, exibe a flag da bandeira
    if (flagged) {
        sf::Texture tex;
        tex.loadFromFile("../assets/images/flag_sprite.png"); //Carrega a imagem

        sf::Sprite sprite;
        sprite.setTexture(tex);
        sprite.setPosition(posX, posY); //Ajusta a posição
        sprite.scale(0.02, 0.02); //Ajusta a escala
        sprite.setOrigin(0.5, 0.5);

        window.draw(sprite);
    }

    //Exibição caso o tile seja clicado (no final do jogo, todas as bombas são mostradas).
    else if (revealed) {
        sf::Texture tex;
        tex.loadFromFile("../assets/images/bomb_sprite.png"); //Carrega a imagem

        sf::Sprite sprite;
        sprite.setTexture(tex);
        sprite.setPosition(posX, posY); //Ajusta a posição
        sprite.scale(0.02, 0.02); //Ajusta a escala
        sprite.setOrigin(0.5, 0.5);

        window.draw(sprite);
    }
}