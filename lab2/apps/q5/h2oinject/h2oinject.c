#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "q5_header.h"

void main(int argc, char* argv[]) {
    
    sem_t s_procs_completed;
    sem_t h2o;
    int h2o_num;

	if (argc != 4) { 
		Printf("Usage: "); Printf(argv[0]); Printf("FILENAME_TO_RUN, h_mem, s_procs_completed, h2o, h2o_num\n"); 
		Exit();
	} 

    s_procs_completed = dstrtol(argv[1], NULL, 10);
    h2o = dstrtol(argv[2], NULL, 10);
    h2o_num = dstrtol(argv[3], NULL, 10);

    while(h2o_num > 0) {
        if(sem_signal(h2o) != SYNC_SUCCESS) {
            Printf("h2o injection failed\n");
            Exit();
        } else {
            Printf("H2O injected into Radeon atmosphere, PID: %d\n", getpid());
            h2o_num--;
        }
    }

    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }
}