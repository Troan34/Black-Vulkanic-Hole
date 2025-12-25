#include "pipeline.hpp"


namespace engine
{
	std::vector<char> Pipeline::ReadFile(const File file)
	{
		std::ifstream File{};

		fs::path path_;

		try
		{
			path_ = FindFile(file).value();
		}
		catch (const std::bad_optional_access& e)
		{
			//P.S. fuck you standards commitee for taking your sweet time to add reflection, but especially fuck you MSVC for taking all this time to NOT EVEN finish c++23
			std::runtime_error("Failed to find file: " + static_cast<int>(file));
		}

		File.open(path_, std::ios::ate | std::ios::binary);
	   
		if (!File.is_open())
		{
			throw std::runtime_error("Failed to open file: " + path_.string());
		}

		size_t FileSize = static_cast<size_t>(File.tellg());

		std::vector<char> Buffer(FileSize);

		File.seekg(0);//put the reading pointer at 0 (start at the start)
		File.read(Buffer.data(), FileSize);

		File.close();

		return Buffer;
	}

	void Pipeline::CreateGraphicsPipeline()
	{
		auto VertShader = ReadFile(File::VERT_SHADER);
		auto FragShader = ReadFile(File::FRAG_SHADER);

		std::cout << "Vert Shader size: " << VertShader.size() << '\n';
		std::cout << "Frag Shader size: " << FragShader.size() << '\n';
	}

	Pipeline::Pipeline()
	{
		CreateGraphicsPipeline();
	}
}