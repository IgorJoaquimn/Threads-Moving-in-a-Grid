#include "Thread.h"

void thread_t::run()
// Função que implementa o caminho no grid
{
    while (!path.empty())
    {
        // Vá para a proxima posição
        cell next_position = path.front();
        path.pop();

        // Entre (se possível)
        entra(next_position);
        // Execute passa_tempo
        passa_tempo(id, next_position.x, next_position.y, next_position.time);
        // Saia da posição atual
        sai(next_position);
    }
}
