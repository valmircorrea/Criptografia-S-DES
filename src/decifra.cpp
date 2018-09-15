/**
* @file	    decifra.cpp
* @brief	programa de 
* @author   Valmir Correa (valmircsjr@gmail.com)
* @date	    08/2018
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <string>
using std::string;
using std::stoi;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstdlib>
using std::atoi;

#include <bitset>
using std::bitset;

#include <cstring>
#include <algorithm>

/**
* @brief    Faz a leitura do conteudo do arquivo
* @param    arq Nome do arquivo a ser lido
* @return   Mensagem lida do arquivo
*/
string leitura (string arq) {
    
    ifstream arquivo (arq);
    
    if (!arquivo) {
        cerr << "Erro ao ler o arquivo " << arq << "!" << endl;
        exit (1);
    }

    string msg;
    while (!arquivo.eof()) {
        string str_temp;
        getline(arquivo, str_temp);
        msg += str_temp;
        msg += '\n';
    }

    if (msg == "") {
        cerr << "Não há mensagem para ser decifrada!" << endl;
        exit(1);
    }

    return msg;
}

/**
* @brief    Faz a escrita de uma mensagem em um arquivo
* @param    arq Nome do arquivo a ser aberto
*/
void escrita (string msg, string nome_arq) {
    
    ofstream arquivo (nome_arq, std::ofstream::ate);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo " << nome_arq << "!" << endl;
        exit (1);
    }

    arquivo << msg << endl;
    arquivo.close();
}

/**
* @brief    Cifra a mensagem recebida
* @param    msg Mensagem a ser cifrada
* @param    data Data
* @return   Mensagem cifrada
*/
string decifrar (bitset<10> chave_bit) {

    // Base para Permutações
    int P10[10] = {3,5,2,7,4,10,1,9,8,6};
    int P8[8] = {6,3,7,4,8,5,10,9};
    string chave_per = "";

    // Permutação inicial com P10 
    for (int ii = 0; ii < 10; ii++) {

        int indice_per = P10[ii]-1;
        chave_per     += chave_bit.to_string()[indice_per];
        
    }

    // Separação
    char temp_1[5];
    char temp_2[5];

    for (int ii = 0; ii < 5; ii++) {
            temp_1[ii] = chave_per[ii];
            temp_2[ii] = chave_per[ii + 5];
    }


    return chave_per;
}

/**
 * Função principal
*/
int main (int argc, char* argv[]) {

    // Verifica se os argumentos foram passados corretamente
    if (argc < 3) {
        cout << "--> Argumentos inválidos! Use o comando: ";
        cout << "'./bin/decifrar chave mensagem.txt saida.txt'" << endl;
        exit(1);
    }

    string arquivo_txt = argv[2];

    // Verificando o tamanho da chave
    if (strlen(argv[1]) != 10) {
        cerr << "--> Chave invalida!" << endl;
        cerr << "A chave deve ser uma sequencia de 10 bits" << endl;
        exit (1);
    }

    // leitura da mensagem
    string msg_cifrada = leitura(arquivo_txt);

    // Convertendo a chave para trabalhar com os bits
    string chave_str = argv[1];
    bitset<10> chave_bit (chave_str);

    cout << "Chave: " << chave_bit << endl;  

    cout << endl << "Permutação inicial (P10): " << decifrar (chave_bit) << endl;

    //cout << "--> Mensagens decifradas em 'data/mensagens_decifradas'!" << endl;

    return 0;
}