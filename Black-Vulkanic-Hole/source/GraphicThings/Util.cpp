#include "Util.hpp"


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
