#pragma once
#define GLFW_INCLUDE_VULKAN
#include <stdexcept>
#include <GLFW\glfw3.h>
#include <vulkan\vulkan.h>
#include "EG_Settings.h"

using namespace std;

class egWindow
{
public:
	void createWindow();
	void createWindow(egDisplaySettings windowSettings);
	void createSurface(VkInstance* instance);
	//void updateWindowSettings(egDisplaySettings newWindowSettings);
	int shouldClose();
	~egWindow();
private:
	GLFWwindow* windowPtr = nullptr;
	VkSurfaceKHR windowSurface = VK_NULL_HANDLE;
	egDisplaySettings windowSettingsCurrent;
	VkInstance* pInstance = nullptr;
};