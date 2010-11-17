/* recursive.cpp 
   example recursive code and rentrant code

*/
   

#include "stdafx.h"
#include "string.h"

#define MAX_DEPTH			256
#define MAX_FILE_NAME_LEN   256

static unsigned int depth;

struct
{
	char filename[MAX_FILE_NAME_LEN];
	int  line;
} log[MAX_DEPTH];

/* recursive function - it calls itself */
void recurFunc(int a)
{
	if (a != 0)
	{
		recurFunc(--a);
	}
}



volatile unsigned char lockvar;

/* unitialize variables for logging */
void initLog(void)
{
	lockvar = 0;
	depth = 0;
}

/* lock example */
void lock(void)
{
	/* might add block interrupts as well */
	do 
	{
		lockvar++;
		if (lockvar != 1)
		{
			lockvar--;
			/* optionally sleep */
		}
	}
	while (lockvar != 1);
}

/* unlock example */
void unlock(void)
{
	lockvar--;
	/* might add unblock interrupts as well */
}

/* function to do a circular log */
void logit(char *filename, int line)
{
	lock();
	strncpy(log[depth].filename,filename, MAX_FILE_NAME_LEN);
	log[depth].line = line;
	depth++;
	if (depth >= MAX_DEPTH)
	{
		depth = 0;
	}
	unlock();	
}

/* two task that may run at similair times */
void taskA(void)
{
	logit(__FILE__,__LINE__);
}

void taskB(void)
{
	logit(__FILE__,__LINE__);
}

int main(int argc, char* argv[])
{
	recurFunc(2);
	initLog();
	taskA();
	taskB();
	printf("Hello World!\n");
	return 0;
}
