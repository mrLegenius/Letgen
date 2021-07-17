#include "pch.h"
#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "Core/Asserts.h"

namespace Letgen
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;

		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		LE_CORE_ASSERT(false, "Unknown shader type '{1}'", type)
		return 0;
	}
	
	OpenGLShader::OpenGLShader(const std::string& filepath) : m_FilePath(filepath)
	{
		const std::string source = ReadFile(filepath);
		const auto shaderSources = Preprocess(source);
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	} 

	void OpenGLShader::SetUniformBool(const std::string& name, const bool value)
	{
		glUniform1i(GetUniformLocation(name), static_cast<int>(value));
	}

	void OpenGLShader::SetUniformInt(const std::string& name, const int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformFloat(const std::string& name, const float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}
	void OpenGLShader::SetUniformFloat2(const std::string& name, const float v0, const float v1)
	{
		glUniform2f(GetUniformLocation(name), v0, v1);
	}
	void OpenGLShader::SetUniformFloat3(const std::string& name, const float v0, const float v1, const float v2)
	{
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}
	void OpenGLShader::SetUniformFloat4(const std::string& name, const float v0, const float v1, const float v2, const float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniformFloatVector2(const std::string& name, const glm::vec2& vector)
	{
		glUniform2fv(GetUniformLocation(name), 1, &vector[0]);
	}
	void OpenGLShader::SetUniformFloatVector3(const std::string& name, const glm::vec3& vector)
	{
		glUniform3fv(GetUniformLocation(name), 1, &vector[0]);
	}
	void OpenGLShader::SetUniformFloatVector4(const std::string& name, const glm::vec4& vector)
	{
		glUniform4fv(GetUniformLocation(name), 1, &vector[0]);
	}
	
	void OpenGLShader::SetUniformFloatMatrix2(const std::string& name, const glm::mat2& matrix)
	{
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::SetUniformFloatMatrix3(const std::string& name, const glm::mat3& matrix)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(matrix));
	}
	void OpenGLShader::SetUniformFloatMatrix4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) const
	{
		std::string result;
		std::ifstream in(filepath, std::ios::binary);
		if(in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			Log::CoreError("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source) const
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const auto typeToken = "#shader";
		const size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while(pos != std::string::npos)
		{
			const size_t eol = source.find_first_of("\r\n", pos);
			LE_CORE_ASSERT(eol != std::string::npos, "Syntax error")
			const size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			LE_CORE_ASSERT(ShaderTypeFromString(type), "Unkown shader type!")
			
			const size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
					pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		const auto program = glCreateProgram();
		std::vector<GLuint> glShaderIDs(shaderSources.size());
		
		for (auto& [type, source] : shaderSources)
		{
			const GLuint shader = glCreateShader(type);
			const char* src = source.c_str();
			
			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);

			GLint success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				
				const auto message = static_cast<char*>(nullptr);
				glGetShaderInfoLog(shader, length, &length, message);
				
				Log::CoreError("Failed to compile {0}", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
				Log::CoreError(message);
				LE_CORE_ASSERT(false)
				
				glDeleteShader(shader);
				return;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}
		
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

		if(isLinked == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			const auto message = static_cast<char*>(nullptr);
			glGetProgramInfoLog(program, length, &length, message);

			for (auto shader : glShaderIDs)
			{
				glDeleteShader(shader);
			}
			
			Log::CoreError(message);
			LE_CORE_ASSERT(false, "Shader link failure!")
			
			return;
		}
		
		glValidateProgram(program);
		for (auto shader : glShaderIDs)
		{
			glDeleteShader(shader);
		}

		m_RendererID = program;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
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