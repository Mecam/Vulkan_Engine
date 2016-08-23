#include <stdexcept>
#include "EG_Engine.h"

void egEngine::run()
{
	init();
	mainLoop();
}

 

void egEngine::init()
{
	glfwInit();
	createVulkanInstance();
	setupValidation();
	setupWindow();
}

void egEngine::mainLoop()
{
	while (!this->mWindow.shouldClose())
	{
		glfwPollEvents();
	}
}

void egEngine::createVulkanInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Engine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "EG";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	vector<const char*> instanceExtensions;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (size_t i = 0; i < glfwExtensionCount; ++i)
	{
		instanceExtensions.push_back(glfwExtensions[i]);
	}
	
#ifdef _DEBUG
	instanceExtensions.insert(instanceExtensions.end(), debugExtensions.begin(), debugExtensions.end());
#endif

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	
	instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

#ifdef _DEBUG
	instanceCreateInfo.enabledLayerCount = (uint32_t)validationLayers.size();
	instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
#endif
	 
	if (vkCreateInstance(&instanceCreateInfo, nullptr, &this->vulkanInstance) != VK_SUCCESS)
	{
		throw runtime_error("Failed to create instance!");
	}
}

void egEngine::setupValidation()
{
#ifdef _DEBUG
	loadDebugFuncs(this->vulkanInstance);
	this->mDebugCallback.create(&this->vulkanInstance);
#endif
}

void egEngine::setupWindow()
{
	this->mWindow.createWindow();
	this->mWindow.createSurface(&this->vulkanInstance);
}
