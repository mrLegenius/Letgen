#include "pch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "Shader.h"
#include "RenderCommand.h"

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

		s_Data->colorShader->Bind();
		s_Data->colorShader->SetMatrix4("u_Projection", projectionMatrix);
		s_Data->colorShader->SetMatrix4("u_View", viewMatrix);

		s_Data->textureShader->Bind();
		s_Data->textureShader->SetMatrix4("u_Projection", projectionMatrix);
		s_Data->textureShader->SetMatrix4("u_View", viewMatrix);

		const float gray = 0.69f / 5;
		RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		RenderCommand::Clear();
	}

	void Renderer2D::DrawQuad(const Transform2D& transform, const glm::vec4& color)
	{
		const auto& shader = s_Data->colorShader;
		shader->Bind();
		shader->SetFloat4("u_Color", color);
		shader->SetMatrix4("u_Model", transform.GetModel());

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::DrawSprite(const Ref<Sprite>& sprite)
	{
		const auto model = sprite->GetTransform()->GetModel();

		const auto& shader = s_Data->textureShader;
		shader->Bind();
		shader->SetMatrix4("u_Model", model);
		shader->SetInt("u_Texture", 0);
		
		s_Data->quadVertexArray->Bind();
		sprite->GetTexture()->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::EndScene()
	{
		
	}
}
