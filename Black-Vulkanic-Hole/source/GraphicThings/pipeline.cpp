#include "pipeline.hpp"


namespace engine
{
	std::vector<char> Pipeline::ReadFile(const std::string& path)
	{
		fs::path path_(fs::current_path());
		
		path_ = path_.parent_path();
		path_ = path_ / "Black-Vulkanic-Hole/source" / path;

		std::ifstream File{};
		File.open(path_, std::ios::ate | std::ios::binary);
	   
		if (!File.is_open())
		{
			throw std::runtime_error("Failed to open file: " + path);
		}

		size_t FileSize = static_cast<size_t>(File.tellg());

		std::vector<char> Buffer(FileSize);

		File.seekg(0);//put the reading pointer at 0 (start at the start)
		File.read(Buffer.data(), FileSize);

		File.close();

		return Buffer;
	}
	void Pipeline::CreateGraphicsPipeline(const std::string& VertFilePath, const std::string& FragFilePath)
	{
		auto VertShader = ReadFile(VertFilePath);
		auto FragShader = ReadFile(FragFilePath);

		std::cout << "Vert Shader size: " << VertShader.size() << '\n';
		std::cout << "Frag Shader size: " << FragShader.size() << '\n';
	}
	Pipeline::Pipeline(const std::string& VertFilePath, const std::string& FragFilePath)
	{
		CreateGraphicsPipeline(VertFilePath, FragFilePath);
	}
}