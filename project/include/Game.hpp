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
        int displayScores();     //Exibição de scores
        int displayInstructions();


    public:
    /*
        Game(int rows, int cols, int bombs) : field(rows, cols), rows(rows), cols(cols), bombs(bombs), availableFlags(bombs), correctFlags(0) {
            window(sf::VideoMode(TILE_SIZE * cols * SCREEN_RESIZE, TILE_SIZE * rows * SCREEN_RESIZE), "Campo Minado"){
            window.setView(sf::View(sf::FloatRect(0, 0, TILE_SIZE * cols, TILE_SIZE * rows)));
            field.initialize(bombs);
        }
    */

        Game() : field(8, 8), rows(8), cols(8), bombs(10), availableFlags(10), correctFlags(0) {
            window.create(sf::VideoMode(800, 600), "Campo Minado");
        }

        void initialize(int rows, int cols, int bombs) {
            this->rows = rows;
            this->cols = cols;
            this->bombs = bombs;
            this->availableFlags = bombs;
            this->correctFlags = 0;
            this->revealedCount = 0;

            field = Board(rows, cols);
            field.initialize(bombs);

            window.create(sf::VideoMode(cols * TILE_SIZE * SCREEN_RESIZE, (rows+1) * TILE_SIZE * SCREEN_RESIZE), "Campo Minado");
            window.setView(sf::View(sf::FloatRect(0, 0, TILE_SIZE * cols, TILE_SIZE * (rows+1))));
        }

        std::string getDifficulty(int difficulty) {
            if (difficulty == 0) {
                return "easy";
            } else if (difficulty == 1) {
                return "medium";
            } else if (difficulty == 2) {
                return "hard";
            } else {
                return "Invalid difficulty"; // Caso o valor seja fora de 0, 1 ou 2
            }
        }

        // Função que vai ler a entrada após o fim do jogo
    void read_after_game(){
        sf::Event event;
        bool validInput= false;
        while(!validInput && window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    window.close();
                }
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::R){
                        std::cout << "Reiniciando o jogo..." << std::endl;
                        state = DifficultyMenu;
                        validInput = true;
                    }
                    else if(event.key.code == sf::Keyboard::M){
                        std::cout << "Voltando ao menu principal..." << std::endl;
                        state = MainMenu;
                        validInput = true;
                    }
                }
            }
        }
    }

        void run() {
            int difficulty;
            int ganhou=0;
            while (window.isOpen()) {
                window.clear();
                if (state == MainMenu) {
                    int choice = mainMenu();
                    if (choice == 0) {
                        state = DifficultyMenu;
                    } else if (choice == 1) {
                        displayInstructions();
                    } else if (choice == 2) {
                        displayScores();
                    } else if (choice == 3) {
                        state = Exit;
                    }
                } else if (state == DifficultyMenu) {
                    difficulty = difficultyMenu();
                    if (difficulty == 0) {
                        initialize(8, 8, 10); //Fácil
                        state = Playing;
                    } else if (difficulty == 1) {
                        initialize(16, 16, 40); //Médio
                        state = Playing;
                    } else if (difficulty == 2) {
                        initialize(24, 24, 99); //Difícil
                        state = Playing;
                    } else {
                        state = MainMenu;
                    }
                } else if (state == Playing) {
                    auto start = std::chrono::high_resolution_clock::now();


                    time_ref = sf::seconds(0);
                    Player player("adm");
                    sf::Clock clock;
                    while (state == Playing && window.isOpen() && ganhou==0) {
                        time_ref = clock.getElapsedTime();
                        Events();
                        ganhou= check_WL();
                        render_map();

                    }
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
                    player.addScore(duration);
                    field.revealAllBombs();
                    render_map();
                    writeScoreToFile(getDifficulty(difficulty), player);
                    read_after_game();

                } else if (state == Exit) {
                    window.close();
                }
            }
        }

        void flagInteraction(int row, int col);

        void gridChange(int row, int col); //Muda a posição de uma bomba. Chamada apenas se o primeiro clique for em uma bomba.
        
};
