#include "pch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "glm/ext/matrix_transform.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Letgen
{
	Renderer2D::SceneData* Renderer2D::s_SceneData = new SceneData;

	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> colorShader;
		Ref<Shader> textureShader;
	};

	static Renderer2DStorage* s_Data;
	
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage;
		auto& data = *s_Data;
		data.quadVertexArray = VertexArray::Create();

		float quadVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(quadVertices, sizeof quadVertices);

		vertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float2, "a_TexCoord" }});

		const Ref<IndexBuffer> indexBuffer(IndexBuffer::Create(quadIndices, sizeof quadIndices / sizeof(uint32_t)));

		data.quadVertexArray->AddVertexBuffer(vertexBuffer);
		data.quadVertexArray->SetIndexBuffer(indexBuffer);

		data.colorShader = Shader::Create("assets/shaders/Unlit_Color.shader");
		data.textureShader = Shader::Create("assets/shaders/Unlit_Texture.shader");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
		delete s_SceneData;
	}

	void Renderer2D::OnWindowResized(const uint32_t width, const uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		const auto projectionMatrix = camera.GetProjectionMatrix();
		const auto viewMatrix = camera.GetViewMatrix();

		std::dynamic_pointer_cast<OpenGLShader>(s_Data->colorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->colorShader)->SetUniformFloatMatrix4("u_Projection", projectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->colorShader)->SetUniformFloatMatrix4("u_View", viewMatrix);

		std::dynamic_pointer_cast<OpenGLShader>(s_Data->textureShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->textureShader)->SetUniformFloatMatrix4("u_Projection", projectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->textureShader)->SetUniformFloatMatrix4("u_View", viewMatrix);

		const float gray = 0.69f / 5;
		RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		RenderCommand::Clear();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		auto glShader = std::dynamic_pointer_cast<OpenGLShader>(s_Data->colorShader);
		glShader->Bind();
		glShader->SetUniformFloatVector4("u_Color", color);

		const auto model =
			translate(glm::mat4(1.0f), position) *
			scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		glShader->SetUniformFloatMatrix4("u_Model", model);
		
		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::DrawSprite(const Ref<Sprite>& sprite)
	{
		const auto model = sprite->GetTransform()->GetModel();

		auto glShader = std::dynamic_pointer_cast<OpenGLShader>(s_Data->textureShader);
		glShader->Bind();
		glShader->SetUniformFloatMatrix4("u_Model", model);
		glShader->SetUniformInt("u_Texture", 0);
		
		s_Data->quadVertexArray->Bind();
		sprite->GetTexture()->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::EndScene()
	{
		
	}
}
