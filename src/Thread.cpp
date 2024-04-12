#include "Thread.h"

void thread_t::run()
{
    while (!path.empty())
    {
        // Get the next position
        cell next_position = path.front();
        path.pop();

        // Enter the next position
        entra(next_position.x, next_position.y);
        // Execute passa_tempo for the next position
        passa_tempo(id, next_position.x, next_position.y, next_position.time);
        // Release the previous position
        sai(next_position.x, next_position.y);
    }
}
