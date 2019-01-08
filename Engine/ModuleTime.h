#ifndef __ModuleTime_H__
#define __ModuleTime_h__

#include "Timer.h"
#include "Module.h"
#include "Globals.h"

enum class GameState 
{ 
	RUN = 0,
	PAUSE,
	STOP
};

class ModuleTime : public Module
{
public:
	ModuleTime();
	~ModuleTime();

	bool			Init()		override;
	bool			CleanUp()	override;

	update_status	Update()	override;
	
	void			StartGameClock();
	void			PauseGameClock(bool pause);
	void			StopGameClock();
	void			Step();

public:
	bool			nextFrame		= false;

	float			gameTimeScale	= 1.0f;
	float			gameTime		= 0.0f;
	float			gameDeltaTime	= 0.0f;
	float			realTime		= 0.0f;
	float			realDeltaTime	= 0.0f;

	int				FPS				= 0;
	
	unsigned		maxFps			= 144u;
	unsigned		totalFrames		= 0u;
	unsigned		realFrameCount	= 0u;

	GameState		gameState		= GameState::STOP;

	Timer			frameTimer;
	Timer			fpsTimer;

private:
	unsigned		frameCount		= 0u;

};

#endif // __ModuleTime_h__