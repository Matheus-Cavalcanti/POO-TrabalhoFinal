#pragma once
#include "Tile.hpp"

using namespace std;

//Classe derivada de Tile, representa espaços com bomba.
class BombTile : public Tile
{
    public:
        BombTile() {} //Construtor
        virtual ~BombTile() {} //Destrutor

        string display() const override; //Exibe em ascii (DEBUG).
        void draw(sf::RenderWindow& window, float posX, float posY) const override; //Exibe graficamente os espaços com bombas (revelado ou não)
};
