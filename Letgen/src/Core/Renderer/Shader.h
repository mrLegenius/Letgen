#pragma once
#include "glm/fwd.hpp"

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
		explicit Shader(const std::string& filepath, int pointLightsCount = 1, int spotLightsCount = 2);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1b(const std::string& name, bool value);
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformVec2f(const std::string& name, const glm::vec2& vector);
		void SetUniformVec3f(const std::string& name, const glm::vec3& vector);
		void SetUniformVec4f(const std::string& name, const glm::vec4& vector);
		void SetUniformMat2f(const std::string& name, const glm::mat2& matrix);
		void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
		void SetUniformMat4fv(const std::string& name, const glm::f32* value);
	
	private:
		ShaderProgramSource ParseShader(const std::string& filePath, int pointLightsCount, int spotLightsCount) const;
		unsigned int CompileShader(unsigned int type, const std::string& source) const;
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

		int GetUniformLocation(const std::string& name);
		
		std::string m_FilePath;
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}
