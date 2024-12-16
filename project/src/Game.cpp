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
            
        	break;

        default:
            break;
        }
}

void Game::check_WL()
{
    if(revealedCount==(rows * cols - bombs)){
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