#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "../include/Board.hpp"

#define FRAME_DURATION 16667

//Por enquanto, pra compilar essa bosta tu executa isso
//g++ main.cpp Board.cpp EmptyTile.cpp BombTile.cpp -lsfml-graphics -lsfml-window -lsfml-system

int main() {
    //Pretendo passar toda essa lógica da main para a classe Game, só não sei como ainda

    Board field(16, 16);
    field.initialize(30);

    //unsigned delay = 0;

    //std::chrono::time_point<std::chrono::steady_clock> previousTime;

    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * field.getCols() * SCREEN_RESIZE, TILE_SIZE * field.getRows() * SCREEN_RESIZE), "Campo Minado"); //Configurações da janela
    window.setView(sf::View(sf::FloatRect(0, 0, TILE_SIZE * field.getCols(),  TILE_SIZE * field.getRows())));

    //previousTime = std::chrono::steady_clock::now();

    while (window.isOpen()) { //Enquanto a janela está aberta
        sf::Event event;

        //unsigned lag = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime).count();
        //delay += lag;
        //previousTime += std::chrono::microseconds(lag);

        while (window.pollEvent(event)) //Se ocorre um evento...
        {
            switch (event.type) //Tratamento diferente para cada tipo de evento
            {
               case sf::Event::Closed: //Janela fechada
               {
                    if (event.type == sf::Event::Closed) window.close();
                    break;
               }
               
               case sf::Event::KeyReleased: //Tecla pressionada
               {

               }

               case sf::Event::MouseButtonReleased: //Botão do mouse pressionado
               {
                    //Recebe posição do mouse e arredonda para descobrir sobre qual tile está
                    int mouseTileX = sf::Mouse::getPosition(window).x / TILE_SIZE / SCREEN_RESIZE;
                    int mouseTileY = sf::Mouse::getPosition(window).y / TILE_SIZE / SCREEN_RESIZE;

                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left: //Botão esquerdo
                        {
                            cout << "tile clicado: x - " << mouseTileX << " y - " << mouseTileY << endl;
                            field.revealTile(mouseTileY, mouseTileX);
                        }
                        
                        case sf::Mouse::Right: //Botão direito
                        {

                        }
                    }
                }
            } 
        }

        window.clear();
        field.draw(window);
        window.display();
    }

    return 0;
}