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
	switch (this->windowSettingsCurrent.windowMode)
	{
	case EG_WINDOW_MODE_WINDOW:
		width = this->windowSettingsCurrent.width;
		height = this->windowSettingsCurrent.height;
		break;

	case EG_WINDOW_MODE_WINDOWED_FULLSCREEN:
		width = vidMode->width;
		height = vidMode->height;
		break;

	case EG_WINDOW_MODE_FULLSCREEN:
		break;
	}
	this->windowPtr = glfwCreateWindow(width, height, this->windowSettingsCurrent.windowTitle, this->windowSettingsCurrent.windowMode > 0 ? monitor : nullptr, nullptr);
}

void egWindow::createWindow(egDisplaySettings windowSettings)
{
	this->windowSettingsCurrent = windowSettings;
	this->createWindow();
}

void egWindow::createSurface(VkInstance* instance)
{
	if (glfwCreateWindowSurface(*instance, this->windowPtr, nullptr, &this->windowSurface) != VK_SUCCESS)
		throw runtime_error("Failed to Create Window Surface!");
	pInstance = instance;
}

int egWindow::shouldClose()
{
	return glfwWindowShouldClose(this->windowPtr);
}

egWindow::~egWindow()
{
	if (pInstance)
		vkDestroySurfaceKHR(*pInstance, this->windowSurface, nullptr);
	if (windowPtr)
		glfwDestroyWindow(this->windowPtr);
}
 
