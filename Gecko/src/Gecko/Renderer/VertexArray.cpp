#include "gkpch.h"
#include "VertexArray.h"

#include "Gecko/Platform/OpenGL/OpenGLVertexArray.h"

namespace Gecko {

	Ref<VertexArray> VertexArray::Create()
	{
		// TODO: Choose different API
		return std::make_shared<OpenGLVertexArray>();

		GK_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}