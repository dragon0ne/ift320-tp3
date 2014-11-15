// scheduler.h 
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"

// The following class defines the scheduler/dispatcher abstraction -- 
// the data structures and operations needed to keep track of which 
// thread is running, and which threads are ready but not running.

class Scheduler {
  public:
    Scheduler();			// Initialize list of ready threads 
    ~Scheduler();			// De-allocate ready list

    void ReadyToRun(Thread* thread);	// Thread can be dispatched.
    Thread* FindNextToRun();		// Dequeue first thread on the ready 
					// list, if any, and return thread.
    void Run(Thread* nextThread);	// Cause nextThread to start running
    void Print();			// Print contents of ready list
    
  private:
    List *readyList;  		// queue of threads that are ready to run,
				// but not running
	class PlanificationAlgorithm
	{
		public:
			virtual Thread* FindNextToRun(List *readyList) 
			{
				return (Thread *)readyList->Remove();
			}
	};
		
	PlanificationAlgorithm *algo;
	
	class RoundRobin : public PlanificationAlgorithm
	{
		public:
			virtual Thread* FindNextToRun(List *readyList)
			{	
				if(readyList->IsEmpty())
					return NULL;
				return (Thread *)readyList->Remove();
			}
	};
	
	class StaticPriority : public PlanificationAlgorithm
	{
		public:
			virtual Thread* FindNextToRun(List *readyList)
			{	
				ListElement *ptr = readyList->first;
				Thread *retained = (Thread*) ptr->item;
				for (*ptr; ptr != NULL; ptr = ptr->next) 
				{
				   Thread *current = (Thread *)ptr;
				   if(current->getPriority() > retained->getPriority())
						retained = current;
				}
				
				return retained;
			}
	};
	
	class DynamicPriority : public PlanificationAlgorithm
	{
		public:
			virtual Thread* FindNextToRun(List *readyList)
			{	
				return (Thread *)readyList->Remove();
			}
	};
	
};

#endif // SCHEDULER_H
