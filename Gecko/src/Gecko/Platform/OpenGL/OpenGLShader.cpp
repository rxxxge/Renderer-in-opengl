#include "gkpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Gecko {

	namespace Utils {

		enum CompileType
		{
			VERTEX, FRAGMENT, PROGRAM
		};
		
		bool CheckCompileErrors(GLuint glObject, CompileType type)
		{
			GLint isCompiled = 0;
			switch (type)
			{
				case Utils::VERTEX:
				case Utils::FRAGMENT:
					glGetShaderiv(glObject, GL_COMPILE_STATUS, &isCompiled);
					if (isCompiled == GL_FALSE)
					{
						GLint maxLength = 0;
						glGetShaderiv(glObject, GL_INFO_LOG_LENGTH, &maxLength);

						std::vector<GLchar> infoLog(maxLength);

						glGetShaderInfoLog(glObject, maxLength, &maxLength, &infoLog[0]);

						GK_CORE_ERROR("{0}", infoLog.data());
						if (type == FRAGMENT)
							GK_CORE_ASSERT(false, "Fragment shader compilation failed!");
						if (type == VERTEX)
							GK_CORE_ASSERT(false, "Vertex shader compilation failed!");
						return false;
					}
					break;
				case Utils::PROGRAM:
					glGetProgramiv(glObject, GL_LINK_STATUS, &isCompiled);
					if (isCompiled == GL_FALSE)
					{
						GLint maxLength = 0;
						glGetProgramiv(glObject, GL_INFO_LOG_LENGTH, &maxLength);

						std::vector<GLchar> infoLog(maxLength);
						glGetProgramInfoLog(glObject, maxLength, &maxLength, &infoLog[0]);

						GK_CORE_ERROR("{0}", infoLog.data());
						GK_CORE_ASSERT(false, "Shader linkage error!");
						return false;
					}
					break;
			}

			return true;
		}

	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexSrc);
			fShaderFile.open(fragmentSrc);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			GK_CORE_ERROR(e.what());
		}

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		GLuint vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		if (!Utils::CheckCompileErrors(vertexShader, Utils::VERTEX))
		{
			glDeleteShader(vertexShader);
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		if (!Utils::CheckCompileErrors(fragmentShader, Utils::FRAGMENT))
		{
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
		}

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		if (!Utils::CheckCompileErrors(program, Utils::PROGRAM))
		{
			glDeleteProgram(program);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

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

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				GK_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			GK_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

}