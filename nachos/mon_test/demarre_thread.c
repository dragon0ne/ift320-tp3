/* 
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"
int i,j,k ;
int a,b,c;
char tampon[10],t1[10];
OpenFileId fich;

fct1()
{
 	a=0;
 	b=0;
 	c=0; 
  while(1)
  {   for (k=0;k<1000000; k++)
  		{
			a++; b++; c = a + b;
		}
	}
   Exit(0);
}

fct2()
{
   tampon[0]='t';tampon[1]='i';tampon[2]='t';tampon[3]='o';tampon[4]=0;
     for(i =1; i<10;i++)
			Write(tampon, 4, fich);     
   Exit(0);
    
}

fct3()
{
   t1[0]='z';t1[1]='z';t1[2]='z';t1[3]='\n';;
     for(i =1; i<10;i++)
			Write(t1, 4, fich);     
   Exit(0);
    
}

int main()
{  int toto;

	Create("tito");
   fich = Open("tito");
	
	Fork(fct1);
 	Fork(fct2);
 	Fork(fct3);
	while (i < 10000)
	  {i++;}
   Exit(0);    
}

