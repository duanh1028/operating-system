#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "pro_and_con.h"

void main(int argc, char* argv[]) {
    cir_buff* buff;

    int i = 0;                          // Loop index variable
    uint32 h_mem;                   // Used to hold handle to shared memory page
    sem_t s_procs_completed;        // Semaphore used to wait until all spawned processes have completed
    lock_t buff_lock;       // lock to secure no other processs

    char str[] = "Hello World";
    //Printf("has consumer started?\n");
    if (argc != 4) {
    Printf("Usage: "); Printf(argv[0]); Printf(" FILENAME_TO_RUN, h_mem, s_procs_completed, buff_lock\n");
    Exit();
    }

    // Convert string from ascii command line argument to integer number
    h_mem = dstrtol(argv[1], NULL, 10); // the "10" means base 10
    s_procs_completed = dstrtol(argv[2], NULL, 10);
    buff_lock = dstrtol(argv[3], NULL, 10);

    // Map shared memory page into this process's memory space
    if ((buff = (cir_buff *)shmat(h_mem)) == NULL) {
    Printf("Could not map the shared page to virtual address in \n"); Printf(argv[0]); Printf(", exiting..\n");
    Exit();
    }

    for (i = 0; i < 11;) {
        if (lock_acquire(buff_lock) != SYNC_SUCCESS) {
            Printf("lock acquire failed\n");
            Exit();
        }

        if (buff -> head == buff -> tail) {
            Printf("buffer is empty\n");
        }
        else {
            //Printf("buffer is not empty\n");
            Printf("Consumer %d removed: %c \n", getpid(), buff->c[buff->tail]);
            buff -> tail = (buff -> tail + 1) % BUFFERSIZE;
            i++;
        }

        if (lock_release(buff_lock) != SYNC_SUCCESS) {
            Printf("lock release failed\n");
            Exit();
        }
    }
    Printf("Consumer number %d completed \n", getpid());

    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }

 }