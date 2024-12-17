#include <random>
#include <stdio.h>
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

void Game::event_Mouse_Click(const sf::Event::MouseButtonEvent &mouseButton)
{
    int mouseTileX = sf::Mouse::getPosition(window).x / TILE_SIZE / SCREEN_RESIZE;
    int mouseTileY = sf::Mouse::getPosition(window).y / TILE_SIZE / SCREEN_RESIZE;

    if (mouseTileX < 0 || mouseTileX >= cols || mouseTileY < 0 || mouseTileY >= rows) return;

    switch (mouseButton.button){
        case sf::Mouse::Left:
            if(revealedCount == 0 && dynamic_pointer_cast<BombTile>(field.getTile(mouseTileY, mouseTileX))) {
                gridChange(mouseTileY, mouseTileX);
            }
            field.revealTile(mouseTileY, mouseTileX, revealedCount);
            break;

        case sf::Mouse::Right:
            this->flagInteraction(mouseTileY, mouseTileX);
        	break;

        default:
            break;
        }
}

int Game::check_WL()
{
    if(revealedCount==(rows * cols - bombs) || correctFlags == bombs){
        std::cout<< "DEBBUG SUCESSO\n";
        return 1;
    } 
    else if(revealedCount == -1){
        std::cout << "DEBBUG DERROTA\n";
        return -1;
    }
    return 0;
}

void Game::render_map()
{
    window.clear();

    // Imprime o quadrado debaixo
    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE*cols, 2*TILE_SIZE));
    shape.setPosition(0, TILE_SIZE*cols);
    shape.setFillColor(sf::Color(3, 16, 151));
    window.draw(shape);

    // Imprime timer
    sf::Font font;
    font.loadFromFile("../assets/fonts/RobotoCondensed-Regular.ttf"); //Carrega a fonte
    string str_text = "Tempo: ";
    string literal_time = to_string(int(time_ref.asSeconds()));
    str_text.append(literal_time);

    sf::Text time_text(str_text, font, 9);
    time_text.setPosition(0, int(TILE_SIZE*cols)-2); //Ajusta posição do texto
    time_text.setFillColor(sf::Color::White);
    window.draw(time_text);


    
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
        return;
    }

    // Tile ja possui uma flag. Interacao de remocao da flag
    if(tilePtr->isFlagged()) {
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags--;

        availableFlags++;
        tilePtr->setFlag(false);
        return;
    }

    // Tile nao possui flag. Interacao de colocar flag
    if(!(tilePtr->isFlagged())) {
        if(availableFlags == 0) return;
        if(dynamic_pointer_cast<BombTile>(tilePtr)) correctFlags++;

        availableFlags--;
        tilePtr->setFlag(true);
        return;
    }

    return;
}

int Game::mainMenu()
{
    
    window.create(sf::VideoMode(800, 600), "Campo Minado");
    std::vector<std::string> menuItems = {
        "Jogar",
        "Como Jogar",
        "Maiores Scores",
        "Sair",
    };

    sf::Font font;
    font.loadFromFile("../assets/fonts/Orbitron-Bold.ttf");
    int selectedIndex = 0;

    // Carregar a textura de fundo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/Menu.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return -1;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : menuItems.size() - 1;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    selectedIndex = (selectedIndex < menuItems.size() - 1) ? selectedIndex + 1 : 0;
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    return selectedIndex;
                }
            }
        }

        window.clear();
        
        window.draw(backgroundSprite);

        for (size_t i = 0; i < menuItems.size(); ++i) {
            sf::Text text(menuItems[i], font, 35);
            text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
            text.setPosition(window.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, 275 + i * 70);
            window.draw(text);
        }

        window.display();
    }

    return -1;
}

int Game::difficultyMenu() {
    std::vector<std::string> difficulties = {
        "Facil",
        "Medio",
        "Dificil",
        "Voltar"
    };

    sf::Font font;
    font.loadFromFile("../assets/fonts/Orbitron-Bold.ttf");

    // Carregar a textura de fundo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/Menu.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );


    int selectedIndex = 0;
    window.create(sf::VideoMode(800, 600), "Escolha a Dificuldade");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : difficulties.size() - 1;
                } else if (event.key.code == sf::Keyboard::Down) {
                    selectedIndex = (selectedIndex < difficulties.size() - 1) ? selectedIndex + 1 : 0;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    return selectedIndex;
                }
            }
        }

        window.clear();

        window.draw(backgroundSprite);

        for (size_t i = 0; i < difficulties.size(); ++i) {
            sf::Text text(difficulties[i], font, 40);
            text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
            text.setPosition(window.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, 275 + i * 70);
            window.draw(text);
        }

        window.display();
    }

    return -1;
}

void Game::gridChange(int row, int col) {
    int totalTiles = rows * cols, i = 0;
    int new_col, new_row, pos;

    vector<int> positions(totalTiles);
    for (i = 0; i < totalTiles; ++i) positions[i] = i;

    //Embaralha as posições para distribuir as bombas
    random_device rd; //Fonte de números aleatórios
    mt19937 g(rd());  //Gerador de números
    shuffle(positions.begin(), positions.end(), g);

    //Coloca as bombas no campo
    i = 0;
    do {
        pos = positions[i];
        new_row = pos / cols;
        new_col = pos % cols;
        i++;
    }
    while(dynamic_pointer_cast<BombTile>(field.getTile(new_row, new_col)));


    field.setTile(row, col, 1);
    field.setTile(new_row, new_col, 2);
    field.calculateAdjacentBombs();

    return;
}