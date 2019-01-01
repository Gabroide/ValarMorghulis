#ifndef __ModuleInput_h__
#define __ModuleInput_h__

#include "Module.h"
#include "Point.h"

#include "SDL\include\SDL_scancode.h"

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	virtual ~ModuleInput();

	bool			Init()								override;
	bool			Start()								override;
	bool			CleanUp()							override;
	bool			GetWindowEvent(EventWindow code)	const;

	update_status	PreUpdate()	override;

	const iPoint&	GetMouseMotion()					const;
	const iPoint&	GetMousePosition()					const;

public:
	KeyState GetKey(int id) const
	{

		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{

		return mouse_buttons[id - 1];
	}

	KeyState GetMouseWheelUsed() const
	{

		return mouse_wheel;
	}

private:
	bool		windowEvents[WE_COUNT];

	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	KeyState	mouse_wheel;

	iPoint		mouse_motion;
	iPoint		mouse;

private:
	KeyState*	keyboard;

};

#endif // __ModuleInpu_h__