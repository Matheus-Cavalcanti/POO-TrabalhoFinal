#include <iostream>
#include <random>
#include "../include/Board.hpp"
#include "../include/EmptyTile.hpp"
#include "../include/BombTile.hpp"
#include "../include/Game.hpp"

#define DEBUG 0

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

//Exibição em ascii
void Board::displayBoard() const {
    for (const auto& row : grid) {
        for (const auto& tile : row) {
            //tile->reveal();
            cout << tile->display() << " ";
        }
        cout << std::endl;
    }
}

//Exibição gráfica
void Board::draw(sf::RenderWindow& window)
{
    //Opera desenhando cada tile.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j]->draw(window, j * TILE_SIZE, i * TILE_SIZE);
        }
    }
}

//Revela todas as bombas
void Board::revealAllBombs() {
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            //Testa se o tile é bomba
            if (grid[i][j] && dynamic_pointer_cast<BombTile>(grid[i][j])){
                grid[i][j]->reveal();
            }
        }
    }
}

//Revela um Tile específico
void Board::revealTile(int row, int col, int &revealed_Count)
{
    if(row < 0 || row >= rows || col < 0 || col >= cols){ //Caso esteja fora do tabuleiro ja criado
        return;
    }

    // Se ja foi revelado entao nao o acessa de novo pois ja esta na recursao
    if(grid[row][col]->isRevealed()){
        return;
    }

    //Pula se estiver flagged
    if(grid[row][col]->isFlagged()) {
        return;
    }

    //Revela para o jogador caso contrario
    grid[row][col]->reveal();
    revealed_Count++;

    auto emptyTile= dynamic_pointer_cast<EmptyTile>(grid[row][col]);
    if(emptyTile){ //Se for numero ou espaco vazio
        if(emptyTile->getAdjacentBombs()> 0){ //Se for numero (quadrado com bombas adjacentes)
            return;
        }
        else{ // É um quadrado sem bombas adjacentes, "em branco".
            for(int i= -1; i<= 1; i++){
                for(int j= -1;j<= 1; j++){
                    if(i != 0 || j != 0){ // Caso não seja o mesmo quadrado
                        revealTile(row + i, col + j, revealed_Count);
                    }
                }
            }
        }
    }
    else{ //É bomba, interrompe a recursao. Você morreu
        revealed_Count=-1; //Acaba o jogo com derrota
        return;
    }
}

// Muda o valor de tile na grid
// Type 1: Quadrado vazio
// Type 2(else): Bomba
void Board::setTile(int row, int col, int type) {
    if(type == 1) {
        grid[row][col] = make_shared<EmptyTile>();
    }
    else {
        grid[row][col] = make_shared<BombTile>();
    }
    return;
}