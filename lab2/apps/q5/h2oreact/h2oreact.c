#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "q5_header.h"

void main(int argc, char* argv[]) {
        
    sem_t s_procs_completed;
    sem_t h2o;
    sem_t h2;
    sem_t o2;
    int h2o_num;

	if (argc != 6) { 
		Printf("Usage: "); Printf(argv[0]); Printf("FILENAME_TO_RUN, h_mem, s_procs_completed, h2o, h2, o2, h2o_num\n"); 
		Exit();
	}    

    s_procs_completed = dstrtol(argv[1], NULL, 10);
    h2o = dstrtol(argv[2], NULL, 10);
    h2 = dstrtol(argv[3], NULL, 10);
    o2 = dstrtol(argv[4], NULL, 10);
    h2o_num = dstrtol(argv[5], NULL, 10);

    while(h2o_num > 1) {
        if(sem_wait(h2o) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        } 
        if(sem_wait(h2o) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        }
        if(sem_signal(h2) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        } 
        if(sem_signal(h2) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        }
        if(sem_signal(o2) != SYNC_SUCCESS) {
            Printf("h2o reaction failed\n");
            Exit();
        }  
        h2o_num -= 2;
        Printf("2 H2O -> 2 H2 + O2 reacted, PID: %d\n", getpid());
    }
    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }
}