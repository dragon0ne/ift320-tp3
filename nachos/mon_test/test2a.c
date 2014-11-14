/* 
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"

int
main()
{
	OpenFileId input = ConsoleInput;
	OpenFileId output = ConsoleOutput;
	int i;
   
	for(i =1; i<10;i++)
		Write("CECI EST UN TEST\n", 17, ConsoleOutput);     

   Exit(0);
    
}
