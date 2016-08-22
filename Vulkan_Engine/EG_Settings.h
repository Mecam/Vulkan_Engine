#pragma once
/*Display*/
enum egDisplayModes
{
	EG_WINDOW_MODE_WINDOW,
	EG_WINDOW_MODE_FULLSCREEN,
	EG_WINDOW_MODE_WINDOWED_FULLSCREEN
};

class egDisplaySettings
{
public:
	unsigned short mWindowMode = EG_WINDOW_MODE_WINDOW;
	const char* windowTitle = "Window";
	int mWidth = 800;
	int mHeight = 600;
};