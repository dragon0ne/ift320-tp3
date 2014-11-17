// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void SyscallHandler(int);
void ErrorHandler(ExceptionType);
void Exit();
SpaceId Exec();

void Create();
void Open();
void Read();
void Write();
void Close();
void ModifyRegister();
void CopyFromUser(int, char*, int);
void CopyToUser(int, char*, int);

void func(int space);








void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if (which == SyscallException) 
    {	
		SyscallHandler(type);	
	}

	else
	{
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}

void
SyscallHandler(int type)
{
	switch (type) 
	{	
	
		case SC_Halt :
			DEBUG('a', "Shutdown, initiated by user program.\n");
			printf("HALT !!!!! \n");
			interrupt->Halt();
			break;
		case SC_Exit :
			Exit();
			break;
		case SC_Exec :
			Exec();
			break;
		case SC_Create :
			Create();
			break;
		case SC_Open :
			Open();
			break;
		case SC_Read :
			Read();
			break;
		case SC_Write :
			Write();
			break;
		case SC_Close :
			Close();
			break;
	
	}
	ModifyRegister();
}

void Exit()
{
	currentThread->RemoveAllOpenFiles();
	RemoveUserThread(currentThread);
	
	printf("Thread  %s terminé : ", currentThread->getName());
	printf("\n\n--EXIT---\n\n\n ");

	currentThread->Finish();

}
SpaceId Exec()
{
  
	int adress = machine->ReadRegister(4);
	
	char* name = new char[128];
	printf("Exec\n");

    OpenFile* openFile = fileSystem->Open(name);
	if (openFile == NULL) {
		printf("Impossible d'ouvrir :  %s\n", name);
		return -1;
	}
	else 
	{
		currentThread->AddOpenFile(openFile);
		
		Thread *thread = new Thread(name);
		thread->space = new AddrSpace(openFile);
		
		

		//récupérer le numéro du processus et l'écrire dans le registre utilisateur
		SpaceId value = addUserThread(thread);	
		machine->WriteRegister(2, value);		
		
		
		thread->Fork(func, 0);
		
		delete openFile;
		return value;
	}



}
void func(int space)
{
	currentThread->space->InitRegisters();
	currentThread->space->RestoreState();
	machine->Run();
}



void Create()
{

	// récupérer le nom du fichier
	int adress = machine->ReadRegister(4);
	char name[128];
	CopyFromUser(adress, name, 128);


	fileSystem->Create(name, 0);
	printf ("Creation de %s \n", name);

}
void Open()
{
	//Récupération du nom du fichier
	int adress = machine->ReadRegister(4);
	char name[128];	
	CopyFromUser(adress, name, 128);

	OpenFile* openFile = fileSystem->Open(name);
	if (openFile == NULL) 
	{
		printf("Impossible d'ourir le fichier :  %s \n", name);
	}
	else 
	{
		// Placer dans la table des fichiers ouverts
		int index = currentThread->AddOpenFile(openFile);
		machine->WriteRegister(2, index);
	}

}
void Read()
{
	int adress = machine->ReadRegister(4);
	int size = machine->ReadRegister(5);
	int index = machine->ReadRegister(6);
	char *text = new char[size];

    CopyToUser(adress, text, size);

    if (index == ConsoleInput)
    {
		printf("Console input : %s", text);
	}
	else
	{
	
		OpenFile* openFile = currentThread->GetOpenFile(index);			
		openFile->Read(text, size); 
	}



}
void Write()
{

	int adress = machine->ReadRegister(4);
	int size = machine->ReadRegister(5);
	int index = machine->ReadRegister(6);
	char* text = new char[size];

	CopyFromUser(adress, text, size);

	if (index == ConsoleOutput)
	{
		printf("Console output : %s", text);
	}
	else 
	{	
		OpenFile* openFile = currentThread->GetOpenFile(index);	
		openFile->Write(text, size);
	}
}


void Close()
{
	int index = machine->ReadRegister(4);
	currentThread->RemoveOpenFile(index);

}

void CopyFromUser(int adress, char *buffer, int size)
{
	int value = 0;
	int i = 0;

	do
	{
		machine->ReadMem(adress + i, 1, &value);
		buffer[i] = value;
		i++;
	}
	while(i < size && value != 0);

}


void CopyToUser(int adress, char *buffer, int size)
{
	int i = 0;
	int value = 0;
	for (i = 0; i < size; i++)
	{
		value = buffer[i];
		machine->WriteMem(adress + i, 1, value);
	}

}



void
ErrorHandler(ExceptionType which)
{
	switch(which) {
		case PageFaultException :
			printf("PageFaultException");
			break;
		case ReadOnlyException :
			printf("ReadOnlyException");
			break;
		case BusErrorException :
			printf("BusErrorException");
			break;
		case AddressErrorException :
			printf("AddressErrorException");
			break;
		case OverflowException :
			printf("OverflowException");
			break;
		case IllegalInstrException :
			printf("IllegalInstrException");
			break;
		case NumExceptionTypes :
			printf("NumExceptionTypes");
			break;
		default:
			break;
	}
	
	interrupt->Halt();
}
void
ModifyRegister()
{
	int pc;
	pc = machine -> ReadRegister(PCReg);
	machine -> WriteRegister(PrevPCReg,pc);
	pc = machine->ReadRegister(NextPCReg);
	machine->WriteRegister(PCReg,pc);
	pc+=4;
	machine-> WriteRegister(NextPCReg,pc);
}
