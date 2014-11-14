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
	char tampon[30];
	OpenFileId fich1,fich2;
   int i;
   
	fich1 = Open("original");
   Read(tampon, 30, fich1);
 
 	Create("NOUVEAU");
	fich2 = Open("NOUVEAU");
   
   for(i =1; i<10;i++)
			Write(tampon, 30, fich2);
  	Exit(0);
    
}
