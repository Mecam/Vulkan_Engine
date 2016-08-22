#pragma once
#ifdef _DEBUG
#include <vector>
#include <stdexcept>
using namespace std;

/*Required Validation Layers and Extensions*/
static vector<char*> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};
static vector<char*> debugExtensions = {VK_EXT_DEBUG_REPORT_EXTENSION_NAME};

/*Debug Report Functions Obtained from Instance*/

static PFN_vkCreateDebugReportCallbackEXT vkeCreateDebugReportCallbackEXT;
static PFN_vkDebugReportMessageEXT vkeDebugReportMessageEXT;
static PFN_vkDestroyDebugReportCallbackEXT vkeDestroyDebugReportCallbackEXT;

static void loadDebugFuncs(VkInstance instance)
{
	vkeCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
	vkeDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT"));
	vkeDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallbackFunc(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
	throw runtime_error(string(pLayerPrefix) + ":" + string(pMessage));
	return VK_FALSE;
}

class egDebugCallback
{
public:
	void create(VkInstance* instance)
	{
		VkDebugReportCallbackCreateInfoEXT callbackCreateInfo = {};
		callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		callbackCreateInfo.pfnCallback = &debugReportCallbackFunc;
		callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |
								   VK_DEBUG_REPORT_WARNING_BIT_EXT |
			                       VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;

		if (vkeCreateDebugReportCallbackEXT(*instance, &callbackCreateInfo, nullptr, &this->debugReportCallback) != VK_SUCCESS)
			throw runtime_error("Failed to set up debug callback!");

		pInstance = instance;
	}
	
	~egDebugCallback()
	{
		if(!vkeDestroyDebugReportCallbackEXT)
			vkeDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(*pInstance, "vkDestroyDebugReportCallbackEXT"));
		
		if (pInstance)
			vkeDestroyDebugReportCallbackEXT(*pInstance, this->debugReportCallback, nullptr);
	}
private:
	VkDebugReportCallbackEXT debugReportCallback = VK_NULL_HANDLE;
	VkInstance* pInstance = nullptr;
};
#endif
