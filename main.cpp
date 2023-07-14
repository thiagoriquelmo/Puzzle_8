//ALUNO: Thiago Riquelmo Marques Nascimento

#include <iostream>
#include <vector>
#include <queue>
#include "puzzle.hpp"

using namespace std;

int main(){
    
    unsigned tabuleiro1[N][N] = {
        {5, 6, 2},
        {7, 1, 8},
        {3, 4, 0}
    };

    unsigned tabuleiro2[N][N] = {
        {5, 3, 2},
        {8, 7, 1},
        {4, 0, 6}
    };

    unsigned tabuleiro3[N][N] = {
        {1, 0, 7},
        {5, 2, 4},
        {3, 8, 6}
    };

    cout <<"Solução do tabuleiro 1:" << endl;
    resolverPuzzleAStar(tabuleiro1);
    cout << endl;

    cout <<"Solução do tabuleiro 2:" << endl;
    resolverPuzzleAStar(tabuleiro2);
    cout << endl;

    cout <<"Solução do tabuleiro 3:" << endl;
    resolverPuzzleAStar(tabuleiro3);
    cout << endl;

    return 0;
}