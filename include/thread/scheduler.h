/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
#include "thread/entrant.h"
#include "object/queue.h"
 
/** \brief Simple FIFO scheduler **/
class Scheduler : protected Dispatcher {
private:
  /** Queue of threads that are ready to be processed
   * **/
  Queue threads;

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
  void ready(Entrant& that);

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
   */
  void kill(Entrant* that);

  /** \brief Use the scheduling algorithm to get the next thread and
   * resumes with that thread.
   **/
  void resume();
};

#endif
