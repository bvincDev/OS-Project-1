#include "share.hpp"
using namespace std;

int main() {
    //open shared memory and set its size
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedTable));
    auto* shared = (SharedTable*)mmap(nullptr, sizeof(SharedTable),
                                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    //open or create semaphores
    auto* empty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0666, TABLE_SIZE);
    auto* full  = sem_open(SEM_FULL_NAME,  O_CREAT, 0666, 0);
    auto* mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0666, 1);

    while (true) {
        sem_wait(full);   //wait for an item to consume
        sem_wait(mutex);  //critical section

        //remove item from shared table
        int item = shared->table[shared->out];
        cout << "Consumed: " << item << endl;
        shared->out = (shared->out + 1) % TABLE_SIZE;

        sem_post(mutex);  //exit critical section
        sem_post(empty);  //signal a free slot
        sleep(2);         //time to consume
    }

    return 0;
}