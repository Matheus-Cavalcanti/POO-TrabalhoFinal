#pragma once
#include "Board.hpp"
#include "Player.hpp"

using namespace std;

class Game
{
    private:
        Board board;
        Player player;
        enum Dificculty {easy = 1, medium = 2, hard = 3};
        bool gameOver;
        unsigned int availableFlags;
        unsigned int correctFlags;

    public:
        Game(int rows, int cols, const string& playerName);
        void play(); //Gerencia o loop principal do jogo
        void flagInteraction(int row, int col);
};
