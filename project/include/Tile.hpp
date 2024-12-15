#pragma once //Proteção de múltipla inclusão
#include <string>

#define TILE_SIZE 16

using namespace std;

class Tile
{
    protected:
        bool revealed;
        bool flagged;
        int x;
        int y;

    public:
        Tile() : revealed(false), flagged(false) {} //Construtor
        virtual ~Tile() {} //Destrutor

        //Getters
        bool isRevealed() const { return revealed; }
        bool isFlagged() const { return flagged; }
        int getX() const { return x; }
        int getY() const { return y; }

        //Setters
        void reveal() { revealed = true; }
        void setFlag(bool value) { flagged = value; }
        void setX(int value) { x = value; }
        void setY(int value) { y = value; }

        virtual string display() const = 0; 
        virtual void draw(sf::RenderWindow& window, float posX, float posY) const = 0; //Método virtual para exibição do tile no tabuleiro
};

//Todos os métodos da classe são inline, portanto, não há a necessidade de um arquivo de implementação .cpp
//Além disso, Tile é uma classe abstrata, servindo de base para as classes EmptyTile e BombTile