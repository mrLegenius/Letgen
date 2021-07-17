#pragma once
#include "Buffer.h"

namespace Letgen
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}
