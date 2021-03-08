#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "q5_header.h"

void main(int argc, char* argv[]) {
        
    sem_t s_procs_completed;
    sem_t so4;
    sem_t so2;
    sem_t o2;
    int so4_num;

	if (argc != 6) { 
		Printf("Usage: "); Printf(argv[0]); Printf("FILENAME_TO_RUN, h_mem, s_procs_completed, so4, o2, so4_num\n"); 
		Exit();
	}    

    s_procs_completed = dstrtol(argv[1], NULL, 10);
    so4 = dstrtol(argv[2], NULL, 10);
    so2 = dstrtol(argv[3], NULL, 10);
    o2 = dstrtol(argv[4], NULL, 10);
    so4_num = dstrtol(argv[5], NULL, 10);

    while(so4_num > 0) {
        if(sem_wait(so4) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        } 
        if(sem_signal(so2) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        } 
        if(sem_signal(o2) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        }  
        so4_num--;
        Printf("SO4 -> SO2 + O2 reacted, PID: %d\n", getpid());
    }
    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }
}