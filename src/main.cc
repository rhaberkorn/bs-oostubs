/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                              M A I N                                      *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "machine/multiboot.h"

#include "machine/cpu.h"
#include "machine/plugbox.h"
#include "machine/pic.h"

#include "device/cgastr.h"
#include "device/panic.h"
#include "device/watch.h"

#include "guard/guard.h"

#include "syscall/guarded_scheduler.h"
#include "syscall/guarded_keyboard.h"

#include "user/task6.h"

CPU cpu;
PIC pic;
Plugbox plugbox;

CGA_Stream kout;

Panic panic;
Watch watch(20000);

Guard guard;
Guarded_Scheduler scheduler;
Guarded_Keyboard keyboard;

/* METHODS  */

extern "C" void kernel(uint32_t magic, const Multiboot_Info* addr);

/** \brief kernel entry point
 *
 * This is the entry point of the operating system.  If this function returns
 * all interrupts will be disabled and the cpu will be halted.
 *
 * \param magic bootloader magic value
 * \param addr address of multiboot info structure
 **/

void kernel(uint32_t magic, const Multiboot_Info* addr)
{
	Task6 task;

	watch.windup();
	keyboard.plugin();

	cpu.enable_int();

	scheduler.ready(task);
	scheduler.schedule();
}
