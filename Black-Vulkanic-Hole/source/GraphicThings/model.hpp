#pragma once

#include "device.hpp"

//pretty self explanatory
#define GLM_FORCE_RADIANS
//depth value will be (we clamped it) between 0 and 1
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace engine
{
	/// <summary>
	/// This class takes and prepares data (vertices) for the gpu
	/// </summary>
	class Model
	{
	public:
		struct Vertex
		{
			glm::vec2 position;
			glm::vec3 color;

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};

	private:
		Device& device;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;

		void CreateVertexBuffers(const std::vector<Vertex>& vertices);
	public:

		Model(Device& device, const std::vector<Vertex>& vertices);
		~Model();
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		void inline Bind(VkCommandBuffer commandBuffer)
		{
			VkBuffer buffers[] = { vertexBuffer };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
		}
		void inline Draw(VkCommandBuffer commandBuffer) const
		{
			vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
		}
	};
}