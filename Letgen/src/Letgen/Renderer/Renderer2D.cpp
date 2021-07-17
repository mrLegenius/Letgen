#include "pch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "Shader.h"
#include "RenderCommand.h"

namespace Letgen
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> ultimateShader;
		Ref<Texture2D> blankTexture;
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

		data.blankTexture = Texture2D::Create(1, 1);
		const uint32_t blankTextureData = 0xffffffff;
		data.blankTexture->SetData((void*)&blankTextureData, sizeof(uint32_t));
		
		data.quadVertexArray->AddVertexBuffer(vertexBuffer);
		data.quadVertexArray->SetIndexBuffer(indexBuffer);

		data.ultimateShader = Shader::Create("assets/shaders/Ultimate2D.shader");
		data.ultimateShader->Bind();
		data.ultimateShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		const auto projectionMatrix = camera.GetProjectionMatrix();
		const auto viewMatrix = camera.GetViewMatrix();

		s_Data->ultimateShader->Bind();
		s_Data->ultimateShader->SetMatrix4("u_Projection", projectionMatrix);
		s_Data->ultimateShader->SetMatrix4("u_View", viewMatrix);

		const float gray = 0.69f / 5;
		RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		RenderCommand::Clear();
	}

	void Renderer2D::DrawQuad(const Transform2D& transform, const glm::vec4& color)
	{
		Draw(
			transform.GetModel(),
			color,
			s_Data->blankTexture,
			1.0f);
	}

	void Renderer2D::DrawSprite(const Ref<Sprite>& sprite)
	{
		Draw(
			sprite->GetTransform()->GetModel(), 
			glm::vec4(1.0f), 
			sprite->GetTexture(), 
			1.0f);
	}

	void Renderer2D::DrawSprite(const Transform2D& transform, const Ref<Texture2D>& texture)
	{
		Draw(transform.GetModel(), glm::vec4(1.0f), texture, 10.0f);
	}

	void Renderer2D::Draw(const glm::mat4& model, const glm::vec4& color, const Ref<Texture2D>& texture, const float tiling)
	{
		const auto& shader = s_Data->ultimateShader;
		shader->SetMatrix4("u_Model", model);
		shader->SetFloat4("u_Color", color);
		shader->SetFloat("u_TexTiling", tiling);

		s_Data->quadVertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::EndScene()
	{
		
	}
}
