#pragma once

namespace Letgen
{

	enum class FramebufferTextureFormat
	{
		None = 0,

		// -- Color -------------------

		RGBA8,
		RedInteger,

		// -- Depth/Stencil -----------

		Depth24Stencil8,

		//Defaults
		Depth = Depth24Stencil8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(const FramebufferTextureFormat format) : textureFormat(format) { }

		FramebufferTextureFormat textureFormat = FramebufferTextureFormat::None;
		//TODO: filtering/wrapping
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(const std::initializer_list<FramebufferTextureSpecification> attachments)
			: attachments(attachments) { }
		

		std::vector<FramebufferTextureSpecification> attachments;
	};
	
	struct FramebufferSpecification
	{
		uint32_t width = 0;
		uint32_t height = 0;
		
		FramebufferAttachmentSpecification attachmentSpecification;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};
	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		_NODISCARD virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		_NODISCARD virtual uint32_t GetColorAttachmentRendererID(const uint32_t index = 0) const = 0;
		
		_NODISCARD virtual const FramebufferSpecification& GetSpecification() const = 0;
		_NODISCARD virtual FramebufferSpecification& GetSpecification() = 0;

		_NODISCARD static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}