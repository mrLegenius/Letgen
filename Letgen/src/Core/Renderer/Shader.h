#pragma once

namespace Letgen
{
	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};
	
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& filepath);
	};
}
