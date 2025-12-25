#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <iostream>
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

#ifdef _DEBUG

#define VkCall(x) \
		VkResult err = x;\
		VkGetError(#x, __FILE__, __LINE__, err);

static constexpr bool enableValidationLayers = true;

#else

static constexpr bool enableValidationLayers = false;
#define VkCall(x) x;

#endif

enum class File
{
	FRAG_SHADER,
	VERT_SHADER,
};

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

void VkGetError(const char* function, const char* file, const int line, const VkResult err);

std::optional<fs::path> FindFile(File file);

bool checkValidationLayerSupport();