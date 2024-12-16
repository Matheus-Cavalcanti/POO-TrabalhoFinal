#pragma once
#include <string>

using namespace std;

class Player {
    string name;
    int score;

public:
    Player(const string& name) : name(name), score(0) {}
    Player() : score(0), name("") {}

    void addScore(int points) { score += points; }
    void addName(std::string t_name){ name = t_name;}
    int getScore() const { return score; }

    string getName() const { return name; }
    
};
