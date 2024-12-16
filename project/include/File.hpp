#include <fstream>
#include <iostream>
#include <string>


std::fstream openFile(){
    
    std::fstream file("main_file", std::ios::in | std::ios::out | std::ios::app); // Abre para leitura e escrita, cria se não existir

    if (!file.is_open()) {
        exit(-1);
    }

    return file; // Retorna o arquivo
}

void uptade_file( std::fstream main_file){
    // pensar em um metodo de
}