#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <filesystem>
#include "Windows.h"

#include "Util.hpp"

namespace fs = std::filesystem;

namespace engine
{

	class Pipeline
	{
	private:
		static std::vector<char> ReadFile(const File path);
		void CreateGraphicsPipeline();

	public:
		Pipeline();
	};
}