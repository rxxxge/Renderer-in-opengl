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

}