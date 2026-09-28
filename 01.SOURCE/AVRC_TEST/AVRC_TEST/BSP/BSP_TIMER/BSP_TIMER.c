#include "BOARD.h"
#include "BSP_TIMER.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t sys_time_count = 0u;
extern volatile uint16_t	app_button_timer_count;
#define F_CPU 8000000UL

void BSP_Timer1_Init(void)
{
	uint8_t sreg = SREG;
	cli();

	sys_time_count = 0u;


	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1  = 0x0000;

	TCCR1B |= (1u << WGM12); 

	
	
	OCR1A = (uint16_t)(F_CPU / 64UL / 1000UL - 1UL);

	
	#if defined(TIMSK1)
	TIMSK1 |= (1u << OCIE1A);
	#else

	TIMSK  |= (1u << OCIE1A);
	#endif

	TCCR1B |= (1u << CS11) | (1u << CS10);

	
	SREG = sreg;
}


ISR(TIMER1_COMPA_vect)
{
	sys_time_count++;
	if (0 < app_button_timer_count) app_button_timer_count--;
}


uint32_t BSP_GetSysTimeMs(void)
{
	uint32_t t;
	uint8_t sreg = SREG;
	cli();
	t = sys_time_count;
	SREG = sreg;

	return t;
}

void BSP_DelayMs(uint32_t delayMs)
{
	uint32_t start = BSP_GetSysTimeMs();

	while ((uint32_t)(BSP_GetSysTimeMs() - start) < delayMs) {
		
	}
}


