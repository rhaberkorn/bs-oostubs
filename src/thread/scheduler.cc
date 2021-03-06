/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "thread/scheduler.h"
#include "thread/entrant.h"

void
Scheduler::schedule()
{
	Entrant *e = (Entrant *)threads.dequeue();
	if (e)
		go(*e);
	/*else
		while (42);*/
}

void
Scheduler::ready(Entrant& that)
{
	threads.enqueue(&that);
}

void
Scheduler::exit()
{
	Entrant *head = (Entrant *)threads.dequeue();
	if (head)
		dispatch(*head);
	else
		while (42);
}

void
Scheduler::kill(Entrant* that)
{
	if (that == active())
		exit();
	else
		threads.remove((Entrant *)that);
}

void
Scheduler::resume()
{
	Entrant *next;

	if (active() && /* in case, the watch is wound up and interrupts enabled
			 * after the first thread is ready but was not yet scheduled
		 	 * (or resume() was simply called before schedule()) */
	    (next = (Entrant *)threads.dequeue())) {
		threads.enqueue(active());
		dispatch(*next);
	}
}
