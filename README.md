# OS-Project-1
Programming assignment #1 for operating systems, the producer consumer problem.

## Files:
- `shared.hpp`: defines the shared memory structure and semaphore names
- `producer.cpp`: implements the process of continuously producing items in the shared memory
- `consumer.cpp`: implements the process of continuously consuming items in the shared memory
  
## Overview
#### problem
- The producer and consumer processes need to share a buffer and modify/access it concurrently
#### description
- First, a buffer is created with shared memory and semaphores. There are three seperate semaphores; empty, full, and mutex. Empty is initialized to the buffer size and tracks the empty slots, forcing the producer to wait before adding an item. Full semaphore is initialized to zero and counts the filled slots, having the consumer wait before consuming. Finally the Mutex semaphore makes sure of mutual exclusion when accessing the shared buffer, preventing concurrent changes. The producer process will create an item and wait for an empty slot. The shared memory is then locked using the mutex. In the buffer the item is placed and the in index is updated unlocking the buffer and signaling an item is available. The consumer process waits for an item available and locks the shared memory. The item is retrieved from the buffer and the out is updated unlocking the buffer signaling a slot is empty. Lastly, sleep is used to simulate the time it takes to produce and consume.

## Prerequisites

- A Unix operating system or environment
- A C++ compiler

## Compiling the Programs

$ `g++ producer.cpp -pthread -lrt -o producer`<br />
$ `g++ consumer.cpp -pthread -lrt -o consumer`<br />
$ `./producer & ./consumer &`

## Example
![image](https://github.com/user-attachments/assets/ac714a5d-14d9-4f12-b1de-23e516eb88fe)<br />
![image](https://github.com/user-attachments/assets/e445b450-1078-4215-a1d9-8fed94426327)
