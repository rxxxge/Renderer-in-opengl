#include "gkpch.h"
#include "Shader.h"

#include "Gecko/Platform/OpenGL/OpenGLShader.h"

namespace Gecko {

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// TODO: Switch different API's
		return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);

		GK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	//Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	//{
	//	// Print some info
	//	GLint attributesNum;
	//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributesNum);
	//	GK_CORE_INFO("Maximum number of vertex attributes supported: {0}", attributesNum);

	//	// Empty vertex shader handle
	//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//	// Send vertex shader source to GL
	//	const GLchar* source = vertexSrc.c_str();
	//	glShaderSource(vertexShader, 1, &source, 0);

	//	// Compile vertex shader
	//	glCompileShader(vertexShader);

	//	GLint isCompiled = 0;
	//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	//	if (isCompiled == GL_FALSE)
	//	{
	//		GLint maxLength = 0;
	//		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

	//		std::vector<GLchar> infoLog(maxLength);

	//		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

	//		glDeleteShader(vertexShader);

	//		GK_CORE_ERROR("{0}", infoLog.data());
	//		GK_CORE_ASSERT(false, "Vertex shader compilation failed!");
	//		return;
	//	}

	//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//	source = fragmentSrc.c_str();
	//	glShaderSource(fragmentShader, 1, &source, 0);

	//	glCompileShader(fragmentShader);

	//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	//	if (isCompiled == GL_FALSE)
	//	{
	//		GLint maxLength = 0;
	//		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

	//		std::vector<GLchar> infoLog(maxLength);

	//		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

	//		glDeleteShader(fragmentShader);
	//		glDeleteShader(vertexShader);

	//		GK_CORE_ERROR("{0}", infoLog.data());
	//		GK_CORE_ASSERT(false, "Fragment shader compilation failed!");
	//		return;
	//	}

	//	// After compiling, link vertex and fragment shader into one program
	//	m_RendererID = glCreateProgram();
	//	GLuint program = m_RendererID;

	//	// Attach shaders to program
	//	glAttachShader(program, vertexShader);
	//	glAttachShader(program, fragmentShader);

	//	// Link program
	//	glLinkProgram(program);

	//	GLint isLinked = 0;
	//	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	//	if (isLinked == GL_FALSE)
	//	{
	//		GLint maxLength = 0;
	//		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

	//		std::vector<GLchar> infoLog(maxLength);
	//		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

	//		glDeleteProgram(program);
	//		glDeleteShader(fragmentShader);
	//		glDeleteShader(vertexShader);

	//		GK_CORE_ERROR("{0}", infoLog.data());
	//		GK_CORE_ASSERT(false, "Shader linkage failed!");
	//		return;
	//	}

	//	glDetachShader(program, vertexShader);
	//	glDetachShader(program, fragmentShader);
	//}

	//Shader::~Shader()
	//{
	//	glDeleteProgram(m_RendererID);
	//}

	//void Shader::Bind() const
	//{
	//	glUseProgram(m_RendererID);
	//}

	//void Shader::Unbind() const
	//{
	//	glUseProgram(0);
	//}

	/*void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		GK_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}*/

	//Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	//{
	//	auto shader = Shader::Create(filepath);
	//	Add(shader);
	//	return shader;
	//}

	//Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	//{
	//	auto shader = Shader::Create(filepath);
	//	Add(name, shader);
	//	return shader;
	//}

	/*Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		GK_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}*/

}