#include "renderer.hpp"


namespace engine
{
	Renderer::Renderer(Window& window_, Device& device_)
		:window{ window_ }, device{ device_ }
	{
		RecreateSwapChain();
		CreateCommandBuffers();
	}
	Renderer::~Renderer()
	{
		FreeCommandBuffers();
	}

	VkCommandBuffer Renderer::BeginFrame()
	{
		assert(!isFrameStarted and "Can't call BeginFrame() while frame is in progress");

		auto result = swapChain->acquireNextImage(&currentImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();
			return nullptr;
		}

		if (result != VK_SUCCESS and result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("Failed to acquire swap chain image, DrawFrame function");

		isFrameStarted = true;

		auto commandBuffer = GetCurrentCommandBuffer();


		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		VkCall(vkBeginCommandBuffer(commandBuffer, &beginInfo));

		return commandBuffer;
	}

	void Renderer::EndFrame()
	{
		assert(isFrameStarted and "Can't call EndFrame() if frame hasn't started");
		auto commandBuffer = GetCurrentCommandBuffer();

		VkCall(vkEndCommandBuffer(commandBuffer));

		auto result = swapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR or result == VK_SUBOPTIMAL_KHR or window.WasWindowResized())
		{
			window.ResetWindowResizedFlag();
			RecreateSwapChain();
		}
		else if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to present swap chain image, DrawFrame function");

		isFrameStarted = false;
		currentFrameIndex = (currentFrameIndex + 1) % SwapChain::MAX_FRAMES_IN_FLIGHT;
	}

	void Renderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer)
	{
		assert(isFrameStarted and "Can't call BeginSwapChainRenderPass() if frame is not in progress");
		assert(commandBuffer == GetCurrentCommandBuffer() and "Can't begin render pass on a command buffer from a different frame");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = swapChain->getRenderPass();
		renderPassInfo.framebuffer = swapChain->getFrameBuffer(currentImageIndex);

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChain->getSwapChainExtent();


		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);//this enum says that the commands do not contain other (secondary) command buffers

		VkViewport viewport{};
		//these configs manage how the objects are shown in the rendering
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		//for example these can squeeze the objects
		viewport.width = static_cast<float>(swapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(swapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{ {0, 0}, swapChain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	}

	void Renderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer)
	{
		assert(isFrameStarted and "Can't call EndSwapChainRenderPass() if frame is not in progress");
		assert(commandBuffer == GetCurrentCommandBuffer() and "Can't end render pass on a command buffer from a different frame");

		vkCmdEndRenderPass(commandBuffer);
	}

	
	void Renderer::CreateCommandBuffers()
	{
		commandBuffers.resize(SwapChain::MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;//when a command buffer is submitted to the queue, it has to be primary, secondary comm. buf. can only be called by primaries
		allocInfo.commandPool = device.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		VkCall(vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()));

	}

	void Renderer::FreeCommandBuffers()
	{
		vkFreeCommandBuffers(device.device(), device.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}


	void Renderer::RecreateSwapChain()
	{
		auto extent = window.GetExtent();

		while (extent.width == 0 or extent.height == 0)
		{
			extent = window.GetExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(device.device());

		if (swapChain == nullptr)
			swapChain = std::make_unique<SwapChain>(device, extent);
		else
		{
			std::shared_ptr<SwapChain> oldSwapChain = std::move(swapChain);
			swapChain = std::make_unique<SwapChain>(device, extent, oldSwapChain);

			if (!oldSwapChain->CompareSwapFormat(*swapChain.get()))
			{
				throw std::runtime_error("Swap chain image(or depth) format has changed!");
			}
		}

		//CreatePipeline();
	}

	
}