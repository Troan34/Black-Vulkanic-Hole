#pragma once

#include <array>

#include "window.hpp"
#include "device.hpp"
#include "swap_chain.hpp"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace engine
{

	class Renderer
	{
	private:
		Window& window;
		Device& device;
		std::unique_ptr<SwapChain> swapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex = 0;
		int currentFrameIndex;
		bool isFrameStarted = false;

		void CreateCommandBuffers();
		void FreeCommandBuffers();
		void RecreateSwapChain();


	public:

		Renderer(Window& window_, Device& device_);
		~Renderer();
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		VkCommandBuffer BeginFrame();
		void EndFrame();

		void BeginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void EndSwapChainRenderPass(VkCommandBuffer commandBuffer);


		NO_DIS inline bool IsFrameInProgress() const { return isFrameStarted; }

		NO_DIS inline VkCommandBuffer GetCurrentCommandBuffer() const
		{
			assert(isFrameStarted and "Cannot get command buffer when frame is not in progress");
			return commandBuffers[currentFrameIndex];
		}

		NO_DIS inline VkRenderPass GetSwapChainRenderPass() const { return swapChain->getRenderPass(); }

		NO_DIS inline int GetFrameIndex() const
		{
			assert(isFrameStarted and "Cannot get frame index when frame is not in progress");
			return currentFrameIndex;
		}

		float inline GetAspectRatio() const { return swapChain->extentAspectRatio(); }
	};
}