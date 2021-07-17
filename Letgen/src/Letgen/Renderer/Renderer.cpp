#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Letgen
{
	OrthographicCamera Renderer::s_Camera = {0.0f, 0.0f};
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResized(const uint32_t width, const uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	
	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		s_Camera = camera;
	}

	void Renderer::EndScene()
	{
		
	}

	void Renderer::Submit(const Ref<Sprite>& sprite)
	{
		const auto model = sprite->GetTransform()->GetModel();
		const auto view = s_Camera.GetViewMatrix();
		const auto projection = s_Camera.GetProjectionMatrix();

		auto glShader = std::dynamic_pointer_cast<OpenGLShader>(sprite->GetShader());
		glShader->Bind();
		glShader->SetUniformFloatMatrix4("u_Model", model);
		glShader->SetUniformFloatMatrix4("u_View", view);
		glShader->SetUniformFloatMatrix4("u_Projection", projection);
		
		sprite->GetVA()->Bind();
		sprite->GetTexture()->Bind();
		RenderCommand::DrawIndexed(sprite->GetVA());
	}
}
