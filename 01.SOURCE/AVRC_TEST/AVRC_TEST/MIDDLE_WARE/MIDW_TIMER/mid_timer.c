#include "mid_timer.h"
#include "BSP_TIMER.h"

void Middleware_Timer_Start(Middleware_Timer_t *timer, uint32_t timeout_ms)
{
	if (timer == 0)
	{
		return;
	}

	timer->start_time = BSP_GetSysTimeMs();
	timer->timeout = timeout_ms;
}

uint8_t Middleware_Timer_IsExpired(Middleware_Timer_t *timer)
{
	uint32_t current_time;

	if (timer == 0)
	{
		return 0U;
	}

	current_time = BSP_GetSysTimeMs();

	if ((current_time - timer->start_time) >= timer->timeout)
	{
		return 1U;
	}

	return 0U;
}

uint32_t Middleware_Timer_GetElapsed(Middleware_Timer_t *timer)
{
	if (timer == 0)
	{
		return 0U;
	}
 
	return BSP_GetSysTimeMs() - timer->start_time;
}

void Middleware_Timer_Reset(Middleware_Timer_t *timer)
{
	if (timer == 0)
	{
		return;
	}

	timer->start_time = BSP_GetSysTimeMs();
}