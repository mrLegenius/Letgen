#pragma once
#include "Core/Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Letgen
{
	class OpenGLShader : public Shader

	{
	public:
		explicit OpenGLShader(const std::string& filepath);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetUniformBool(const std::string& name, bool value);

		void SetUniformInt(const std::string& name, int value);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat2(const std::string& name, float v0, float v1);
		void SetUniformFloat3(const std::string& name, float v0, float v1, float v2);
		void SetUniformFloat4(const std::string& name, float v0, float v1, float v2, float v3);

		void SetUniformFloatVector2(const std::string& name, const glm::vec2& vector);
		void SetUniformFloatVector3(const std::string& name, const glm::vec3& vector);
		void SetUniformFloatVector4(const std::string& name, const glm::vec4& vector);

		void SetUniformFloatMatrix2(const std::string& name, const glm::mat2& matrix);
		void SetUniformFloatMatrix3(const std::string& name, const glm::mat3& matrix);
		void SetUniformFloatMatrix4(const std::string& name, const glm::mat4& matrix);
	private:
		[[nodiscard]] ShaderProgramSource ParseShader(const std::string& filePath) const;
		[[nodiscard]] uint32_t CompileShader(unsigned int type, const std::string& source) const;
		[[nodiscard]] uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

		[[nodiscard]] int GetUniformLocation(const std::string& name);

		std::string m_FilePath;
		uint32_t m_RendererID = 0;
		
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}
