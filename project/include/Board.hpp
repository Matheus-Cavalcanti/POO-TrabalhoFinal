#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

#define SCREEN_RESIZE 4 

using namespace std;

class Board
{
    private:
        int rows;
        int cols;
        vector<vector<shared_ptr<Tile>>> grid; //Matriz de ponteiros para Tile

    public:
        Board(int rows, int cols) : rows(rows), cols(cols) { grid.resize(rows, vector<shared_ptr<Tile>>(cols)); } //Construtor
        virtual ~Board() {}; //Destrutor

        void initialize(int numBombs); //Inicializa os tiles, decidindo quais serão bombas e quais serão vazios
        void revealTile(int row, int col, int& revealed_Count);
        void calculateAdjacentBombs(); //Calcula a quantidade de bombas adjacentes para os tiles vazios
        void displayBoard() const;

        //Getters
        int getRows() const { return rows; }
        int getCols() const { return cols; }
        shared_ptr<Tile> getTile(int row, int col) const { return grid[row][col]; }

        //Setter
        void setTile(int row, int col, int type); //Muda o tipo de tile;
 
        //Funções do SFML
        void draw(sf::RenderWindow& window); //Desenha o tabuleiro

        void revealAllBombs();
};