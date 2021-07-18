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
		float texIndex;
	};
	
	struct Renderer2DData
	{
		const uint32_t verticesPerQuad = 4;
		const uint32_t indicesPerQuad = 6;
		static const uint32_t maxTextureSlots = 32; //TODO: Render Capabilities;
		
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

		std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1; // slot 0 - blank texture
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
			{ShaderDataType::Float2, "a_TexCoord" },
			{ShaderDataType::Float, "a_TexIndex" },
		});

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

			offset += s_Data->verticesPerQuad;
		}
		
		const Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data->maxIndices);
		data.quadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		
		data.blankTexture = Texture2D::Create(1, 1);
		uint32_t blankTextureData = 0xffffffff;
		data.blankTexture->SetData(&blankTextureData, sizeof(uint32_t));
		s_Data->textureSlots[0] = s_Data->blankTexture;

		int32_t samplers[Renderer2DData::maxTextureSlots];
		for(int32_t i = 0; i < Renderer2DData::maxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		
		data.quadVertexArray->AddVertexBuffer(s_Data->quadVertexBuffer);

		data.ultimateShader = Shader::Create("assets/shaders/Ultimate2D.shader");
		data.ultimateShader->Bind();
		data.ultimateShader->SetIntArray("u_Textures", samplers, Renderer2DData::maxTextureSlots);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data->quadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		LE_PROFILE_FUNCTION();

		s_Data->ultimateShader->Bind();
		s_Data->ultimateShader->SetMatrix4("u_Projection", camera.GetProjectionMatrix());
		s_Data->ultimateShader->SetMatrix4("u_View", camera.GetViewMatrix());

		s_Data->quadVertexBufferPtr = s_Data->quadVertexBufferBase;
		s_Data->quadIndexCount = 0;
		s_Data->textureSlotIndex = 1;
		
		const float gray = 0.69f / 5;
		RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		RenderCommand::Clear();
	}
	
	void Renderer2D::EndScene()
	{
		LE_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer2D::Flush()
	{
		if(s_Data->quadIndexCount == 0)
			return;

		const uint32_t dataSize = (uint32_t)((uint8_t*)s_Data->quadVertexBufferPtr - (uint8_t*)s_Data->quadVertexBufferBase);
		s_Data->quadVertexBuffer->SetData(s_Data->quadVertexBufferBase, dataSize);

		for(uint32_t i = 0; i < s_Data->textureSlotIndex; i++)
		{
			s_Data->textureSlots[i]->Bind(i);
		}

		s_Data->ultimateShader->Bind();
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

		AddQuadToVertexBuffer(transform.GetModel(), color, texture);

		const auto& shader = s_Data->ultimateShader;
		shader->SetFloat("u_TexTiling", tiling);

		s_Data->quadVertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::AddQuadToVertexBuffer(const glm::mat4& model, const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		float textureIndex = -1.0f;

		for(uint32_t i = 0; i < s_Data->textureSlotIndex; i++)
		{
			if(*s_Data->textureSlots[i] == *texture)
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}
		
		if(textureIndex == -1.0f)
		{
			textureIndex = static_cast<float>(s_Data->textureSlotIndex);
			s_Data->textureSlots[s_Data->textureSlotIndex] = texture;
			s_Data->textureSlotIndex++;
		}
		
		constexpr glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f } };
		
		constexpr glm::vec4 quadVertexPositions[] {
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f,  0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f },
		};
		
		for (uint32_t i = 0; i < s_Data->verticesPerQuad; i++)
		{
			s_Data->quadVertexBufferPtr->position = model * quadVertexPositions[i];
			s_Data->quadVertexBufferPtr->color = color;
			s_Data->quadVertexBufferPtr->texCoord = textureCoords[i];
			s_Data->quadVertexBufferPtr->texIndex = textureIndex;
			s_Data->quadVertexBufferPtr++;
		}

		s_Data->quadIndexCount += s_Data->indicesPerQuad;
	}
}
