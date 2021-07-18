﻿#pragma once
#include <glad/glad.h>
#include "Letgen/Renderer/Texture.h"

namespace Letgen
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		explicit OpenGLTexture2D(const std::string& path);
		explicit OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D() override;

		[[nodiscard]] uint32_t GetWidth() const override { return m_Width; }
		[[nodiscard]] uint32_t GetHeight() const override { return m_Height; }

		void SetData(void* data, uint32_t size) override;
		
		void Bind(uint32_t slot = 0) const override;
		
		bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		};
	private:
		std::string m_Path;
		uint32_t m_RendererID;
		
		uint32_t m_Width;
		uint32_t m_Height;

		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}
