#include "Shader.h"
#include <fstream>
#include <iostream>
#include "Math/Matrix4D.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// Ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		std::cout << "VERTEX PATH: " << vertexPath << std::endl;
		std::cout << "FRAGMENT PATH: " << fragmentPath << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	if (!CheckCompilationStatus(vertex) || !CheckCompilationStatus(fragment))
	{
		std::cout << "FAILED TO COMPILE SHADERS" << std::endl;
		return;
	}

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	if (!CheckLinkingStatus())
	{
		std::cout << "FAILED TO LINK PROGRAM" << std::endl;
		return;
	}
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Use() const
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Error: uniform location not found: "<< name << std::endl;
		return;
	}
	glUniform1i(location, (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Error: uniform location not found: " << name << std::endl;
		return;
	}
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Error: uniform location not found: " << name << std::endl;
		return;
	}
	glUniform1f(location, value);
}

void Shader::SetVec3(const std::string& name, float r, float g, float b) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Error: uniform location not found: " << name << std::endl;
		return;
	}
	glUniform3f(location, r, g, b);
}

void Shader::SetVec3(const std::string& name, const Math::Vector3D& vec3) const
{
	SetVec3(name, vec3.x, vec3.y, vec3.z);
}

void Shader::SetVec4(const std::string& name, float r, float g, float b, float a) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Error: uniform location not found: " << name << std::endl;
		return;
	}
	glUniform4f(location, r, g, b, a);
}

void Shader::SetVec4(const std::string& name, const Math::Vector4D& vec4) const
{
	SetVec4(name, vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::SetMat4(const std::string& name, const Math::Matrix4D& mat) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Error: uniform location not found: " << name << std::endl;
		return;
	}
	// GL_TRUE since my matrix4D is row-major
	glUniformMatrix4fv(location, 1, GL_TRUE, &mat.r0c0);
}

bool Shader::CheckStatus(uint program, PFNGLGETSHADERIVPROC getProgramivFunc, uint statusToCheck, PFNGLGETPROGRAMINFOLOGPROC infoLogGetterFunc) const
{
	int status;
	getProgramivFunc(program, statusToCheck, &status);
	if (status != GL_TRUE)
	{
		int infoLength;
		getProgramivFunc(program, GL_INFO_LOG_LENGTH, &infoLength);
		char* buffer = new char[infoLength];
		int bufferSize;

		infoLogGetterFunc(program, infoLength, &bufferSize, buffer);

		// Log error
		std::cout << " ERROR ON COMPILATION: " << buffer << std::endl;

		delete[] buffer;
		return false; // Failure
	}
	return true; // Success
}

bool Shader::CheckCompilationStatus(const uint& shaderProgram) const
{
	return CheckStatus(shaderProgram, glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog);
}

bool Shader::CheckLinkingStatus() const
{
	return CheckStatus(ID, glGetProgramiv, GL_LINK_STATUS, glGetProgramInfoLog);
}
