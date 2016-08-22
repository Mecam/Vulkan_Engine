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
	unsigned short windowMode = EG_WINDOW_MODE_WINDOW;
	const char* windowTitle = "Window";
	int width = 800;
	int height = 600;
};