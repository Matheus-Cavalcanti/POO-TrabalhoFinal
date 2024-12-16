#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hpp"
#include <chrono>
#include "Player.hpp"

class Game {

    private:
        Board field;
        sf::RenderWindow window;
        int rows, cols, bombs;
        int revealedCount = 0; // Contador de tiles revelados

        unsigned int availableFlags;
        unsigned int correctFlags;


        void Events();

        void event_Mouse_Click(const sf::Event::MouseButtonEvent& mouseButton);

        void check_WL();

        void render_map();
    public:
        Game(int rows, int cols, int bombs) : field(rows, cols), rows(rows), cols(cols), bombs(bombs), availableFlags(bombs), correctFlags(0),
        window(sf::VideoMode(TILE_SIZE * cols * SCREEN_RESIZE, TILE_SIZE * rows * SCREEN_RESIZE), "Campo Minado"){
            window.setView(sf::View(sf::FloatRect(0, 0, TILE_SIZE * cols, TILE_SIZE * rows)));
            field.initialize(bombs);
        }

        void run(){
            auto start = std::chrono::high_resolution_clock::now();
            Player player("adm");
            while (window.isOpen()) {
                Events();
                check_WL();
                render_map();
            }
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end- start).count(); // em segundos para facilitar as coisas
            player.addScore(duration);
            cout << player.getScore();
        }
        void flagInteraction(int row, int col);
};
