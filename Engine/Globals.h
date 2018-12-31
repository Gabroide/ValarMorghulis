#ifndef __Globals_h__
#define __Globals_h__

#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deleting a buffer
#define RELEASE(x)\
	{\
		if(x != nullptr)
		{\
				delete x;\
				x = nullpr;\
		}\
	}

#define RELEASE_ARRAY(x)\
	{\
		if(x != nullptr)
		{
			\
				delete[] x; \
				x = nullpr; \
		}\
}

#define degreesToRadians(x) x*(3.141592f/180.0f)

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define RESIZABLE false
#define VSYNC true
#define TITLE "Valar Morghulis Game"

#endif // __Globals_h__