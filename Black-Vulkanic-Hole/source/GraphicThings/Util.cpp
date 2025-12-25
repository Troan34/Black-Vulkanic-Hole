#include "Util.hpp"

#ifdef _DEBUG

#define VkCall(x) \
		VkResult err = x;\
		VkGetError(#x, __FILE__, __LINE__, err);
#else

#define VkCall(x) x;

#endif

void VkGetError(const char* function, const char* file, const int line, const VkResult err)
{
	if (err != VkResult::VK_SUCCESS)
	{
		std::cerr << "Vulkan error: " << err << " in file: " << file << " at line " << line;
	}
}

std::optional<fs::path> FindFile(File file)
{
	fs::path path_(fs::current_path());

	bool IDontKnowHowToNameThis = true;

	while (path_.parent_path() == "Black-Vulkanic-Hole" or IDontKnowHowToNameThis == true)
	{
		path_ = path_.parent_path();
		if (path_.filename() == "Black-Vulkanic-Hole")
			IDontKnowHowToNameThis = false;
	}

	//After these loops we have reached the top of the files


	switch (file)
	{
		case File::VERT_SHADER:
			path_ /= "Black-Vulkanic-Hole/source/GraphicThings/Shader/Shader.vert.spv";
			break;
		case File::FRAG_SHADER:
			path_ /= "Black-Vulkanic-Hole/source/GraphicThings/Shader/Shader.frag.spv";
			break;
	}

	if (fs::exists(path_))
		return path_;
	else
		return std::nullopt;
}

bool checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (auto layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound) return false;
	}

	return true;
}
