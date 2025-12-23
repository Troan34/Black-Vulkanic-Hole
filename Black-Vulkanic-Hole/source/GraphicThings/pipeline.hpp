#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

namespace engine
{
	class Pipeline
	{
	private:
		static std::vector<char> ReadFile(const std::string& path);
		void CreateGraphicsPipeline(const std::string& VertFilePath, const std::string& FragFilePath);

	public:
		Pipeline(const std::string& VertFilePath, const std::string& FragFilePath);
	};
}