#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "pro_and_con.h"

void main(int argc, char* argv[]) {
    cir_buff* buff;
    int i = 0;
    uint32 h_mem; 
    lock_t buff_lock;
    sem_t s_procs_completed;
    cond_t wcond, scond;


    char msg[] = "Hello World";
    Printf("has producer started?\n");
	if (argc != 6) { 
		Printf("Usage: "); Printf(argv[0]); Printf("FILENAME_TO_RUN, h_mem, s_procs_completed, buff_lock, wcond, scond\n"); 
		Exit();
	} 

    h_mem = dstrtol(argv[1], NULL, 10);
    s_procs_completed = dstrtol(argv[2], NULL, 10);
    buff_lock = dstrtol(argv[3], NULL, 10);
    wcond = dstrtol(argv[4], NULL, 10);
    scond = dstrtol(argv[5], NULL, 10);



    if ((buff = (cir_buff *)shmat(h_mem)) == NULL) {
        Printf("Could not map the shared page to virtual address in \n"); Printf(argv[0]); Printf(", exiting..\n");
        Exit();
    }
    
    for (i = 0; i < 11; i++) {
        if (lock_acquire(buff_lock) != SYNC_SUCCESS) {
            Printf("lock acquire failed\n");
        }
        while ((buff -> head + 1) % BUFFERSIZE == buff -> tail) {
            if (cond_wait(wcond) == 1) {
                Printf("cond wait failed\n");
                exit();
            }
        }
        // buffer is not full
        Printf("Producer %d inserted: %c\n", getpid(), msg[i]);

        buff -> c[buff -> head] = msg[i];
        buff -> head = (buff -> head + 1) % BUFFERSIZE;


        cond_signal(scond);
    
        if (lock_release(buff_lock) != SYNC_SUCCESS) {
             Printf("lock release failed\n");
        }

    }
    Printf("Producer number %d completed \n", getpid());

    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }
}
