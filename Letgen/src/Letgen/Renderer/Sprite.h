#pragma once
#include "Texture.h"
#include "Letgen/Components/Transform2D.h"

namespace Letgen
{
	class Sprite
	{
	public:
		explicit Sprite(const std::string& textureName);
		~Sprite() = default;

		[[nodiscard]] Ref<Transform2D> GetTransform() const { return m_Transform; }
		[[nodiscard]] Ref<Texture> GetTexture() const { return m_Texture; }
	private:
		Ref<Transform2D> m_Transform;
		Ref<Texture> m_Texture;
	};
}
