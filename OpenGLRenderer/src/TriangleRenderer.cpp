#include "TriangleRenderer.h"

#include <GLFW/glfw3.h>
#include <iostream>

//////////////////////////////////
//Start Error Checking definitions
void ClearGLErrors()
{
    while (glGetError() != GL_NO_ERROR);
}

bool CheckGLError(const char* function, const char* file, int line)
{
    //Error codes can be found in glew.h and are saved as hex codes
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}
//End Error Checking definitions
//////////////////////////////////

void TriangleRenderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void TriangleRenderer::Draw(const VertexArray& vertexArrayObject, const IndexBuffer& indexBuffer, const Shader& shader) const
{
    vertexArrayObject.Bind();
    indexBuffer.Bind();

    //Render triangle
    //OpenGl Error checking
    //This is just for practice. Ideally every OpenGL function call should be surrounded by the macro GLCall()
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
