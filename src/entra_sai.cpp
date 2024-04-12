#include "Thread.h"

const int N_init = 20;

pthread_mutex_t grid_mutexes[N_init][N_init]; // 2D array of mutexes
pthread_cond_t grid_conds[N_init][N_init];    // 2D array of condition variables
bool grid_occupied[N_init][N_init];    // 2D array of condition variables

void entra(int x, int y)
{
    pthread_mutex_lock(&grid_mutexes[x][y]);
    while(grid_occupied[x][y]) pthread_cond_wait(&grid_conds[x][y], &grid_mutexes[x][y]);

    grid_occupied[x][y] = true;
    pthread_mutex_unlock(&grid_mutexes[x][y]);
}

void sai(int x, int y)
{
    grid_occupied[x][y] = false;
    pthread_cond_signal(&grid_conds[x][y]); // Notify one waiting thread that the position is available
}

void init_mutex(int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            pthread_mutex_init(&grid_mutexes[i][j], NULL);
            pthread_cond_init(&grid_conds[i][j], NULL);
            grid_occupied[i][j] = false;
        }
    }
}