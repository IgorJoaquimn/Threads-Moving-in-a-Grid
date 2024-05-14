#include "Thread.h"
#include <set>

const int N_init = 20;

pthread_mutex_t grid_mutexes[N_init][N_init]; // 2D array of mutexes
pthread_cond_t grid_conds[N_init][N_init];    // 2D array of condition variables
std::set<int> grid_occupied[N_init][N_init];    // 2D array of condition variables

bool is_grid_occupied(cell &c, int t) {
    int x = c.x;
    int y = c.y;

    if (grid_occupied[x][y].size() == 2)
        return true;

    if (grid_occupied[x][y].find(t) != grid_occupied[x][y].end())
        return true;

    return false;
}

void entra(cell &c,int t)
{
    pthread_mutex_lock(&grid_mutexes[c.x][c.y]);
    while(is_grid_occupied(c,t)) pthread_cond_wait(&grid_conds[c.x][c.y], &grid_mutexes[c.x][c.y]);

    grid_occupied[c.x][c.y].insert(t);
    pthread_mutex_unlock(&grid_mutexes[c.x][c.y]);
}

void sai(cell &c,int t)
{
    pthread_mutex_lock(&grid_mutexes[c.x][c.y]);
    grid_occupied[c.x][c.y].erase(grid_occupied[c.x][c.y].find(t));
    pthread_cond_signal(&grid_conds[c.x][c.y]);
    pthread_mutex_unlock(&grid_mutexes[c.x][c.y]);

}


void init_mutex(int N)
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