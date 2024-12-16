#include "../include/File.hpp"
#include "../include/Player.hpp"
#include <map>
#include <vector>

void open_file(){
    std::ifstream fileCheck("main_file");
    
    if(!fileCheck.is_open()){  // Se o arquivo não existir, cria
        std::ofstream file("main_file");
        file << "easy\n";
        file << "medium\n";
        file << "hard\n";
        file.close();
    }
    fileCheck.close();
}

void writeScoreToFile(const std::string& difficulty, const Player& player){
    std::ifstream main_file_op("main_file"); // arquivo principal aberto

    if(!main_file_op.is_open()){
        std::cout<<"Erro ao abrir o arquivo para leitura."<<std::endl;
        exit(-1);
    }

    std::map<std::string, std::vector<Player>> scores;
    std::string line_read, difficulty_aux;
    std::vector<Player> list_players;

    // leitura do arquivo
    while(std::getline(main_file_op, line_read)){
        if(line_read.empty()){
           continue; // nao sei pq isso funciona
        } 

        if(line_read== "easy"|| line_read== "medium"|| line_read== "hard"){ // leitura da dificuldade
            if(!difficulty_aux.empty()){
                scores[difficulty_aux] = list_players; // salva a lista de jogadores anteriores na dificuldade anteriormente lida
            }
            difficulty_aux= line_read; // atualiza a dificuldade processada
            list_players.clear(); // limpa buffer
        } 
        else{ // leitura dos jogadores na dificuldade anteriormente lida
            std::stringstream string_aux(line_read);
            Player ply_aux;
            int score;
            string_aux >> score; // leitura do valor pontuacao
            if(string_aux.fail()){ // Ignora linhas inválidas
                continue;
            }

            ply_aux.addScore(score); // add score ao jogador

            std::string name;
            std::getline(string_aux, name); // leitura do nome
            ply_aux.addName(name);

            list_players.push_back(ply_aux); // salva ele no vetor 
        }
    }

    if (!difficulty_aux.empty()){// coloca o vetor jogadores na dificuldade correta
        scores[difficulty_aux] = list_players; 
    }
    main_file_op.close(); // fecha o arquivo principal

    // arquivo secundario para reescrita das informacoes 

    auto& players = scores[difficulty]; // salva o map de player criado
    players.push_back(player); // adiciona score e nome novo

    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b){ // faz o sort com o resultado novo
        return a.getScore() < b.getScore();
    });

    // pega os 5 menores tempos 
    if(players.size()> 5){
        players.resize(5);
    }

    // rescreve o arquivo completo
    std::ofstream outfile("main_file", std::ios::trunc);
    if(!outfile.is_open()){
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        exit(-1);
    }

    // reescrevenmdo
    auto it = scores.begin();
    for (; it != scores.end(); ++it) {
        const auto& diff = it->first;
        const auto& players = it->second;
        
        outfile << diff << "\n";
        for (size_t i = 0; i < players.size(); ++i) {
            const auto& p = players[i];
            outfile << p.getScore() << " " << p.getName() << "\n";
        }
        outfile << "\n"; // Adiciona uma linha em branco entre seções
    }
    
    outfile.close();
}

