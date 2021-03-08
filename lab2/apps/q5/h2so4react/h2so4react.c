#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "q5_header.h"

void main(int argc, char* argv[]) {
        
    sem_t s_procs_completed;
    sem_t h2so4;
    sem_t so2;
    sem_t o2;
    sem_t h2;
    int h2so4_num;
    int h2so4_count = 0;

	if (argc != 7) { 
		Printf("Usage: "); Printf(argv[0]); Printf("FILENAME_TO_RUN, h_mem, s_procs_completed, h2so4, h2, o2, h2so4_num\n"); 
		Exit();
	}    

    s_procs_completed = dstrtol(argv[1], NULL, 10);
    h2so4 = dstrtol(argv[2], NULL, 10);
    h2 = dstrtol(argv[3], NULL, 10);
    so2 = dstrtol(argv[4], NULL, 10);
    o2 = dstrtol(argv[5], NULL, 10);
    h2so4_num = dstrtol(argv[6], NULL, 10);

    while(h2so4_num > 0) {
        if(sem_signal(h2so4) != SYNC_SUCCESS) {
            Printf("h2so4 reaction failed\n");
            Exit();
        } 
        if(sem_wait(so2) != SYNC_SUCCESS) {
            Printf("so2 reaction failed\n");
            Exit();
        } 
        if(sem_wait(o2) != SYNC_SUCCESS) {
            Printf("o2 reaction failed\n");
            Exit();
        }  
        if(sem_wait(h2) != SYNC_SUCCESS) {
            Printf("h2 reaction failed\n");
            Exit();
        }  
        h2so4_num--;
        h2so4_count++;
        Printf("(%d)H2 + O2 + SO2 -> H2SO4 reacted, PID: %d\n", h2so4_count, getpid());
    }
    if (sem_signal(s_procs_completed) != SYNC_SUCCESS) {
        Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
        Exit();
    }
}