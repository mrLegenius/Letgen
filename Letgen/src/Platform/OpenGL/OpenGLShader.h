#pragma once
#include "Letgen/Renderer/Shader.h"


#include <glm/glm.hpp>

//TODO: Remove!
typedef unsigned int GLenum;

namespace Letgen
{
	class OpenGLShader : public Shader

	{
	public:
		explicit OpenGLShader(const std::string& filepath);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		const std::string& GetName() const override { return m_Name; }
		
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
		[[nodiscard]] std::string ReadFile(const std::string& filepath) const;
		[[nodiscard]] std::unordered_map<GLenum, std::string> Preprocess(const std::string& source) const;

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		
		[[nodiscard]] int GetUniformLocation(const std::string& name);
	private:
		std::string m_FilePath;
		std::string m_Name;
		
		uint32_t m_RendererID = 0;
		
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}
