#pragma once
#include "CoreMinimal.h"

template <typename T>
class  FJSingleTon
{
public:
	static T& GetInstance()
	{
		if (nullptr == Instance)
		{
			Instance = new T();
		}
		return *Instance;
	}

	static void ShutDown()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
	virtual ~FJSingleTon()
	{

	};
protected:
	FJSingleTon()
	{

	};
private:
	static T* Instance;
};
template <typename T> T* FJSingleTon<T>::Instance = nullptr;
