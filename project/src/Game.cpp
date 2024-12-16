#include <random>
#include "../include/Board.hpp"
#include "../include/EmptyTile.hpp"
#include "../include/BombTile.hpp"
#include "../include/Game.hpp"

void Game::Events(){
	sf::Event event;
    while(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonReleased:
                event_Mouse_Click(event.mouseButton);
                break;

            default:
                break;
        }
    }    
} 

void Game::event_Mouse_Click(const sf::Event::MouseButtonEvent &mouseButton){

    
    int mouseTileX = sf::Mouse::getPosition(window).x / TILE_SIZE / SCREEN_RESIZE;
    int mouseTileY = sf::Mouse::getPosition(window).y / TILE_SIZE / SCREEN_RESIZE;

    if (mouseTileX < 0 || mouseTileX >= cols || mouseTileY < 0 || mouseTileY >= rows) return;

    switch (mouseButton.button){
        case sf::Mouse::Left:
            field.revealTile(mouseTileY, mouseTileX, revealedCount);
            break;

        case sf::Mouse::Right:
            this->flagInteraction(mouseTileY, mouseTileX);
        	break;

        default:
            break;
        }
}

void Game::check_WL()
{
    if(revealedCount==(rows * cols - bombs) || correctFlags == bombs){
        std::cout<< "DEBBUG SUCESSO\n";
        window.close();
    } 
    else if(revealedCount == -1){
        std::cout << "DEBBUG DERROTA\n";
        window.close();
    }
}

void Game::render_map()
{
    window.clear();
    field.draw(window);
    window.display();
}

void Game::flagInteraction(int row, int col) {
    if(row < 0 || row >= field.getRows() || col < 0 || col >= field.getCols()){ // se estiver fora do tabuleiro ja criado
        return;
    }

    // Os testes estao todos em if pra caso eu tenha esquecido de alguma possibilidade
    shared_ptr<Tile> tilePtr = field.getTile(row, col);
    if(tilePtr->isRevealed()) {
        cout << "ja revelado\n";
        return;
    }

    // Tile ja possui uma flag. Interacao de remocao da flag
    if(tilePtr->isFlagged()) {
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags--;

        cout << "remocao\n";

        availableFlags++;
        tilePtr->setFlag(false);
        return;
    }

    // Tile nao possui flag. Interacao de colocar flag
    if(!(tilePtr->isFlagged())) {

        cout << "nova flag\n";
        if(availableFlags == 0) return;
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags++;

        availableFlags--;
        tilePtr->setFlag(true);
        return;
    }

    return;
}