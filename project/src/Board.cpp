#include <iostream>
#include <random>
#include "../include/Board.hpp"
#include "../include/EmptyTile.hpp"
#include "../include/BombTile.hpp"

#define DEBUG 1

using namespace std;

void Board::initialize(int numBombs) //Gera posições aleatórias para as bombas
{
    int totalTiles = rows * cols;

    vector<int> positions(totalTiles);
    for (int i = 0; i < totalTiles; ++i) positions[i] = i;

    //Embaralha as posições para distribuir as bombas
    random_device rd; //Fonte de números aleatórios
    mt19937 g(rd());  //Gerador de números
    shuffle(positions.begin(), positions.end(), g);

    //Coloca as bombas no campo
    for (int i = 0; i < numBombs; ++i) {
        int pos = positions[i];
        int row = pos / cols;
        int col = pos % cols;
        grid[row][col] = make_shared<BombTile>();
    }

    //Preenche os tiles restantes como EmptyTile
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!grid[i][j]) {
                grid[i][j] = make_shared<EmptyTile>(); //Inicializa sem bombas adjacentes
            }
        }
    }

    #if DEBUG
    this->displayBoard();
    #endif

    //Calcula as bombas adjacentes para cada EmptyTile
    calculateAdjacentBombs();

    #if DEBUG
    this->displayBoard();
    #endif
}

void Board::calculateAdjacentBombs() {
    const int directions[8][2] = {    //Posições relativas de tiles ao redor de um tile qualquer
        {-1, -1}, {-1, 0},{-1, 1},    //Superior esquerdo, cima, superior direito
        {0,  -1},         {0,  1},    //Esquerda, direita
        {1,  -1}, {1,  0},{1,  1}     //Inferior esquerdo, baixo, inferior direito
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //Verifica se é um EmptyTile
            if (dynamic_pointer_cast<EmptyTile>(grid[i][j])) {
                int bombCount = 0;

                //Verifica todas as direções
                for (const auto& dir : directions) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];

                    //Verifica se a posição vizinha está dentro dos limites e contém uma bomba
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        if (dynamic_pointer_cast<BombTile>(grid[ni][nj])) {
                            ++bombCount;
                        }
                    }
                }

                //Atualiza o número de bombas adjacentes no EmptyTile
                auto emptyTile = dynamic_pointer_cast<EmptyTile>(grid[i][j]);
                emptyTile->setAdjacentBombs(bombCount);
            }
        }
    }
}

void Board::displayBoard() const {
    for (const auto& row : grid) {
        for (const auto& tile : row) {
            //tile->reveal();
            cout << tile->display() << " ";
        }
        cout << std::endl;
    }
}

void Board::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //grid[i][j]->reveal();
            grid[i][j]->draw(window, j * TILE_SIZE, i * TILE_SIZE);
        }
    }
}

void Board::revealTile(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col]->isRevealed()) {
        return;
    }

    grid[row][col]->reveal();
}