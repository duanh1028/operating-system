#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "q5_header.h"

void main(int argc, char* argv[]) {
    
    sem_t s_procs_completed;
    sem_t so4;
    int so4_num;

	if (argc != 4) { 
		Printf("Usage: "); Printf(argv[0]); Printf("FILENAME_TO_RUN, h_mem, s_procs_completed, so4, so4_num\n"); 
		Exit();
	} 

    s_procs_completed = dstrtol(argv[1], NULL, 10);
    so4 = dstrtol(argv[2], NULL, 10);
    so4_num = dstrtol(argv[3], NULL, 10);

    while(so4_num > 0) {
        if(sem_signal(so4) != SYNC_SUCCESS) {
            Printf("so4 injection failed\n");
            Exit();
        } else {
            Printf("so4 injected into Radeon atmosphere, PID: %d\n", getpid());
            so4_num--;
        }
    }

    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }
}