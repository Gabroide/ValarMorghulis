#ifndef __Timer_h__
#define __Timer_h__

class Timer
{
public:
	Timer();
	~Timer();

	// Timer in miliseconds
	void	Start();
	void	StartPrecise();


	int		Read();
	int		Stop();
	int		startTime			= 0;
	int		timeSpent			= 0;
	
	bool	timerRunning		= false;
	bool	timerPreciseRunning = false;

	double	ReadPrecise();
	double	StopPrecise();
	double	startTimePrecise	= 0;
	double	timeSpentPrecise	= 0;

};

#endif // __Timer_h__