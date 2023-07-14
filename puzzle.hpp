// ALUNO: Thiago Riquelmo Marques Nascimento

#ifndef PUZZLE_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

#define N 3

// Estrutura para representar um estado de tabuleiro
struct EstadoTabuleiro
{
    unsigned tabuleiro[N][N];   // Configuração do tabuleiro
    unsigned movimentos;        // Número de movimentos até este estado
    unsigned linhaVazia;        // Linha em que o espaço em branco está localizado
    unsigned colunaVazia;       // Coluna em que o espaço em branco está localizado
    string sequenciaMovimentos; // Sequência de movimentos para chegar a este estado
    unsigned heuristica;        // Valor heurístico (distância de Manhattan)
};

// Imprime o tabuleiro do puzzle
void imprimirEstado(unsigned tabuleiro[N][N])
{
    for (unsigned i = 0; i < N; i++)
    {
        for (unsigned j = 0; j < N; j++)
        {
            cout << tabuleiro[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Verifica se o estado é a solução final
bool verificarSolucao(unsigned tabuleiro[N][N])
{
    unsigned contador = 1;
    for (unsigned i = 0; i < N; i++)
    {
        for (unsigned j = 0; j < N; j++)
        {
            if (tabuleiro[i][j] != contador % 9)
            {
                return false;
            }
            contador++;
        }
    }
    return true;
}

// Calcula a distância de Manhattan para uma célula específica
unsigned calcularDistanciaManhattan(unsigned valor, int linhaDoValor, int colunaDoValor)
{
    unsigned distancia;

    int linhaAlvo = (valor - 1) / N;
    int colunaAlvo = (valor - 1) % N;

    distancia = abs(linhaDoValor - linhaAlvo) + abs(colunaDoValor - colunaAlvo);

    return distancia;
}

// Calcula a heurística (distância de Manhattan) para o tabuleiro atual
unsigned calcularHeuristica(unsigned tabuleiro[N][N])
{
    unsigned heuristica = 0;
    for (unsigned i = 0; i < N; i++)
    {
        for (unsigned j = 0; j < N; j++)
        {
            unsigned valor = tabuleiro[i][j];
            if (valor != 0)
            {
                heuristica = heuristica + calcularDistanciaManhattan(valor, i, j);
            }
        }
    }
    return heuristica;
}

// Gera os possíveis movimentos a partir de um estado do puzzle
vector<EstadoTabuleiro> gerarMovimentos(EstadoTabuleiro estadoAtual)
{
    unsigned linhaDoZero = estadoAtual.linhaVazia;
    unsigned colunaDoZero = estadoAtual.colunaVazia;

    vector<EstadoTabuleiro> proximosMovimentos;

    // Movimento para cima (Caso não seja a primeira linha do tabuleiro)
    if (linhaDoZero > 0)
    {
        EstadoTabuleiro proximoEstado = estadoAtual;

        proximoEstado.tabuleiro[linhaDoZero][colunaDoZero] = proximoEstado.tabuleiro[linhaDoZero - 1][colunaDoZero];
        proximoEstado.tabuleiro[linhaDoZero - 1][colunaDoZero] = 0;

        proximoEstado.linhaVazia = linhaDoZero - 1;

        proximoEstado.movimentos++;

        proximoEstado.sequenciaMovimentos += "Cima";

        proximoEstado.heuristica = calcularHeuristica(proximoEstado.tabuleiro);

        proximosMovimentos.push_back(proximoEstado);
    }

    // Movimento para baixo
    if (linhaDoZero < N - 1)
    {
        EstadoTabuleiro proximoEstado = estadoAtual;

        proximoEstado.tabuleiro[linhaDoZero][colunaDoZero] = proximoEstado.tabuleiro[linhaDoZero + 1][colunaDoZero];
        proximoEstado.tabuleiro[linhaDoZero + 1][colunaDoZero] = 0;

        proximoEstado.linhaVazia = linhaDoZero + 1;

        proximoEstado.movimentos++;

        proximoEstado.sequenciaMovimentos += "Baixo";

        proximoEstado.heuristica = calcularHeuristica(proximoEstado.tabuleiro);

        proximosMovimentos.push_back(proximoEstado);
    }

    // Movimento para a esquerda
    if (colunaDoZero > 0)
    {
        EstadoTabuleiro proximoEstado = estadoAtual;

        proximoEstado.tabuleiro[linhaDoZero][colunaDoZero] = proximoEstado.tabuleiro[linhaDoZero][colunaDoZero - 1];
        proximoEstado.tabuleiro[linhaDoZero][colunaDoZero - 1] = 0;

        proximoEstado.colunaVazia = colunaDoZero - 1;

        proximoEstado.movimentos++;

        proximoEstado.sequenciaMovimentos += "Esquerda";

        proximoEstado.heuristica = calcularHeuristica(proximoEstado.tabuleiro);

        proximosMovimentos.push_back(proximoEstado);
    }

    // Movimento para a direita
    if (colunaDoZero < N - 1)
    {
        EstadoTabuleiro proximoEstado = estadoAtual;

        proximoEstado.tabuleiro[linhaDoZero][colunaDoZero] = proximoEstado.tabuleiro[linhaDoZero][colunaDoZero + 1];
        proximoEstado.tabuleiro[linhaDoZero][colunaDoZero + 1] = 0;

        proximoEstado.colunaVazia = colunaDoZero + 1;

        proximoEstado.movimentos++;

        proximoEstado.sequenciaMovimentos += "Direita";

        proximoEstado.heuristica = calcularHeuristica(proximoEstado.tabuleiro);

        proximosMovimentos.push_back(proximoEstado);
    }

    return proximosMovimentos;
}
// Classe para comparar dois estados do puzzle com base em seus valores heurísticos
class CompararEstado
{
public:
    bool operator()(EstadoTabuleiro estado1, EstadoTabuleiro estado2)
    {
        return (estado1.movimentos + estado1.heuristica) > (estado2.movimentos + estado2.heuristica);
    }
};

// Função para resolver o puzzle
void resolverPuzzleAStar(unsigned tabuleiro[N][N])
{
    auto start = std::chrono::high_resolution_clock::now(); // armazena o tempo de início

    // Estado inicial
    EstadoTabuleiro estadoInicial;
    estadoInicial.movimentos = 0;
    estadoInicial.linhaVazia = 0;
    estadoInicial.colunaVazia = 0;
    estadoInicial.sequenciaMovimentos = "";
    estadoInicial.heuristica = calcularHeuristica(tabuleiro);

    for (unsigned i = 0; i < N; i++)
    {
        for (unsigned j = 0; j < N; j++)
        {
            estadoInicial.tabuleiro[i][j] = tabuleiro[i][j];
            if (tabuleiro[i][j] == 0)
            {
                estadoInicial.linhaVazia = i;
                estadoInicial.colunaVazia = j;
            }
        }
    }

    // Fila de prioridade para manter os estados a serem avaliados
    priority_queue<EstadoTabuleiro, vector<EstadoTabuleiro>, CompararEstado> filaDeEstados;
    filaDeEstados.push(estadoInicial);

    // Tabela hash para verificar se um estado já foi visitado
    unordered_map<string, bool> visitados;
    visitados[estadoInicial.sequenciaMovimentos] = true;

    // Tabela hash para armazenar os estados visitados para reconstruir a solução
    unordered_map<string, vector<EstadoTabuleiro>> estadosVisitados;
    estadosVisitados[estadoInicial.sequenciaMovimentos] = {};

    unsigned contadorEstados = 0;

    // Percorre os estados que estão na fila
    while (!filaDeEstados.empty())
    {
        EstadoTabuleiro estadoAtual = filaDeEstados.top();
        filaDeEstados.pop();
        contadorEstados++;

        // Verifica se chegou na solução, se chegou imprime o caminho
        if (verificarSolucao(estadoAtual.tabuleiro))
        {
            cout << "Solução encontrada em " << estadoAtual.movimentos << " movimentos." << endl;
            cout << "Passos para a solução: " << endl;
            vector<EstadoTabuleiro> passosSolucao;
            passosSolucao.push_back(estadoAtual);
            while (estadoAtual.movimentos > 0)
            {
                for (EstadoTabuleiro proximoEstado : estadosVisitados[estadoAtual.sequenciaMovimentos])
                {
                    if (proximoEstado.movimentos == estadoAtual.movimentos - 1)
                    {
                        passosSolucao.push_back(proximoEstado);
                        estadoAtual = proximoEstado;
                        break;
                    }
                }
            }
            for (int i = passosSolucao.size() - 1; i >= 0; i--)
            {
                cout << "Passo " << passosSolucao[i].movimentos << ":" << endl;
                imprimirEstado(passosSolucao[i].tabuleiro);
            }
            break;
        }

        //Armazena o próximos movimentos gerados em um vector
        vector<EstadoTabuleiro> proximosMovimentos = gerarMovimentos(estadoAtual);
        for (EstadoTabuleiro proximoEstado : proximosMovimentos)
        {
            //Testa de o estado não foi visitado ainda
            if (!visitados[proximoEstado.sequenciaMovimentos])
            {
                filaDeEstados.push(proximoEstado);
                visitados[proximoEstado.sequenciaMovimentos] = true;
                estadosVisitados[proximoEstado.sequenciaMovimentos].push_back(estadoAtual);
            }
        }
    }

    cout << "Número de estados avaliados: " << contadorEstados << endl;

    auto end = std::chrono::high_resolution_clock::now(); // armazena o tempo de fim
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double seconds = duration.count() / 1000000.0;
    cout << endl << "Tempo de execução: " << seconds << " segundos" << endl;
    cout << endl;
}

#endif // !PUZZLE_H