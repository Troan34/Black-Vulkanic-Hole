#pragma once

#include <array>

#include "pipeline.hpp"
#include "device.hpp"
#include "game_object.hpp"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace engine
{
	struct SimplePushConstantData
	{
		glm::mat4 transform{ 1.f };
		alignas(16) glm::vec3 color;
	};

	class RenderSystem
	{
	private:
		Device &device;
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;

		void CreatePipelineLayout();
		void CreatePipeline(VkRenderPass renderPass);



	public:
		RenderSystem(Device& device, VkRenderPass renderPass);
		~RenderSystem();
		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;

		void RenderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects);
	};
}