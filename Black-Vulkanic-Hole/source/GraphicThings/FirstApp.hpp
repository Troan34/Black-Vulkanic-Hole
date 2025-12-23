#pragma once

#include "window.hpp"
#include "pipeline.hpp"

namespace engine
{
	class FirstApp
	{
	private:
		Window window{ Height, Width, "Black Hole" };
		Pipeline pipeline{"GraphicThings/Shader/Shader.vert.spv", "GraphicThings/Shader/Shader.frag.spv"};

	public:
		static constexpr int Width = 800;
		static constexpr int Height = 600;

		void run();
	};
}