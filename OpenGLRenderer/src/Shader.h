#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class Shader 
{
private:
	std::string m_VertexShaderFilePath;
	std::string m_FragmentShaderFilePath;

	unsigned int m_RendererID;

	//Caching for Uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const char* vertexShaderFile, const char* fragmentShaderFile);

	//Set Shader uniforms from CPU side
	//needs to be used after binding a shader with glUseProgram
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);

private:
	int GetUniformLocation(const std::string& name);


};
