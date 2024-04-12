#ifndef THREAD
#define THREAD

#include <queue>
#include <pthread.h>
#include <cstdio>


void init_mutex(int N);
void passa_tempo(int tid, int x, int y, int decimos);
void entra(int x, int y);
void sai(int x, int y);


class cell {
    public:
    int x,y,time;
};


class thread_t {
public:
    int id;
    int gid;
    int n_pos;
    std::queue<cell> path;
    thread_t(int id, int gid, int n_pos) : id(id), gid(gid), n_pos(n_pos)  {}

    void run();

};

#endif /* THREAD */
