/**
* @file	    cifra_cesar.cpp
* @brief	programa de criptoanálise que utilize de força bruta para 
*           quebrar uma mensagem encriptada usando uma cifra de César tradicional.
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

#include <cstring>

#include <algorithm>

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstdlib>
using std::atoi;

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
string decifrar (string msg, int chave) {

    string msg_decifrada = "";
    int msg_tam = msg.size();
    char alfabeto_Minuscula[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char alfabeto_Maiuscula[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    for (int ii = 0; ii < msg_tam; ii++) {
        bool achou_letra = false;
        for (int pp = 0; pp < 26; pp++) {
            if (msg[ii] == alfabeto_Minuscula[pp]) {
                achou_letra = true;
                if (pp >= chave) {
                    msg_decifrada += alfabeto_Minuscula[(pp-chave)];
                } else {
                    msg_decifrada += alfabeto_Minuscula[26-(chave-pp)];
                }
                break;
            } else if (msg[ii] == alfabeto_Maiuscula[pp]) {
                achou_letra = true;
                if (pp >= chave) {
                    msg_decifrada += alfabeto_Maiuscula[(pp-chave)];
                } else {
                    msg_decifrada += alfabeto_Maiuscula[26-(chave-pp)];
                }
                break;
            }
        }
        if (!achou_letra) {
            msg_decifrada += msg[ii];
        }
    }
    return msg_decifrada;
}

/**
 * Função principal
*/
int main (int argc, char* argv[]) {

    // Verifica se os argumentos foram passados corretamente
    if (argc != 2) {
        cout << "--> Argumentos inválidos! Use o comando: ";
        cout << "'./cifra_cesar data/mensagem.txt'" << endl;
        exit(1);
    }

    string arquivo_txt = argv[1];

    // leitura da mensagem
    string msg_cifrada = leitura(arquivo_txt);

    // Tentando decifrar
    for (int ii = 1; ii < 25; ii++) {
        string msg_decifrada = decifrar(msg_cifrada, ii);
        
        string nome_arq = "data/mensagens_decifradas/mensagem_decifrada_chave_";
        nome_arq += std::to_string(ii);
        nome_arq += ".txt";
        
        escrita(msg_decifrada, nome_arq);
    }

    cout << "--> Mensagens decifradas em 'data/mensagens_decifradas'!" << endl;

    return 0;
}