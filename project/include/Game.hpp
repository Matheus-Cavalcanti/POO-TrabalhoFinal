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
        Player player;
        sf::RenderWindow window;
        int rows, cols, bombs;
        int revealedCount = 0;          //Contador de tiles revelados
        sf::Time time_ref;              //Tempo decorrido em cada partida
        int again;                      //Atributo determina se o jogador deseja jogar novamente (loop de jogo).

        unsigned int availableFlags;    //Flags disponíveis para serem posicionadas.
        unsigned int correctFlags;      //Flags em posições de bombas

        //Estados de jogo
        enum GameState {
            MainMenu,
            DifficultyMenu,
            Playing,
            Exit,
            NameMenu
        };

        GameState state = MainMenu;
    public:

        //Construtor
        Game() : field(8, 8), rows(8), cols(8), bombs(10), availableFlags(10), correctFlags(0), again(0) {
            window.create(sf::VideoMode(800, 600), "Campo Minado");
        }

        //Destruidor
        ~Game() {};

        //Inicializa o jogo
        void initialize(int rows, int cols, int bombs);

        // Função que vai ler a entrada após o fim do jogo
        void read_after_game();

        //Fluxo de jogo
        void run();

        //Interações de posicionamento de flag
        void flagInteraction(int row, int col);

        //Mudanças na matriz de Tiles
        void gridChange(int row, int col); //Muda a posição de uma bomba. Chamada apenas se o primeiro clique for em uma bomba.

        //Getter
        int test_again() { return again; }

        //Setter
        void set_again(int value) { again = value; }

        //Lida com os eventos de interação do usuário
        void Events();
        //Eventos de clique de mouse (revelar ou bandeira)
        void event_Mouse_Click(const sf::Event::MouseButtonEvent& mouseButton);
        //Verifica se o jogo terminou (derrota ou vitoria)
        int check_WL();
        //Renderiza o mapa
        void render_map();

        //Funções do menu
        int mainMenu();             //Exibe o menu principal
        int difficultyMenu();       //Exibe o menu de escolha de dificuldade
        int nameMenu();             //Recolhe as informações de nome do jogador
        int displayScores();        //Exibe os Scores
        int displayInstructions();  //Exibe as instruções de jogo
};
