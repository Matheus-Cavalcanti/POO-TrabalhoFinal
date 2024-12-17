#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Player.hpp"
#include <sstream>
#include <algorithm>

//Inicaliza o arquivo de scores
void open_file();

//Guarda uma score no arquivo
void writeScoreToFile(const std::string& difficulty, const Player& player);

//Recebe o valor da dificuldade em inteiro e retorna a string
std::string getDifficulty(int difficulty);