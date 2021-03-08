#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "q5_header.h"

void main (int argc, char *argv[])
{

  int numprocs = 5;               // Used to store number of processes to create
  //int i;

  sem_t s_procs_completed;        // Semaphore used to wait until all spawned processes have completed


  char s_procs_completed_str[10]; // Used as command-line argument to pass page_mapped handle to new processes

  sem_t o2;
  sem_t h2o;
  sem_t so4;
  sem_t h2so4;
  sem_t so2;
  sem_t h2;

  char o2_str[10];
  char h2o_str[10];
  char so4_str[10];
  char h2so4_str[10];
  char so2_str[10];
  char h2_str[10];
  char h2o_num_str[10];
  char so4_num_str[10];
  char h2so4_num_str[10];

  int o2_num;
  int h2so4_num;
  int so2_num;
  int h2_num;
  int h2o_num;
  int so4_num;

  //Printf("has anything started?\n");
  if (argc != 3) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number of processes to create>\n");
    Exit();
  }
  
  // Convert string from ascii command line argument to integer number
  h2o_num = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  so4_num = dstrtol(argv[2], NULL, 10);
 
  if(h2o < 0 || so4 < 0) {
    Printf("Cannot create negative number of h2o or so4\n");
    Exit();
  }
  
  so2_num = so4_num;
  if(h2o_num % 2 == 0) {
    h2_num = h2o_num;
  } else {
    h2_num = h2o_num - 1;
  }
  o2_num = so4_num + h2o_num / 2;

  h2so4_num = min(min(o2_num, so2_num), h2_num);

 
  Printf("DEBUGGING USE: there are %d so2, %d h2, %d o2, %d h2so4\n\n", so2_num, h2_num, o2_num, h2so4_num);




  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  if ((s_procs_completed = sem_create(-(numprocs-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }

  if ((h2o = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in h2o\n");
    Exit();
  }

  if ((o2 = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in o2\n");
    Exit();
  }

  if ((so2 = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in o2\n");
    Exit();
  }

  if ((so4 = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in o2\n");
    Exit();
  }

  if ((h2 = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in o2\n");
    Exit();
  }

  if ((h2so4 = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in o2\n");
    Exit();
  }

  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings. 
  ditoa(s_procs_completed, s_procs_completed_str);
  ditoa(h2, h2_str);
  ditoa(h2o, h2o_str);
  ditoa(so4, so4_str);
  ditoa(so2, so2_str);
  ditoa(h2so4, h2so4_str);
  ditoa(o2, o2_str);

  ditoa(h2o_num, h2o_num_str);
  ditoa(so4_num, so4_num_str);
  ditoa(h2so4_num, h2so4_num_str);
  
  Printf("Creating %d H2Os AND %d SO4s\n", h2o_num, so4_num);

  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.
 // for(i=0; i<numprocs; i++) {
    process_create(H2OINJECT, s_procs_completed_str, h2o_str, h2o_num_str, NULL);
    //Printf("why not consuemr?\n");
    process_create(SO4INJECT, s_procs_completed_str, so4_str, so4_num_str, NULL);
    //Printf("has consumer been ran\n");
    process_create(H2OREACT, s_procs_completed_str, h2o_str, h2_str, o2_str, h2o_num_str, NULL);
    
    process_create(SO4REACT, s_procs_completed_str, so4_str, o2_str, so2_str, so4_num_str, NULL);
    
    process_create(H2SO4REACT, s_procs_completed_str, h2so4_str, h2_str, o2_str, so2_str, h2so4_num_str, NULL);


  ///  Printf("Process %d created\n", i);
 // }

  // And finally, wait until all spawned processes have finished.
  if (sem_wait(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
    Exit();
  }
  Printf("%d H2O's left over. %d H2's left over. %d O2's left over. %d SO2's left over. ", h2o_num - h2so4_num, h2_num - h2so4_num, o2_num - h2so4_num, so2_num - h2so4_num);
  Printf("%d H2SO4's created.\n", h2so4_num);
  Printf("All other processes completed, exiting main process.\n");
}
