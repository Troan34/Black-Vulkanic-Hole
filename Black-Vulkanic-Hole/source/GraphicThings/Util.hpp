#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <iostream>
#include <filesystem>
#include <optional>
#include <sstream>
#include <memory>
#include <cassert>

namespace fs = std::filesystem;

//error checking in debug mode
#ifndef NDEBUG
#define VkCall(x) \
		VkGetError(#x, __FILE__, __LINE__, x);
#else
#define VkCall(x) x;
#endif


enum class File
{
	FRAG_SHADER,
	VERT_SHADER,
};


void inline VkGetError(const char* function, const char* file, const int line, const VkResult err)
{
	if (err != VkResult::VK_SUCCESS)
	{
		std::ostringstream ss;
		ss << "Vulkan error: " << err << " in file: " << file << " at line " << line;
		throw std::runtime_error(ss.str());
	}
}

std::optional<fs::path> FindFile(File file);
