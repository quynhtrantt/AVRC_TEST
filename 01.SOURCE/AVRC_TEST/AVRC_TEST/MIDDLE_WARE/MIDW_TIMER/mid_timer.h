#ifndef MID_TIMER_H_
#define MID_TIMER_H_


#include <stdint.h>

typedef struct
{
	uint32_t start_time;
	uint32_t timeout;
} Middleware_Timer_t;

void Middleware_Timer_Start(Middleware_Timer_t *timer, uint32_t timeout_ms);

uint8_t Middleware_Timer_IsExpired(Middleware_Timer_t *timer);

uint32_t Middleware_Timer_GetElapsed(Middleware_Timer_t *timer);

void Middleware_Timer_Reset(Middleware_Timer_t *timer);

#endif

