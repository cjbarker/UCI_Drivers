
/* Poor Man's Operation System 
/
/ This is not complete code...
/
/    (Aaron Baranoff)
/
*/ 
#include <stdio.h>
#include "pmos.h"

extern void critical_tasks(void);

static void task1(void)
{

}

 
static void task2(void)
{

}
 
static void crit_task1(void)
{

  
}

// list of tasks with how ofter then need to run
TASK_DATA task_info[] = {
  {task1, ONE_MILLISEC , 0},
  {task2, ONE_SECOND , 0}
  };

TASK_DATA critical_task_info[] = { // every signal period
  // 3 Phase Task
  {crit_task1,0, 0},
  };

unsigned int last_time = 0;

// crtical tasks
void critical_tasks(void)
{
    int critical_task_num;
    // beteen each non-critical task check the critical ones
    for (critical_task_num = 0; critical_task_num < sizeof(critical_task_info)/sizeof(critical_task_info[0]); critical_task_num++)
    {
        (critical_task_info[critical_task_num].task)();
    }
  
}

int main()
{
  static unsigned int last_time = 0;
  int task_num;
  unsigned int present_time = READ_COUNTER();

  WRITE_FREQ(1000000); // init frequency 
  
  // stagger starting times of each task of 1/16 of a millisecond by priming the start time
  for (task_num = 0; task_num < sizeof(task_info)/sizeof(task_info[0]); task_num++)
  {
    task_info[task_num].internal_time = task_num * (ONE_MILLISEC/16);  
  }   
  
  // Main loop
  while (1)
  { 
    present_time = READ_COUNTER();
    

    
    // loop_through each task checking if enough time has passed 
    for (task_num = 0; task_num < sizeof(task_info)/sizeof(task_info[0]); task_num++)
    {
      // beteen each non-critical task check the critical ones
      critical_tasks();
      // run each non-critical task 
      
      // process ecah task in the scheduler
      if (task_info[task_num].internal_time < task_info[task_num].time_between)
      {
        task_info[task_num].internal_time += (present_time - last_time);
      }
      else
      {
        task_info[task_num].internal_time = 0;
        (task_info[task_num].task)();
      }
    }

    last_time = present_time;
  }
  
  return 0;
}