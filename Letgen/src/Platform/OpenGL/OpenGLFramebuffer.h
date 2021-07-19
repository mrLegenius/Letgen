#pragma once

#include "Letgen/Renderer/Framebuffer.h"

namespace Letgen
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer() override;

		void Invalidate();

		void Bind() override;
		void Unbind() override;

		uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }
		
		_NODISCARD const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		_NODISCARD FramebufferSpecification& GetSpecification() override { return m_Specification; }
		
	private:
		FramebufferSpecification m_Specification;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;

		uint32_t m_RendererID; 
	};
}