#pragma once
#include <vector>
#include "EG_Presentation.h"
#include "EG_Debug.h"
#include "EG_utils.h"

using namespace std;

class egEngine
{
public:
	void run();
private:
	void init();
	void mainLoop();

	/*Init*/
	void createVulkanInstance();
	void setupValidation();
	void setupWindow();
	egDeleter<VkInstance> vulkanInstance{vkDestroyInstance};
#ifdef _DEBUG
	egDebugCallback debugCallback;
#endif
	egWindow window;
};