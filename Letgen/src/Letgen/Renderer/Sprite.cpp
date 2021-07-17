#include "pch.h"
#include "Sprite.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Letgen
{
	Sprite::Sprite(const std::string& textureName) : m_TextureName(textureName)
	{
		m_Shader = Shader::Create("assets/shaders/Unlit_Texture.shader");
		
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

		m_VertexArray = VertexArray::Create();
		Ref<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof vertices));

		vertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float2, "a_TexCoord" }
		});

		const Ref<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Texture = Texture2D::Create(textureName);
		m_Transform = std::make_shared<Transform>();

		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->SetUniformInt("u_Texture", 0);
	}
}
