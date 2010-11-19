/* Poor Man's Operation System 
/
/ This is not complete code...
/
/    (Aaron Baranoff)
/
*/

typedef struct {
  void (*task)(void);
  unsigned int time_between; /* 0 means everytime */
  unsigned int internal_time;   /* used to count dount howmany ticks are left - initial value is ignored*/
} TASK_DATA;

