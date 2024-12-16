#pragma once
#include <string>

using namespace std;

class Player {
    string name;
    int score;

public:
    Player(const string& name) : name(name), score(0) {}

    void addScore(int points) { score += points; }
    int getScore() const { return score; }

    string getName() const { return name; }
    
};
