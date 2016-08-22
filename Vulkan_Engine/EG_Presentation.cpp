#include "EG_Presentation.h"

void egWindow::createWindow()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);

	int width = 0, height = 0;
	switch (this->mWindowSettingsCurrent.mWindowMode)
	{
	case EG_WINDOW_MODE_WINDOW:
		width = this->mWindowSettingsCurrent.mWidth;
		height = this->mWindowSettingsCurrent.mHeight;
		break;

	case EG_WINDOW_MODE_WINDOWED_FULLSCREEN:
		width = vidMode->width;
		height = vidMode->height;
		break;

	case EG_WINDOW_MODE_FULLSCREEN:
		break;
	}
	this->mWindowPtr = glfwCreateWindow(width, height, this->mWindowSettingsCurrent.windowTitle, this->mWindowSettingsCurrent.mWindowMode > 0 ? monitor : nullptr, nullptr);
}

void egWindow::createWindow(egDisplaySettings windowSettings)
{
	this->mWindowSettingsCurrent = windowSettings;
	this->createWindow();
}

void egWindow::createSurface(VkInstance* instance)
{
	if (glfwCreateWindowSurface(*instance, this->mWindowPtr, nullptr, &this->mWindowSurface) != VK_SUCCESS)
	{
		throw runtime_error("Failed to Create Window Surface!");
	}
	mInstance = instance;
}

int egWindow::shouldClose()
{
	return glfwWindowShouldClose(this->mWindowPtr);
}

egWindow::~egWindow()
{
	if (mInstance)
	{
		vkDestroySurfaceKHR(*mInstance, this->mWindowSurface, nullptr);
	}
	if (mWindowPtr)
	{
		glfwDestroyWindow(this->mWindowPtr);
	}
}
 
