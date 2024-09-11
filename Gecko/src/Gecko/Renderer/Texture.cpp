#include "gkpch.h"
#include "Texture.h"

#include "Gecko/Platform/OpenGL/OpenGLTexture.h"

namespace Gecko {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		// TODO: Choose different API
		return std::make_shared<OpenGLTexture2D>(path);
		
		GK_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}