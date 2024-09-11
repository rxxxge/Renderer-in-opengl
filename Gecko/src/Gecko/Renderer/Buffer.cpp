#include "gkpch.h"
#include "Buffer.h"

#include "Gecko/Log.h"

#include "Gecko/Platform/OpenGL/OpenGLBuffer.h"

namespace Gecko {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		// TODO: Choose different API
		return new OpenGLVertexBuffer(vertices, size);

		GK_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		// TODO: Choose different API
		return new OpenGLIndexBuffer(indices, count);

		GK_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

}