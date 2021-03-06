/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                                  G A T E                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

/** \brief Interrupt handling base class
 *
 * Class Gate is the superclass of a set of classes that are able to handle 
 * interrupts. Every subclass of Gate has to implement method trigger() that 
 * implements the appropriated behavior of the handler.
 */

class Gate : public Chain {
private:
	/** \brief current queue state
	 *
	 * **/
	bool isQueued;

public:
  /**\brief Default Constructor
   *
   * Sets this gate to be unqueued
   **/
   Gate() : isQueued(false) {}

  /** \brief Destructor
   *
   * does nothing
   **/
  virtual ~Gate(){
  }

  /** \brief Immediate part of interrupt handling
   *
   * To enalbe different behavior according to the occured interrupt this
   * method has to be implemented in subclasses of Gate.
   *
   * @return TRUE if method epilogue() has to be executed afterwards.
   */
   virtual bool prologue() = 0;

  /**\brief schedulable part of interrupt handling
   * 
   * Just as method prologue() it 
   * has to be implemented in the subclasses of Gate.
   *
   **/
   virtual void epilogue() = 0;

   /** \brief set queuing status
    *
    * \param q new queuing state
    **/
   void
   queued(bool q)
   {
   	   isQueued = q;
   }

   /** \brief get queuing status
    *
    *
    * \return true if queued, false otherwise
    **/
   bool
   queued()
   {
	   return isQueued;
   }
};

#endif
