/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                   G U A R D E D _ S C H E D U L E R                       *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __guarded_scheduler_include__
#define __guarded_scheduler_include__

#include "syscall/thread.h"
#include "thread/organizer.h"

/** \brief User interface to the Scheduler. 
 *
 * The defined methods are guarded but otherwise directly mapped to the methods 
 * of the superclasses Organizer respective Scheduler. 
 * Also Threads and Customers are handled instead of Entrants.
 **/
class Guarded_Scheduler : public Organizer{
public:
  /** \brief Start the scheduling by starting the first thread
   *
   * If there is one contained in the queue of the scheduler.
   **/ 
  void schedule();
  
  /** \brief Insert the specified thread into the ready queue
   *
   * \param that reference to the thread to be inserted
   **/
  void ready(Thread& that);
  
  /** \brief Remove the currently active thread from the queue
   *
   * If there are no more threads, wait for new threads to arive.
   **/
  void exit();

  /** \brief Remove the specified thread from the queue of processes.
   *
   * If the supplied entry is equal to the currently active coroutine, call exit().
   *
   * \param that reference of the thread to be killed.
   **/
  void kill(Thread* that);

  /** \brief Use the scheduling algorithm to get the next thread and
   * resume with that thread.
   **/
  void resume();

  /** \brief get the currently active Thread
   *
   * \return the current Thread
   **/
  Thread* active()
  {
	return (Thread *)Organizer::active();
  }
};

#endif
