#include "FirstApp.hpp"

namespace engine
{
	FirstApp::FirstApp()
	{
		LoadGameObjects();
	}


	void FirstApp::LoadGameObjects()
	{
        std::shared_ptr<Model> model = Model::CreateModelFromFile(device, "resources/models/smooth_vase.obj");

        auto cube = GameObject::CreateGameObject();
        cube.model = model;
        cube.transform.translation = { .0f, .0f, 2.f };
        cube.transform.scale = { .5f, .5f, .5f };
        gameObjects.push_back(std::move(cube));

	}


	void FirstApp::run()
	{
		RenderSystem renderSystem{ device, renderer.GetSwapChainRenderPass() };
        Camera camera{};
        //camera.SetViewDirection(glm::vec3(0.f), glm::vec3(.5f, 0.f, 1.f));
        camera.SetViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.f));

        auto viewerObject = GameObject::CreateGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();
        
		while (!window.ShouldClose())
		{
			glfwPollEvents();
            
            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            frameTime = min(frameTime, MAX_FRAME_TIME);

            cameraController.moveInPlaneXZ(window.GetGLFWWindow(), frameTime, viewerObject);
            camera.SetViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = renderer.GetAspectRatio();
            //camera.SetOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);
            camera.SetPerspectiveProjection(glm::radians(60.f), aspect, 0.1f, 10.f);

			if (auto commandBuffer = renderer.BeginFrame())
			{
				renderer.BeginSwapChainRenderPass(commandBuffer);
				renderSystem.RenderGameObjects(commandBuffer, gameObjects, camera);
				renderer.EndSwapChainRenderPass(commandBuffer);
				renderer.EndFrame();
			}
		}

		vkDeviceWaitIdle(device.device());
	}
}