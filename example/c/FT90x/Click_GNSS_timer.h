/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_GNSS_types.h"

uint32_t timerCounter = 0;

static void gnss_configTimer()
{
    TIMER_CONTROL_0 = 2; 
    TIMER_SELECT = 0; 
    TIMER_PRESC_LS = 80; 
    TIMER_PRESC_MS = 195; 
    TIMER_WRITE_LS = 1; 
    TIMER_WRITE_MS = 0; 
    TIMER_CONTROL_3 = 0;
    TIMER_CONTROL_4 |= 17;
    TIMER_CONTROL_2 |= 16;
    TIMER_INT |= 2;
    TIMER_CONTROL_1 |= 1;
    IRQ_CTRL &= ~((uint32_t)1 << GLOBAL_INTERRUPT_MASK );
}

void Timer_interrupt() iv IVT_TIMERS_IRQ
{
    if (TIMER_INT_A_bit)
    { 
        TIMER_INT = (TIMER_INT & 0xAA) | (1 << 0);
    }
	timerCounter++;
    gnss_tick();
}
