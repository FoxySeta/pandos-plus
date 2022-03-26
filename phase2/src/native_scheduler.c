/**
 * \file native_scheduler.c
 * \brief Schedule awating processes.
 *
 * \author Luca Tagliavini
 * \date 22-03-2022
 */

#include "native_scheduler.h"
#include "os/scheduler.h"
#include "os/util.h"
#include "umps/const.h"
#include "umps/cp0.h"
#include "umps/libumps.h"

#define TIMER_VALUE 100
inline void reset_timer() { setTIMER(TRANSLATE_TIME(TIMER_VALUE)); }

void scheduler_wait()
{
    /* setSTATUS(getSTATUS() | STATUS_IEc | STATUS_IM_MASK); */
    /* setSTATUS(getSTATUS() | STATUS_IEc); */
    //reset_timer();
    /* while(1) */
    WAIT();
}

void scheduler_takeover()
{
    pandos_kprintf(":: letting pid:%d take over (%p)\n", active_process->p_pid,
                   active_process);
    /* Enable interrupts */
    active_process->p_s.status |= STATUS_IEp;
    LDST(&active_process->p_s);
    /* Enable the processor Local Timer */
    if (!active_process->p_prio)
        active_process->p_s.status |= STATUS_TE;
}

void scheduler_panic(const char *msg)
{
    pandos_kprintf("PANIC: %s", msg);
    PANIC();
}
