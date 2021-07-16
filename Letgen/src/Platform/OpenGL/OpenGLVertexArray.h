﻿#pragma once
#include "Core/Renderer/VertexArray.h"

namespace Letgen
{
	class OpenGLVertexArray final : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;
		
		void Bind() const override;
		void Unbind() const override;
		
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		[[nodiscard]] std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}
		[[nodiscard]] std::shared_ptr<IndexBuffer> GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}
	private:
		uint32_t m_RendererID = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}

