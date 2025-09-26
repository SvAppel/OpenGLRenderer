#include "Shader.h"

Shader::Shader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath)
	:m_VertexShaderFilePath(vertexShaderFilepath), m_FragmentShaderFilePath(fragmentShaderFilepath), m_RendererID(0)
{
	unsigned int shaderId = CreateShader(m_VertexShaderFilePath.c_str(), m_FragmentShaderFilePath.c_str());

	m_RendererID = shaderId;
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Checking
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader Compilation Error: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	//Read vertex and fragment shader files
	std::ifstream vertexShaderInput(vertexShaderFile, std::ifstream::in | std::ios::binary);
	std::noskipws(vertexShaderInput);
	if (!vertexShaderInput)
	{
		std::cout << "No such file: " << vertexShaderFile << std::endl;
		return 0;
	}

	std::string vertexShaderSource(std::istream_iterator<char>(vertexShaderInput), {});
	vertexShaderInput.close();


	std::ifstream fragmentShaderInput(fragmentShaderFile, std::ifstream::in | std::ios::binary);
	std::noskipws(fragmentShaderInput);
	if (!fragmentShaderInput)
	{
		std::cout << "No such file: " << fragmentShaderFile << std::endl;
		return 0;
	}

	std::string fragmentShaderSource(std::istream_iterator<char>(fragmentShaderInput), {});
	fragmentShaderInput.close();

	unsigned int program = glCreateProgram();
	unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);


	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return program;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());

	if (uniformLocation < 0)
		std::cout << "Warning: Uniform " << name << "does not exist" << std::endl;
	
	m_UniformLocationCache[name] = uniformLocation;

	return uniformLocation;
}
