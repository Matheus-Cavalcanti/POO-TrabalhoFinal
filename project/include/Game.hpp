#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hpp"
#include <chrono>
#include "Player.hpp"
#include "File.hpp"

class Game {

    private:
        Board field;
        sf::RenderWindow window;
        int rows, cols, bombs;
        int revealedCount = 0; // Contador de tiles revelados
        sf::Time time_ref;
        int again;

        unsigned int availableFlags;
        unsigned int correctFlags;

        enum GameState {
            MainMenu,
            DifficultyMenu,
            Playing,
            Exit
        };

        GameState state = MainMenu;

        void Events();

        void event_Mouse_Click(const sf::Event::MouseButtonEvent& mouseButton);

        int check_WL();

        void render_map();

        //Funções do menu
        int mainMenu();           //Exibe o menu principal
        int difficultyMenu();     //Exibe o menu de escolha de dificuldade
        int displayScores();
        int displayInstructions();

    public:
    /*
        Game(int rows, int cols, int bombs) : field(rows, cols), rows(rows), cols(cols), bombs(bombs), availableFlags(bombs), correctFlags(0) {
            window(sf::VideoMode(TILE_SIZE * cols * SCREEN_RESIZE, TILE_SIZE * rows * SCREEN_RESIZE), "Campo Minado"){
            window.setView(sf::View(sf::FloatRect(0, 0, TILE_SIZE * cols, TILE_SIZE * rows)));
            field.initialize(bombs);
        }
    */

        Game() : field(8, 8), rows(8), cols(8), bombs(10), availableFlags(10), correctFlags(0), again(0) {
            window.create(sf::VideoMode(800, 600), "Campo Minado");
        }

        ~Game() {};

        void reset();

        void initialize(int rows, int cols, int bombs);

        std::string getDifficulty(int difficulty);

        // Função que vai ler a entrada após o fim do jogo
        void read_after_game();

        void run();

        void flagInteraction(int row, int col);

        void gridChange(int row, int col); //Muda a posição de uma bomba. Chamada apenas se o primeiro clique for em uma bomba.

        int test_again() { return again; }

        void set_again(int value) { again = value; }
};
