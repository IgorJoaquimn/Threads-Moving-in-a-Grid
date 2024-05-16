#include "Thread.h"

const int N_init = 20;

pthread_mutex_t grid_mutexes[N_init][N_init];   // 2D array of mutexes
pthread_cond_t  grid_conds[N_init][N_init];     // 2D array of condition variables
std::set<int>   grid_occupied[N_init][N_init];   


bool is_grid_occupied(cell &c) {
// Antes de ocupar uma célula, é preciso checar se o movimento é válido

// Temos as seguintes regras:
    // Podemos ter ao máximo duas threads na mesma célula
    if (grid_occupied[c.x][c.y].size() == 2)
        return true;

    // Existe thread com o tipo T nessa posição? // IF para simplicidade
    if (grid_occupied[c.x][c.y].find(c.t) != grid_occupied[c.x][c.y].end())
        return true; 
    return false;
}

void entra(cell &c)
{
    // Cada célula deve compor uma seção crítica distinta, para impedir que comportamento inesperado aconteça
    pthread_mutex_lock(&grid_mutexes[c.x][c.y]);
    // O próximo movimento só deve acontecer se a posição não estiver ocupada

    
    // O uso de variavel de condição serve para que, dado que uma thread tenha liberado a 
    // celula que outra está tentando acessar, imediatamente as outras threads podem ter a 
    // possibilidade de avançar
    while(is_grid_occupied(c)) pthread_cond_wait(&grid_conds[c.x][c.y], &grid_mutexes[c.x][c.y]);

    // Ao avançar, devemos rastrear qual alterações fizemos na célula atual 
    grid_occupied[c.x][c.y].insert(c.t);
    pthread_mutex_unlock(&grid_mutexes[c.x][c.y]);
}

void sai(cell &c)
{
    // Ainda no momento de saída, é necessário o uso da seção crítica, dado a alteração feita no grid, e o signal feito
    pthread_mutex_lock(&grid_mutexes[c.x][c.y]);

    // Rastreamos a alteração feita (liberando o acesso para threads do grupo T)
    grid_occupied[c.x][c.y].erase(grid_occupied[c.x][c.y].find(c.t));

    // Por fim, avisamos (a quem interessa) que uma alteração foi feita nessa posição 
    pthread_cond_signal(&grid_conds[c.x][c.y]);
    pthread_mutex_unlock(&grid_mutexes[c.x][c.y]);
}


void init_mutex(int N)
// As variáveis de condição e os mutexes devem ser inicializados da maneira esperada
// No início do programa
    // Nenhuma thread deve estar contendo nenhum mutex
    // Nenhuma thread deve estar esperando uma variavel de condição
    // As células devem estar vazias
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            pthread_mutex_init(&grid_mutexes[i][j], NULL);
            pthread_cond_init(&grid_conds[i][j], NULL);
            grid_occupied[i][j].clear();
        }
    }
}