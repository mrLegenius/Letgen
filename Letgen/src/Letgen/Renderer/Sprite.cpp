#include "pch.h"
#include "Sprite.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Letgen
{
	Sprite::Sprite(const std::string& textureName)
	{
		m_Texture = Texture2D::Create(textureName);
		m_Transform = std::make_shared<Transform>();
	}
}
