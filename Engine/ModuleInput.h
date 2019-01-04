#ifndef __ModuleInput_h__
#define __ModuleInput_h__

#include "Module.h"
#include "Point.h"
#include "SDL_scancode.h"

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

	bool			Init()		override;
	bool			CleanUp()	override;
	bool			GetWindowEvent(EventWindow code) const; // Check for window events last frame

	update_status	PreUpdate()	override;
	
	void			DrawGUI();
	void			FileDropped(const char* ev);

	// Get mouse / axis position
	const int		GetMouseWheel() const;
	
	const fPoint&	GetMouseMotion() const;
	const fPoint&	GetMousePosition() const;
	
public:
	// Check key states from keyboard
	KeyState GetKey(int id) const {
		return keyboard[id];
	}

	// Check mouse key states
	KeyState GetMouseButtonDown(int id) const {
		return mouse_buttons[id - 1];
	}

private:
	bool		windowEvents[WE_COUNT];
	
	int			mouse_wheel = 0;
	
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	
	fPoint		mouse_motion;
	fPoint		mouse;

private:
	KeyState*	keyboard = nullptr;

};

#endif // __ModuleInpu_h__