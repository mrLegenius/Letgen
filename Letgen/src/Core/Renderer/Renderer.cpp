#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Letgen
{
	void Renderer::BeginScene()
	{
		
	}

	void Renderer::EndScene()
	{
		
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
