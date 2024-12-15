#pragma once
#include "Tile.hpp"

using namespace std;

class BombTile : public Tile
{
    public:
        BombTile() {} //Construtor
        virtual ~BombTile() {} //Destrutor

        string display() const override;
        void draw(sf::RenderWindow& window, float posX, float posY) const override;
};
