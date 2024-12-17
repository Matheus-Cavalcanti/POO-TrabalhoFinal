#include <random>
#include <stdio.h>
#include "../include/Board.hpp"
#include "../include/EmptyTile.hpp"
#include "../include/BombTile.hpp"
#include "../include/Game.hpp"

//Inicializa o jogo
void Game::initialize(int rows, int cols, int bombs) {
    this->rows = rows;
    this->cols = cols;
    this->bombs = bombs;
    this->availableFlags = bombs;
    this->correctFlags = 0;
    this->revealedCount = 0;

    //Cria um tabuleiro e inicializa ele
    field = Board(rows, cols);
    field.initialize(bombs);

    //Cria a janela de exibição
    window.create(sf::VideoMode(cols * TILE_SIZE * SCREEN_RESIZE, (rows+1) * TILE_SIZE * SCREEN_RESIZE), "Campo Minado");
    window.setView(sf::View(sf::FloatRect(0, 0, TILE_SIZE * cols, TILE_SIZE * (rows+1))));
}

//Lida com os eventos de interção do jogador
void Game::Events(){
	sf::Event event;

    while(window.pollEvent(event)){
        switch(event.type){
            //Evento de fechamento da janela
            case sf::Event::Closed:
                window.close();
                break;

            //Evento de clique no mouse
            case sf::Event::MouseButtonReleased:
                event_Mouse_Click(event.mouseButton);
                break;
            default:
                break;
        }
    }    
} 

//Lida especificamente com os eventos de clique no mouse
void Game::event_Mouse_Click(const sf::Event::MouseButtonEvent &mouseButton)
{
    //Calcula em qual Tile o mouse está posicionado
    int mouseTileX = sf::Mouse::getPosition(window).x / TILE_SIZE / SCREEN_RESIZE;
    int mouseTileY = sf::Mouse::getPosition(window).y / TILE_SIZE / SCREEN_RESIZE;

    //Verifica se o mouse está nos limites de jogo
    if (mouseTileX < 0 || mouseTileX >= cols || mouseTileY < 0 || mouseTileY >= rows) return;

    switch (mouseButton.button){
        //Ação de revelar quadrado
        case sf::Mouse::Left:
            //Caso o primeiro clique seja sobre uma bomba, muda-se a posição desta
            if(revealedCount == 0 && dynamic_pointer_cast<BombTile>(field.getTile(mouseTileY, mouseTileX))) {
                gridChange(mouseTileY, mouseTileX);
            }
            //Revela o tile
            field.revealTile(mouseTileY, mouseTileX, revealedCount);
            break;

        //Ação de posicionar bandeira
        case sf::Mouse::Right:
            this->flagInteraction(mouseTileY, mouseTileX);
        	break;

        default:
            break;
        }
}

//Renderiza o mapa
void Game::render_map()
{
    window.clear();

    // Exibe o quadrado debaixo com informações
    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE*cols, 2*TILE_SIZE));
    shape.setPosition(0, TILE_SIZE*cols);
    shape.setFillColor(sf::Color(3, 16, 151));
    window.draw(shape);

    // Exibe o timer
    sf::Font font;
    font.loadFromFile("./assets/fonts/RobotoCondensed-Regular.ttf"); //Carrega a fonte
    string str_text = "Tempo: ";
    string literal_time = to_string(int(time_ref.asSeconds()));
    str_text.append(literal_time);

    sf::Text time_text(str_text, font, 9);
    time_text.setPosition(0, int(TILE_SIZE*cols)-2); //Ajusta posição do texto
    time_text.setFillColor(sf::Color::White);
    window.draw(time_text);

    // Exibe os quadradinhos
    field.draw(window);
    window.display();
}

//Ações de posicionar a bandeira
void Game::flagInteraction(int row, int col) {
    if(row < 0 || row >= field.getRows() || col < 0 || col >= field.getCols()){ // Se estiver fora do tabuleiro ja criado
        return;
    }

    //Para o ponteiro no qual clicamos
    shared_ptr<Tile> tilePtr = field.getTile(row, col);
    //Se ja estiver revelado, retona
    if(tilePtr->isRevealed()) {
        return;
    }

    // Tile ja possui uma flag. Interacao de remocao da flag
    if(tilePtr->isFlagged()) {
        // Se a posição era de uma bomba, diminui o número de flags corretas
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags--;

        // Retirou uma flag, aumenta o número de flags disponíveis
        availableFlags++;
        tilePtr->setFlag(false);
        return;
    }

    // Tile nao possui flag. Interacao de colocar flag
    if(!(tilePtr->isFlagged())) {
        // Se acabaram as flags, retorna
        if(availableFlags == 0) return;
        // Se a posição for de uma bomba, o número de bandeiras corretas aumenta
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags++;

        //Diminui o número de flags disponíveis
        availableFlags--;
        tilePtr->setFlag(true);
        return;
    }

    return;
}

// Opera mudanças na matriz de tiles
// Usada quando o primeiro clique é sobre uma bomba
void Game::gridChange(int row, int col) {
    int totalTiles = rows * cols, i = 0;
    int new_col, new_row, pos;

    vector<int> positions(totalTiles);
    for (i = 0; i < totalTiles; ++i) positions[i] = i;

    //Embaralha as posições para distribuir as bombas
    random_device rd; //Fonte de números aleatórios
    mt19937 g(rd());  //Gerador de números
    shuffle(positions.begin(), positions.end(), g);

    //Encontra uma nova posição válida para a bomba
    i = 0;
    do {
        pos = positions[i];
        new_row = pos / cols;
        new_col = pos % cols;
        i++;
    }
    while(dynamic_pointer_cast<BombTile>(field.getTile(new_row, new_col)));

    //Onde antes era bomba, torna-se tile
    field.setTile(row, col, 1);
    //Posiciona a bomba na nova posição encontrada.
    //Outras mudanças no objeto game não são necessárias pois o número de bombas não mudou
    field.setTile(new_row, new_col, 2);
    //Calcula novamente o número de adjacencias no tabuleiro todo
    field.calculateAdjacentBombs();

    return;
}