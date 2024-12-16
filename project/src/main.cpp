#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "../include/Board.hpp"
#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include <fstream>

#define FRAME_DURATION 16667

//Por enquanto, pra compilar essa bosta tu executa isso
//g++ main.cpp Board.cpp EmptyTile.cpp BombTile.cpp Game.cpp  -lsfml-graphics -lsfml-window -lsfml-system

int main(){
    Game game(16, 16, 30); // fazer coisas de dificuldade dentro aq
    game.run();            // roda tudo, temos que fazer jogo e tabuleiro rodando 2 coisas distintas
    return 0;
}