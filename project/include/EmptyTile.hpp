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

        string display() const override;
        void draw(sf::RenderWindow& window, float posX, float posY) const override;

        //Getters
        int getAdjacentBombs() { return adjacentBombs; }

        //Setters
        void setAdjacentBombs(int bombs) { adjacentBombs = bombs; }
};