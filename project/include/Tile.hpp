#pragma once //Proteção de múltipla inclusão
#include <string>

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
        int getX() { return x; }
        int getY() { return y; }

        //Setters
        void reveal() { revealed = true; }
        void setFlag(bool value) { flagged = value; }
        void setX(int value) { x = value; }
        void setY(int value) { y = value; }

        virtual string display() const = 0; 
        virtual void draw(sf::RenderWindow& window, float posX, float posY) const = 0; //Método virtual para exibição do tile no tabuleiro
        //Ainda não decidi se essa função vai continuar existindo ou o que vai fazer
};

//Todos os métodos da classe são inline, portanto, não há a necessidade de um arquivo de implementação .cpp
//Além disso, Tile é uma classe abstrata, servindo de base para as classes EmptyTile e BombTile