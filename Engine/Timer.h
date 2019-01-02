#ifndef __Timer_h__
#define __Timer_h__

#include "SDL.h"

class Timer
{
private:
	bool			timerRunning = false;

	Uint32			ms				= 0;
	Uint32			startingMs		= 0;
	Uint32			lastTicks		= 0;
	
public:

	void Start() 
	{
		timerRunning = true;
		startingMs = SDL_GetTicks();
	}

	Uint32 GetTicks() 
	{

		if (timerRunning) 
		{
			return SDL_GetTicks() - startingMs;
		}
		else 
		{
			return lastTicks - startingMs;
		}
	}

	Uint32 Read() 
	{
		return SDL_GetTicks() - startingMs;
	}

	void Stop() 
	{
		timerRunning = false;
		lastTicks = SDL_GetTicks();
	}
};

class TimerPerfomance
{
private:
	bool			timerRunning = false;

	Uint64			ms				= 0;
	Uint64			startingMs		= 0;
	Uint64			lastTicks		= 0;
	static Uint64	frequency;

public:

	void Start() 
	{
		timerRunning = true;
		startingMs = SDL_GetPerformanceCounter();
	}

	Uint64 GetTicks() 
	{
		if (timerRunning) 
		{
			return (SDL_GetPerformanceCounter() - startingMs) * 1000 / frequency;
		}
		else 
		{
			return (lastTicks - startingMs) * 1000 / frequency;
		}
	}

	Uint64 Read() 
	{
		return SDL_GetPerformanceCounter() - startingMs;
	}

	void Stop() 
	{
		timerRunning = false;
		lastTicks = SDL_GetPerformanceCounter();
	}

};

Uint64 TimerPerfomance::frequency = SDL_GetPerformanceFrequency();

#endif // __Timer_h__