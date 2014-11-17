/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
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
	//printf("toto"); // Impossible de foutre un fucking printf ou un debug
	char tampon[30];
	//OpenFileId input = ConsoleInput;
    //OpenFileId output = ConsoleOutput;
	OpenFileId original, fich2;	 
   	int i;
    Create("Plop"); //fonctionne !!!
    original = Open("original"); // semble fonctionner !!!!

  



  // Write("HelloWorld\n",30,fich);   

   Read(tampon, 30, original);
 
 	
	fich2 = Open("original");
   
   //for(i =1; i<10;i++)
	 Write(tampon, 30, fich2);

// fermeture du fichier original
	 Close(original);






  /* for(i =1; i<3;i++)
   {
		Write("test", 30, fich);
   }*/

   // Exec("../../mon_test/mon_test1");
/*
	for(i=1; i<10;i++)
	{
 		Write("ceci est un test\n", 30, fich);
 	}*/
 /*  for(i=1; i<10;i++)
 	 Write("CECI EST UN TEST\n", 18, output);*/
/*   //Read(tampon, 17,fich);*/


    Exit(3); // fonctionne !
	//Halt();
    /* not reached */
}
