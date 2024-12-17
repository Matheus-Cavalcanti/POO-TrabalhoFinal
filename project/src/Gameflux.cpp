//Define o fluxo de jogo
#include "../include/Game.hpp"

void Game::run() {
    int difficulty;
    int ganhou=0;
    while (window.isOpen()) {
        window.clear();
        //Enquanto o estado do objeto for de Main menu
        if (state == MainMenu) {
            //mainMenu() retorna a escolha do jogador. Direciona para o outros menus.
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
            //difficultyMenu() retorn a escolha de difculdade. Jogo é inicializado para cada dificuldade
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
        //Caso o jogador já esteja jogando
        } else if (state == Playing) {
            //Medida de tempo de jogo
            auto start = std::chrono::high_resolution_clock::now();

            time_ref = sf::seconds(0);
            Player player("adm");
            sf::Clock clock;

            //Chamada das funções de comportamento do jogador durante o jogo (Events());
            while (state == Playing && window.isOpen() && ganhou==0) {
                //Tempo do cronômetro
                time_ref = clock.getElapsedTime();
                //Avalia comportamento do jogador
                Events();
                //Verifica se o jogo acabou
                ganhou= check_WL();
                //Renderiza o mapa
                render_map();

            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
            //Adiciona o score para o jogador
            player.addScore(duration);
            //Revela as bombas
            field.revealAllBombs();
            render_map();
            //Salva o score
            writeScoreToFile(getDifficulty(difficulty), player);
            read_after_game();
            window.close();
            return;

        //Estado de saída
        } else if (state == Exit) {
            window.close();
            return;
        }
    }
}

//Avalia interações após o final do jogo
void Game::read_after_game(){
    sf::Event event;
    bool validInput= false;
    while(!validInput && window.isOpen()){
        while(window.pollEvent(event)){
            //Evento de fechamento da janela
            if(event.type == sf::Event::Closed){
                window.close();
            }
            //Evento de retorno para o menu (botão M)
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::M){
                    set_again(1);
                    return;
                }
                else return;
            }
        }
    }
}

//Verifica fim de jogo
int Game::check_WL()
{
    //Vitória
    if(revealedCount==(rows * cols - bombs) || correctFlags == bombs){
        return 1;
    } 
    //Derrota
    else if(revealedCount == -1){
        return -1;
    }
    return 0;
}