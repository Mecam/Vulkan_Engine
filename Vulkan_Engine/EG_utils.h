#pragma once
#include<vector>
#include<functional>
#include<vulkan\vulkan.h>


using namespace std;

template<typename T>
class egEnumList
{
public:
	egEnumList(function<void(uint32_t*, T*)> getEnumFunc)
	{
		getEnumFunc(&this->count, nullptr);
		data.resize(count);
		getEnumFunc(&this->count, this->list.data(););
	}

	egEnumList(function<void(VkInstance, uint32_t*, T*)> getEnumFunc, VkInstance& instance)
	{
		getEnumFunc(instance, &this->count, nullptr);
		data.resize(count);
		getEnumFunc(instance, &this->count, this->list.data(););
	}

	egEnumList(function<void(VkPhysicalDevice, uint32_t*, T*)> getEnumFunc, VkPhysicalDevice& physicalDevice)
	{
		getEnumFunc(physicalDevice, &this->count, nullptr);
		data.resize(count);
		getEnumFunc(physicalDevice, &this->count, this->list.data(););
	}

	egEnumList(function<void(const char*, uint32_t*, T*)> getEnumFunc, const char* layerName)
	{
		getEnumFunc(layerName, &this->count, nullptr);
		data.resize(count);
		getEnumFunc(layerName, &this->count, this->list.data(););
	}

	egEnumList(function<void(VkPhysicalDevice, const char*, uint32_t*, T*)> getEnumFunc, VkPhysicalDevice& physicalDevice, const char* layerName)
	{
		getEnumFunc(physicalDevice, layerName, &this->count, nullptr);
		data.resize(count);
		getEnumFunc(physicalDevice, layerName, &this->count, this->list.data(););
	}

	operator vector<T> const()
	{
		return list;
	}
private:
	vector<T> list;
	uint32_t count;
};

template<typename T>
class egDeleter
{
public:
	egDeleter(function<void(T, VkAllocationCallbacks*)> deleterFunc) : deleter(deleterFunc){}

	operator T const()
	{
		return object;
	}

	T* operator &() 
	{
		return &object;
	}

	~egDeleter()
	{
		deleter(object, nullptr);
	}

private:
	T object = VK_NULL_HANDLE;
	function<void(T, VkAllocationCallbacks*)> deleter;
};