#include "share.hpp"
using namespace std;

int main() {
    //open shared memory and set its size
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedTable));
    auto* shared = (SharedTable*)mmap(nullptr, sizeof(SharedTable),
                                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    //initialize shared table
    shared->in = shared->out = 0;

    //open or create semaphores
    auto* empty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0666, TABLE_SIZE);
    auto* full  = sem_open(SEM_FULL_NAME,  O_CREAT, 0666, 0);
    auto* mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0666, 1);

    int item = 0;
    while (true) {
        item++; //produce an item
        sem_wait(empty); //wait for one empty slot
        sem_wait(mutex); //critical section

        //insert item into shared table
        shared->table[shared->in] = item;
        cout << "Produced: " << item << endl;
        shared->in = (shared->in + 1) % TABLE_SIZE;

        sem_post(mutex);  //exit critical section
        sem_post(full);   //signal an item is produced
        sleep(1);         //time to produce
    }

    return 0;
}