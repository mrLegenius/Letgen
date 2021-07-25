#pragma once
#include "Texture.h"
#include "Letgen/Scene/Components/Transform2DComponent.h"

namespace Letgen
{
	class Sprite
	{
	public:
		explicit Sprite(const std::string& textureName);
		~Sprite() = default;

		[[nodiscard]] Ref<Transform2DComponent> GetTransform() const { return m_Transform; }
		[[nodiscard]] const Ref<Texture2D>& GetTexture() const { return m_Texture; }
	private:
		Ref<Transform2DComponent> m_Transform;
		Ref<Texture2D> m_Texture;
	};
}
