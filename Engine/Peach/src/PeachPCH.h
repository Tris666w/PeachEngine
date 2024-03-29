#pragma once


#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <functional>
#include <SDL.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Logger.h"

#pragma region Templates & Macros
template<class T>
inline void SafeDelete(T& pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

#pragma endregion
