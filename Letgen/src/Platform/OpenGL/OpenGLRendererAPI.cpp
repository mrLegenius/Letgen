#include "pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

void Letgen::OpenGLRendererAPI::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void Letgen::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Letgen::OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Letgen::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount)
{
	const uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void Letgen::OpenGLRendererAPI::SetViewport(const int x, const int y, const uint32_t width, const uint32_t height)
{
	glViewport(x, y, width, height);
}
