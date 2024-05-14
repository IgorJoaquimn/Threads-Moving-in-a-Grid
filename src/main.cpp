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

    init_mutex(N);

    vector<thread_t> threads;

    for (int i = 0; i < n_threads; ++i)
    {
        int id, gid, n_pos;
        cin >> id >> gid >> n_pos;

        thread_t new_thread(id, gid, n_pos);

        for (int j = 0; j < n_pos; ++j)
        {
            int x, y, time;
            cin >> x >> y >> time;
            cell new_cell = {x, y, time, gid};
            new_thread.path.push(new_cell);
        }

        threads.push_back(new_thread);
    }


    vector<pthread_t> thread_handles;

    // Create pthreads
    for (auto& thread : threads)
    {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, thread_run, &thread);
        thread_handles.push_back(thread_id);
    }

    // Join pthreads
    for (auto& thread_id : thread_handles)
        pthread_join(thread_id, NULL);
    return 0;
}