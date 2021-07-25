#pragma once

namespace Letgen
{
	struct FramebufferSpecification
	{
		uint32_t width;
		uint32_t height;
		//FrameBufferFormat format = ;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};
	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		_NODISCARD virtual const FramebufferSpecification& GetSpecification() const = 0;
		_NODISCARD virtual FramebufferSpecification& GetSpecification() = 0;

		_NODISCARD static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}