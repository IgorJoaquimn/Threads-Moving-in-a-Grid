#include <iostream>
#include "Thread.h"
#include <vector>

using namespace std;

void* thread_run(void* arg) {
    thread_t* thread_data = reinterpret_cast<thread_t*>(arg);
    thread_data->run();
    pthread_exit(NULL);
}

int main()
{   
    int n_threads, N;
    cin >> N >> n_threads;

    // Primeiramente, devemos instanciar as variaveis globais
    init_mutex(N);

    // E ler a entrada...
    vector<thread_t> threads;

    int id, gid, n_pos;
    int x, y, time;
    for (int i = 0; i < n_threads; ++i)
    {
        cin >> id >> gid >> n_pos;
        thread_t new_thread(id, gid, n_pos);
        for (int j = 0; j < n_pos; ++j)
        {
            cin >> x >> y >> time;
            cell new_cell = {x, y, time, gid};
            new_thread.path.push(new_cell);
        }
        threads.push_back(new_thread);
    }

    // Com isso, podemos disparar as threads...
    vector<pthread_t> thread_handles;
    for (auto& thread : threads)
    {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, thread_run, &thread);
        thread_handles.push_back(thread_id);
    }
    // E esperá-las executarem
    for (auto& thread_id : thread_handles)
        pthread_join(thread_id, NULL);
    return 0;
}