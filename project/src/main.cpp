#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "../include/Board.hpp"
#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/File.hpp"

//Por enquanto, pra compilar essa bosta tu executa isso
//g++ main.cpp Board.cpp EmptyTile.cpp BombTile.cpp Game.cpp file.cpp -lsfml-graphics -lsfml-window -lsfml-system

int main(){
    while(1) {
        open_file();
        Game game;
        game.run();

        if(!game.test_again()) break;

    }

    return 0;
}