#pragma once
#include <glm/glm.hpp>

namespace Letgen
{
	class Transform2DComponent
	{
	public:
		glm::vec2 position;
		float angle;
		glm::vec2 scale;

		void SetPosition(const glm::vec2& value)
		{
			position = value;
			RecalculateModel();
		}
		_NODISCARD const glm::vec2& GetPosition() const { return position; }
		_NODISCARD glm::vec2& GetPosition() { return position; }

		void SetRotation(const float value)
		{
			angle = value;
			RecalculateModel();
		}
		_NODISCARD float GetRotation() const { return angle; }

		void SetScale(const glm::vec2& value)
		{
			scale = value;
			RecalculateModel();
		}
		_NODISCARD const glm::vec2& GetScale() const { return scale; }
		_NODISCARD glm::vec2& GetScale() { return scale; }

		Transform2DComponent(
			const glm::vec2& position = { 0.0f, 0.0f },
			float angle = 0.0f,
			const glm::vec2& scale = { 1.0f, 1.0f });

		_NODISCARD const glm::mat4& GetModel() const { return m_Model; }
	private:
		glm::mat4 m_Model { 1.0f };
		void RecalculateModel();
	};
}
