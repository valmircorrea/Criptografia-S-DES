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

// rotação para chave 1
string rotacao_esq(char *chave_per) {

    char chave_rotacionada[10];
    string chave_completa = "";

    for (int ii = 0; ii < 10; ii++) {
        if (ii == 4) {
            chave_completa += chave_per[0];
        } else if ( ii == 9) {
            chave_completa += chave_per[5];
        } else {
            chave_completa += chave_per[ii+1];
        }
        
    }
    return chave_completa;
}

/**
* @brief    CGera chave k1
* @param    msg Mensagem a ser cifrada
* @param    data Data
* @return   Mensagem cifrada
*/
string gerar_sub_chave_k1 (bitset<10> chave_bit) {
     
    // Base para Permutações
    int P10[10] = {3,5,2,7,4,10,1,9,8,6};
    int P8[8] = {6,3,7,4,8,5,10,9};
    char chave_per[10];

    // Permutação inicial com P10
    cout << "Permutação inicial (P10): ";
    for (int ii = 0; ii < 10; ii++) {

        int indice_per = P10[ii]-1;
        chave_per[ii]  = chave_bit.to_string()[indice_per];
        cout << chave_per[ii];
        
    }

    // Separação e rotação
    string  chave_rotacionada = rotacao_esq(chave_per);   

    cout << endl << "Rotação a esquerda LS-1: " << chave_rotacionada << endl;

    // Permutação SW (P8)
    bitset<10> chave_per_p8 (chave_rotacionada);
    string sub_chave_k1 = "";
    for (int ii = 0; ii < 8; ii++) {

        int indice_per = P8[ii]-1;
        sub_chave_k1  += chave_per_p8.to_string()[indice_per];   
    }

    cout << "sub_chave_k1 : " << sub_chave_k1 << endl;
   
    return sub_chave_k1 ;
}

// Rotação para a chave 2
string rotacao_esq_2(char *chave_per) {

    char chave_rotacionada[10];

    cout << endl << "teste:   ";
    for ( int ii = 0; ii < 10; ii++) {
        cout << chave_per[ii];
    }
    string chave_completa = "";
    chave_completa += chave_per[2];
    chave_completa += chave_per[3];
    chave_completa += chave_per[4];
    chave_completa += chave_per[0];
    chave_completa += chave_per[1];
    chave_completa += chave_per[7];
    chave_completa += chave_per[8];
    chave_completa += chave_per[9];
    chave_completa += chave_per[5];
    chave_completa += chave_per[6];

    return chave_completa;
}

/**
* @brief    CGera chave k1
* @param    msg Mensagem a ser cifrada
* @param    data Data
* @return   Mensagem cifrada
*/
string gerar_sub_chave_k2 (bitset<10> chave_bit) {
     
    // Base para Permutações
    int P10[10] = {3,5,2,7,4,10,1,9,8,6};
    int P8[8] = {6,3,7,4,8,5,10,9};
    char chave_per[10];

    // Permutação inicial com P10
    cout << "Permutação inicial (P10): ";
    for (int ii = 0; ii < 10; ii++) {

        int indice_per = P10[ii]-1;
        chave_per[ii]  = chave_bit.to_string()[indice_per];
        cout << chave_per[ii];
        
    }

    // Separação e rotação
    string  LS_1 = rotacao_esq(chave_per);

    // ============================ a partir daqui que muda
    char resultado_LS_1[10];
    for (int ii = 0; ii < 10; ii++) {
        resultado_LS_1[ii] = LS_1[ii];
    }

    // Separação e rotação
    string  chave_rotacionada = rotacao_esq_2(resultado_LS_1);   
    cout << endl << "Rotação a esquerda LS-2 duas posições: " << chave_rotacionada << endl;

    // Permutação SW (P8)
    bitset<10> chave_per_p8 (chave_rotacionada);
    string sub_chave_k2 = "";
    for (int ii = 0; ii < 8; ii++) {

        int indice_per = P8[ii]-1;
        sub_chave_k2  += chave_per_p8.to_string()[indice_per];   
    }

    cout << "sub_chave_k2 : " << sub_chave_k2 << endl;
   
    return sub_chave_k2 ;
}

bitset<8> funcao_complexa (/*bitset<8> texto_bit,*/ bitset<10> k1, bitset<10> k2 ) {

    int IP[8]       = {2,6,3,1,4,8,5,7};
    int EP[8]       = {4,1,2,3,2,3,4,1};
    int S0[4][4]    = {{1,0,3,2}, {3,2,1,0}, {0,2,1,3}, {3,1,3,2}};
    int S1[4][4]    = {{1,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3}};
    int P4[4]       = {2,4,3,1};
    int IP_1[8]     = {4,1,3,5,7,2,8,6};

}

/**
* @brief    Cifra a mensagem recebida
* @param    msg Mensagem a ser cifrada
* @param    data Data
* @return   Mensagem cifrada
*/
string decifrar (bitset<10> chave_bit) {

   string k1_str = gerar_sub_chave_k1 (chave_bit);
   string k2_str = gerar_sub_chave_k2 (chave_bit);

    bitset<10> k1 (k1_str);
     bitset<10> k2 (k2_str);

   funcao_complexa (k1, k2);

   return "teste";
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

    decifrar (chave_bit);

    //cout << endl << "Permutação inicial (P10): " << decifrar (chave_bit) << endl;

    //cout << "--> Mensagens decifradas em 'data/mensagens_decifradas'!" << endl;

    return 0;
}