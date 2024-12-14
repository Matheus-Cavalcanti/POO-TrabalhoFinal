#pragma once
#include "Board.hpp"

using namespace std;

class PowerUp
{
    public:
        virtual void activate(Board& board) = 0; //Método virtual puro
        virtual ~PowerUp() {}
    };

    class RevealBomb : public PowerUp {
    public:
        void activate(Board& board) override;
};
