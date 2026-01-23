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
			glm::vec3 position{};
			glm::vec3 color{};

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};

		struct Builder
		{
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indeces{};

		};

	private:
		Device& device;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;
		
		bool hasIndexBuffers = false;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;
		uint32_t indexCount;

		void CreateVertexBuffers(const std::vector<Vertex>& vertices);
		void CreateIndexBuffers(const std::vector<uint32_t>& indices);
	public:

		Model(Device& device, const Model::Builder& builder);
		~Model();
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		void inline Bind(VkCommandBuffer commandBuffer)
		{
			VkBuffer buffers[] = { vertexBuffer };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

			if (hasIndexBuffers)
			{
				vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
			}
		}
		void inline Draw(VkCommandBuffer commandBuffer) const
		{
			if (hasIndexBuffers)
				vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
			else
				vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
		}
	};
}