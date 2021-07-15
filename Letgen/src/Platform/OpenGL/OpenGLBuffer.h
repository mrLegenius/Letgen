#pragma once
#include "Core/Renderer/Buffer.h"

namespace Letgen
{
	class OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
	
	private:
		uint32_t m_RendererID = 0;
	};

	class OpenGLIndexBuffer final : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }
	
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;
	};
}
