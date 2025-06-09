#pragma once
#include "Tile.hpp"

using namespace std;

//Classe derivada para os Tiles livres
class EmptyTile : public Tile
{
    private:
        int adjacentBombs; //Contagem das bombas imediatamente ao lado ou na diagonal.

    public:
        EmptyTile() : adjacentBombs(0) {} //Construtor
        virtual ~EmptyTile() {} //Destrutor

        void draw(sf::RenderWindow& window, float posX, float posY) const override; //Exibição gráfica

        sf::Color number_color(int number) const; //Retorna a cor de cada número

        //Getters
        int getAdjacentBombs() { return adjacentBombs; }

        //Setters
        void setAdjacentBombs(int bombs) { adjacentBombs = bombs; }
};