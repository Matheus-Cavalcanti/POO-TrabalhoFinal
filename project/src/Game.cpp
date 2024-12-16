#include <iostream>
#include <random>
#include "../include/Board.hpp"
#include "../include/EmptyTile.hpp"
#include "../include/BombTile.hpp"
#include "../include/Game.hpp"

void Game::flagInteraction(int row, int col) {
    if(row < 0 || row >= board.getRows() || col < 0 || col >= board.getCols()){ // se estiver fora do tabuleiro ja criado
        return;
    }

    // Os testes estao todos em if pra caso eu tenha esquecido de alguma possibilidade
    shared_ptr<Tile> tilePtr = board.getTile(row, col);
    if(tilePtr->isRevealed()) {
        return;
    }

    // Tile ja possui uma flag. Interacao de remocao da flag
    if(tilePtr->isFlagged()) {
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags--;

        availableFlags++;
        tilePtr->setFlag(false);
        return;
    }

    // Tile nao possui flag. Interacao de colocar flag
    if(!tilePtr->isFlagged()) {
        if(availableFlags == 0) return;
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags++;

        availableFlags--;
        tilePtr->setFlag(true);
        return;
    }

    return;
}