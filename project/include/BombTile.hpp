#pragma once
#include "Tile.hpp"

using namespace std;

class BombTile : public Tile
{
    public:
        string display() const override {
            return revealed ? "*" : (flagged ? "F" : ".");
        }
};

//Todos os métodos da classe são inline, portanto, não há a necessidade de um arquivo de implementação .cpp
