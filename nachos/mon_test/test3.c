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
	int i;
	OpenFileId fich;

   Create("fichier1");
   fich = Open("fichier1");

	Exec("../mon_test/test3a",10);
	Exec("../mon_test/boucle",0);
	Exec("../mon_test/boucle",10);
	

   for(i=1; i<10;i++)
 		Write("ceci est un test\n", 17, fich);

   Exit(3);
    
}


