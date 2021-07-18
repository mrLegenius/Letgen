#include "pch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "Shader.h"
#include "RenderCommand.h"

namespace Letgen
{
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};
	
	struct Renderer2DData
	{
		const uint8_t verticesPerQuad = 4;
		const uint8_t indicesPerQuad = 6;
		
		const uint32_t maxQuads = 10'000;
		const uint32_t maxVertices = maxQuads * verticesPerQuad;
		const uint32_t maxIndices = maxQuads * indicesPerQuad;
		
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> ultimateShader;
		Ref<Texture2D> blankTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;
	};

	static Renderer2DData* s_Data;

	
	
	void Renderer2D::Init()
	{
		LE_PROFILE_FUNCTION();
		
		s_Data = new Renderer2DData;
		auto& data = *s_Data;
		data.quadVertexArray = VertexArray::Create();

		s_Data->quadVertexBuffer = VertexBuffer::Create(s_Data->maxVertices * sizeof QuadVertex);

		s_Data->quadVertexBufferBase = new QuadVertex[s_Data->maxVertices];
		
		s_Data->quadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color" },
			{ShaderDataType::Float2, "a_TexCoord" }});

		const auto quadIndices = new uint32_t[s_Data->maxIndices];

		uint32_t offset = 0;
		for(uint32_t i = 0; i < s_Data->maxIndices; i += s_Data->indicesPerQuad)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		
		const Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data->maxIndices);
		data.quadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		
		data.blankTexture = Texture2D::Create(1, 1);
		const uint32_t blankTextureData = 0xffffffff;
		data.blankTexture->SetData((void*)&blankTextureData, sizeof(uint32_t));

		data.quadVertexArray->AddVertexBuffer(s_Data->quadVertexBuffer);

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
		LE_PROFILE_FUNCTION();
		
		const auto projectionMatrix = camera.GetProjectionMatrix();
		const auto viewMatrix = camera.GetViewMatrix();

		s_Data->ultimateShader->Bind();
		s_Data->ultimateShader->SetMatrix4("u_Projection", projectionMatrix);
		s_Data->ultimateShader->SetMatrix4("u_View", viewMatrix);

		s_Data->quadVertexBufferPtr = s_Data->quadVertexBufferBase;
		s_Data->quadIndexCount = 0;
		
		const float gray = 0.69f / 5;
		RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		RenderCommand::Clear();
	}
	
	void Renderer2D::EndScene()
	{
		LE_PROFILE_FUNCTION();

		const uint32_t dataSize = reinterpret_cast<uint8_t*>(s_Data->quadVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data->quadVertexBufferBase);
		s_Data->quadVertexBuffer->SetData(s_Data->quadVertexBufferBase, dataSize);
		
		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_Data->quadVertexArray, s_Data->quadIndexCount);
	}

	void Renderer2D::DrawQuad(const Transform2D& transform, const glm::vec4& color)
	{
		Draw(
			transform,
			color,
			s_Data->blankTexture,
			1.0f);
	}

	void Renderer2D::DrawSprite(const Ref<Sprite>& sprite)
	{
		Draw(
			*sprite->GetTransform(), 
			glm::vec4(1.0f), 
			sprite->GetTexture(), 
			1.0f);
	}

	void Renderer2D::DrawSprite(const Transform2D& transform, const Ref<Texture2D>& texture)
	{
		Draw(transform, glm::vec4(1.0f), texture, 10.0f);
	}

	void Renderer2D::Draw(const Transform2D& transform, const glm::vec4& color, const Ref<Texture2D>& texture, const float tiling)
	{
		LE_PROFILE_FUNCTION();

		AddQuadToVertexBuffer(transform.position, transform.scale, color);

		const auto model = transform.angle < 0.000001f ? glm::mat4(1.0f) :
			rotate(glm::mat4(1.0f), transform.angle, glm::vec3(0.0f, 0.0f, 1.0f));
		
		const auto& shader = s_Data->ultimateShader;
		shader->SetMatrix4("u_Model", model);
		shader->SetFloat4("u_Color", color);
		shader->SetFloat("u_TexTiling", tiling);

		s_Data->quadVertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::AddQuadToVertexBuffer(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->quadVertexBufferPtr->position = { position.x, position.y, 0.0f };
		s_Data->quadVertexBufferPtr->color = color;
		s_Data->quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		s_Data->quadVertexBufferPtr++;

		s_Data->quadVertexBufferPtr->position = { position.x + size.x, position.y, 0.0f };
		s_Data->quadVertexBufferPtr->color = color;
		s_Data->quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		s_Data->quadVertexBufferPtr++;
		
		s_Data->quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Data->quadVertexBufferPtr->color = color;
		s_Data->quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		s_Data->quadVertexBufferPtr++;

		s_Data->quadVertexBufferPtr->position = { position.x, position.y + size.y, 0.0f };
		s_Data->quadVertexBufferPtr->color = color;
		s_Data->quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		s_Data->quadVertexBufferPtr++;

		s_Data->quadIndexCount += s_Data->indicesPerQuad;
	}
}
