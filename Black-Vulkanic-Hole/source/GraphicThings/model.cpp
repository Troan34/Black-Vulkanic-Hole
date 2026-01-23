#include "model.hpp"

namespace engine
{
	
	Model::Model(Device& device, const Model::Builder& builder)
		:device{device}
	{
		CreateVertexBuffers(builder.vertices);
		CreateIndexBuffers(builder.indeces);
	}
	Model::~Model()
	{
		vkDestroyBuffer(device.device(), vertexBuffer, nullptr);
		vkFreeMemory(device.device(), vertexBufferMemory, nullptr);

		if (hasIndexBuffers)
		{
			vkDestroyBuffer(device.device(), indexBuffer, nullptr);
			vkFreeMemory(device.device(), indexBufferMemory, nullptr);
		}
	}
	void Model::CreateVertexBuffers(const std::vector<Vertex>& vertices)
	{
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 and "Vertex count must be atleast 3");

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		device.createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
							VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,//we can access device memory from host | when we change memory, the device memory is automatically flushed
							stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(device.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(device.device(), stagingBufferMemory);


		device.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
							VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,//the memory is on the device 
							vertexBuffer, vertexBufferMemory);

		device.copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		vkDestroyBuffer(device.device(), stagingBuffer, nullptr);
		vkFreeMemory(device.device(), stagingBufferMemory, nullptr);

	}

	void Model::CreateIndexBuffers(const std::vector<uint32_t>& indeces)
	{
		indexCount = static_cast<uint32_t>(indeces.size());
		
		hasIndexBuffers = indexCount > 0;

		if (!hasIndexBuffers)
			return;

		assert(indexCount >= 3 and "Index count must be atleast 3");

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VkDeviceSize bufferSize = sizeof(indeces[0]) * indexCount;
		device.createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
							VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,//we can access device memory from host | when we change memory, the device memory is automatically flushed
							stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(device.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indeces.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(device.device(), stagingBufferMemory);


		device.createBuffer(bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
							VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,//the memory is on the device 
							indexBuffer, indexBufferMemory);

		device.copyBuffer(stagingBuffer, indexBuffer, bufferSize);

		vkDestroyBuffer(device.device(), stagingBuffer, nullptr);
		vkFreeMemory(device.device(), stagingBufferMemory, nullptr);

	}

	std::vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions()
	{
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		bindingDescriptions[0].stride = sizeof(Vertex);
		return bindingDescriptions;
	}
	std::vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions()
	{
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
}
