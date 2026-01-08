#include "FirstApp.hpp"

namespace engine
{
	FirstApp::FirstApp()
	{
		LoadGameObjects();
	}


	void FirstApp::LoadGameObjects()
	{
		std::vector<Model::Vertex> vertices
		{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		auto model = std::make_shared<Model>(device, vertices);

		auto triangle = GameObject::CreateGameObject();
		triangle.model = model;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2D.translation.x = .2f;
		triangle.transform2D.scale = { 2.f, .5f };
		triangle.transform2D.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}


	void FirstApp::run()
	{
		RenderSystem renderSystem{ device, renderer.GetSwapChainRenderPass() };
		while (!window.ShouldClose())
		{
			glfwPollEvents();
			
			if (auto commandBuffer = renderer.BeginFrame())
			{
				renderer.BeginSwapChainRenderPass(commandBuffer);
				renderSystem.RenderGameObjects(commandBuffer, gameObjects);
				renderer.EndSwapChainRenderPass(commandBuffer);
				renderer.EndFrame();
			}
		}

		vkDeviceWaitIdle(device.device());
	}
}