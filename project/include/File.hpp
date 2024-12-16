#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Player.hpp"
#include <sstream>
#include <algorithm>

void open_file();

void writeScoreToFile(const std::string& difficulty, const Player& player);