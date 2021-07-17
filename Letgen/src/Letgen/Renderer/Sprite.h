#pragma once
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Letgen/Components/Transform.h"

namespace Letgen
{
	class Sprite
	{
	public:
		explicit Sprite(const std::string& textureName);
		~Sprite() = default;

		[[nodiscard]] Ref<Transform> GetTransform() const { return m_Transform; }
		[[nodiscard]] Ref<Shader> GetShader() const { return m_Shader; }
		[[nodiscard]] Ref<VertexArray> GetVA() const { return m_VertexArray; }
		[[nodiscard]] Ref<Texture> GetTexture() const { return m_Texture; }
	private:
		std::string m_TextureName;
		Ref<Transform> m_Transform;

		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		Ref<Texture> m_Texture;
	};
}
