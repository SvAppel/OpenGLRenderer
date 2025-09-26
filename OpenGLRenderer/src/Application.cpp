#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TriangleRenderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //Use OpenGL core profile to avoid creation of default vertex array object
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    ////This would be the default mode and implicitly creates a default VAO
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Renderer", NULL, NULL);
    //window = glfwCreateWindow(1080, 1080, "Renderer", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // GLEW needs to be initialized after creating a valid OpenGL context
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error: GLEW initialization failed" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        //Vertex positions and Texture coordinates
        float positions[] =
        {
            -0.5f,  -0.5f, 0.0f, 0.0f,
            0.5f,   -0.5f, 1.0f, 0.0f,
            0.5f,   0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0,1,2,
            2,3,0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        //Create Vertex Array Object
        VertexArray vertexArrayObject;

        //Create and bind Vertex Buffer Object
        VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        vertexArrayObject.AddBuffer(vertexBuffer, layout);

        //Create and bind Index Buffer Object
        IndexBuffer indexBuffer(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        //Create and bind shader
        Shader shader("../OpenGLRenderer/src/Shaders/DefaultShader.vert", "../OpenGLRenderer/src/Shaders/DefaultShader.frag");
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", proj);

        //Create and bind texture
        Texture texture("../OpenGLRenderer/res/Textures/Sparx.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        //Unbind Shaders and Buffers
        vertexArrayObject.Unbind();
        vertexBuffer.Unbind();
        indexBuffer.Unbind();
        shader.Unbind();

        TriangleRenderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            //Set Shader uniforms from CPU side
            //needs to be used after binding a shader with glUseProgram
            shader.SetUniform4f("u_Color", 1.0f, 0.0f, 1.0f, 1.0f);

            renderer.Draw(vertexArrayObject, indexBuffer, shader);
            

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}