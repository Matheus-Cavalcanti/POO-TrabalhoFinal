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


        string display() const override {
            return revealed ? (adjacentBombs != 0 ? to_string(adjacentBombs) : "#") : (flagged ? "F" : ".");
        }

        //Getters
        int getAdjacentBombs() { return adjacentBombs; }

        //Setters
        void setAdjacentBombs(int bombs) { adjacentBombs = bombs; }
};

//Todos os métodos da classe são inline, portanto, não há a necessidade de um arquivo de implementação .cpp