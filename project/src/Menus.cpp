#include "../include/Game.hpp"

// Exibição do menu principal
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

    //Carregar a textura de fundo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/Menu.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    window.create(sf::VideoMode(800, 600), "Escolha a Dificuldade");

    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );

    //Avalia eventos no menu principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            //Evento de fechamento da janela
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return -1;
            }
            //Seleção das opções pela setinha do computador
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

        //Destaca em amarelo a opção escolhida pelas setinhas
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

// Menu de escolha da dificuldade
int Game::difficultyMenu() {
    std::vector<std::string> difficulties = {
        "Facil",
        "Medio",
        "Dificil",
        "Voltar"
    };

    sf::Font font;
    font.loadFromFile("../assets/fonts/Orbitron-Bold.ttf");

    //Carregar a textura de fundo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/Menu.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    //Cria a janela de exibição
    int selectedIndex = 0;
    window.create(sf::VideoMode(800, 600), "Escolha a Dificuldade");

    //Redimensiona o fundo
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );

    //Lida com os eventos no menu de dificuldades
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //Fechamento da janela
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            //Seleção com setinhas (similar ao menu principal)
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
        //Destaca a opção selecionada em amarelo
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

//Exibe as instruções de jogo
int Game::displayInstructions() {
    std::vector<std::string> scores;

    std::vector<std::string> texts = {
        "A evolucao de um dos maiores jogos de todos os tempos chegou!",
        "Campo Minado 2, agora duas vezes mais divertido!",
        "Para jogar eh muito simples, basta clicar com o botao esquerdo", 
        "para revelar um quadrado e clicar com o botao direito para",
        "marcar um quadrado suspeito de bomba com uma bandeira.",
        "Voce ganha ao marcar todas as bombas com bandeiras",
        "ou revelar todos os quadrados sem bombas.",
        "Ao final do jogo aperte M para voltar para o menu."
    };

    string returnText = "Voltar";

    sf::Font font;
    font.loadFromFile("../assets/fonts/Orbitron-Bold.ttf");

    //Carregar a textura de fundo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/InstructionsAndScore.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );

    window.create(sf::VideoMode(800, 600), "Aprenda a jogar");

    //Lida com os eventos (só da pra voltar)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    return 0;
                }
            }
        }

        window.clear();

        window.draw(backgroundSprite);

        for (size_t i = 0; i < texts.size(); ++i) {
            sf::Text text(texts[i], font, 15);
            text.setFillColor(sf::Color::White);
            text.setPosition(window.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, 100 + i * 35);
            window.draw(text);
        }

        sf::Text text(returnText, font, 40);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(window.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, 490);
        window.draw(text);

        window.display();
    }

    return -1;
}

// Exibe as scores de quem venceu
int Game::displayScores() {
    sf::Font font;
    font.loadFromFile("../assets/fonts/Orbitron-Bold.ttf");

    std::ifstream file("../save/scores.txt");
    file.is_open();

    //Variáveis auxiliares
    std::string line;
    std::string currentDifficulty;
    std::vector<std::string> easyScores;
    std::vector<std::string> mediumScores;
    std::vector<std::string> hardScores;
    string returnText = "Voltar";

    //Lê o arquivo linha por linha
    while (std::getline(file, line)) {
        if (line == "easy" || line == "medium" || line == "hard") {
            currentDifficulty = line; //Define a dificuldade atual
        } else if (!line.empty()) {
            //Armazena a linha dependendo da dificuldade
            if (currentDifficulty == "easy") {
                easyScores.push_back(line);
            } else if (currentDifficulty == "medium") {
                mediumScores.push_back(line);
            } else if (currentDifficulty == "hard") {
                hardScores.push_back(line);
            }
        }
    }

    file.close();

    //Carregar a textura de fundo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/images/InstructionsAndScore.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );

    //Cria uma janela para exibir os scores
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maiores jogadores de todos os tempos");

    //Similar à seção de instruções de jogo
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { //Fecha janela de scores
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    return 0;
                }
            }
        }

        //Exibe o background
        window.clear();
        window.draw(backgroundSprite);

        //Variáveis para posicionamento do texto
        float yOffset = 50;  //Posição inicial no eixo Y

        // Função para desenhar os scores
        auto drawScores = [&](const std::string& difficulty, const std::vector<std::string>& scores) {
            sf::Text title(difficulty, font, 30);
            title.setFillColor(sf::Color::Yellow);
            title.setPosition(window.getSize().x / 2.f - title.getGlobalBounds().width, yOffset);
            window.draw(title);

            yOffset += 30; //Espaço após o título

            for (const auto& score : scores) {
                sf::Text scoreText(score, font, 20);
                scoreText.setFillColor(sf::Color::White);
                scoreText.setPosition(window.getSize().x / 2.f - scoreText.getGlobalBounds().width, yOffset);
                window.draw(scoreText);
                yOffset += 20; //Espaço entre as linhas de score
            }

            yOffset += 10; //Espaço extra entre dificuldades
        };

        // Desenha os scores para cada dificuldade
        drawScores("Easy", easyScores);
        drawScores("Medium", mediumScores);
        drawScores("Hard", hardScores);

        sf::Text text(returnText, font, 40);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(window.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, 490);
        window.draw(text);

        // Exibe os elementos na tela
        window.display();
    }

    return -1;
}