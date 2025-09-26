#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//////////////////////////////////
//Start Error Checking definitions
#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) ClearGLErrors();\
    x;\
    ASSERT(CheckGLError(#x, __FILE__, __LINE__))

void ClearGLErrors();

bool CheckGLError(const char* function, const char* file, int line);
//End Error Checking definitions
//////////////////////////////////


class TriangleRenderer
{
public:

    void Clear() const;
	void Draw(const VertexArray& vertexArrayObject, const IndexBuffer& indexBuffer, const Shader& shader) const;

};

