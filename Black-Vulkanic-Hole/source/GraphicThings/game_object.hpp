#pragma once

#include "model.hpp"

namespace engine
{
	struct Transform2DComponent
	{
		glm::vec2 translation{};
		glm::vec2 scale{ 1.f, 1.f };
		float rotation;

		glm::mat2 mat2() 
		{ 
			const float s = glm::sin(rotation);
			const float c = glm::cos(rotation);
			glm::mat2 rotMatrix{ {c, s}, {-s, c} };

			glm::mat2 scaleMat{ {scale.x, .0f},
							   {.0f, scale.y} };//COLUMNS order
			return rotMatrix * scaleMat; 
		}
	};


	class GameObject
	{
	private:
		using id_t = unsigned int;

		id_t id;


		GameObject(id_t objId) :id{ objId } {}
	public:
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) = default;
		GameObject& operator=(GameObject&&) = default;


		[[nodiscard]] static auto CreateGameObject()
		{
			static id_t currentId = 0;
			return GameObject{currentId++};
	    }

		[[nodiscard]] auto GetId() const { return id; }

		std::shared_ptr<Model> model{};
		glm::vec3 color;
		Transform2DComponent transform2D{};


	};
}