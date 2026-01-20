#pragma once

#include <array>

#include "window.hpp"
#include "device.hpp"
#include "renderer.hpp"
#include "game_object.hpp"
#include "render_system.hpp"
#include "camera.hpp"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace engine
{


	class FirstApp
	{
	private:
		Window window{ height_m, width_m, "Black Hole" };
		Device device{ window };
		Renderer renderer{ window, device };
		std::vector<GameObject> gameObjects;
		
		void LoadGameObjects();
		
		
	public:
		static constexpr int width_m = 800;
		static constexpr int height_m = 600;
		
		FirstApp();
		~FirstApp() = default;
		FirstApp(const FirstApp&) = delete;
		FirstApp &operator=(const FirstApp&) = delete;

		void run();
	};
}