#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>

#include "glm/glm.hpp"

namespace Letgen
{
	Shader::Shader(const std::string& filepath, const int pointLightsCount, const int spotLightsCount) : m_FilePath(filepath)
	{
		const auto [vertexShader, fragmentShader] = ParseShader(filepath, pointLightsCount, spotLightsCount);
		m_RendererID = CreateShader(vertexShader, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filePath, const int pointLightsCount, const int spotLightsCount) const
	{
		std::ifstream stream(filePath);
		const bool isOpened = stream.is_open();
		LE_CORE_ASSERT(isOpened, "Can't open " + filePath + " shader file!");
		
		enum class ShaderType
		{
			None = -1, Vertex = 0, Fragment = 1
		};
		
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::None;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::Vertex;
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::Fragment;
				}
			}
			else
			{
				ss[static_cast<int>(type)] << line.c_str() << "\n";
				if (line.find("#version") != std::string::npos)
				{
					ss[static_cast<int>(type)] << "#define POINT_LIGHTS_NUM " << std::to_string(pointLightsCount) << "\n";
					ss[static_cast<int>(type)] << "#define SPOT_LIGHTS_NUM " << std::to_string(spotLightsCount) << "\n";
				}
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CompileShader(const unsigned int type, const std::string& source) const
	{
		const unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			const auto message = static_cast<char*>(nullptr);
			glGetShaderInfoLog(id, length, &length, message);
			Log::CoreError("Failed to compile {0}", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			Log::CoreError(message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}
	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const
	{
		const unsigned int program = glCreateProgram();
		const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1b(const std::string& name, const bool value)
	{
		glUniform1i(GetUniformLocation(name), static_cast<int>(value));
	}

	void Shader::SetUniform1i(const std::string& name, const int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1f(const std::string& name, const float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform2f(const std::string& name, const float v0, const float v1)
	{
		glUniform2f(GetUniformLocation(name), v0, v1);
	}
	void Shader::SetUniform3f(const std::string& name, const float v0, const float v1, const float v2)
	{
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}
	void Shader::SetUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}
	void Shader::SetUniformVec2f(const std::string& name, const glm::vec2& vector)
	{
		glUniform2fv(GetUniformLocation(name), 1, &vector[0]);
	}
	void Shader::SetUniformVec3f(const std::string& name, const glm::vec3& vector)
	{
		glUniform3fv(GetUniformLocation(name), 1, &vector[0]);
	}
	void Shader::SetUniformVec4f(const std::string& name, const glm::vec4& vector)
	{
		glUniform4fv(GetUniformLocation(name), 1, &vector[0]);
	}
	void Shader::SetUniformMat2f(const std::string& name, const glm::mat2& matrix)
	{
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}
	void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}
	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}
	void Shader::SetUniformMat4fv(const std::string& name, const glm::f32* value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1)
			Log::CoreWarning("In Shader({0}) uniform {1} doesn't exist!", m_RendererID, name);

		m_UniformLocationCache[name] = location;
		return location;
	}
}
