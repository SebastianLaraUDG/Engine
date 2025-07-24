#pragma once
#include <Misc/Typedefs.h>
#include <Middleware/GLEW/include/GL/glew.h>
#include <sstream>


namespace Math
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix4D;
}


class Shader
{
public:
	// The program ID
	uint ID;

	// Constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	// Use/activate the shader
	void Use() const;

	// Utility uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, float r, float g, float b) const;
	void SetVec3(const std::string& name, const Math::Vector3D& vec3) const;
	void SetVec4(const std::string& name, float r, float g, float b, float a) const;
	void SetVec4(const std::string& name, const Math::Vector4D& vec4) const;
	void SetMat4(const std::string& name, const Math::Matrix4D& mat) const;

private:

	/// <summary>
	/// Check status of program/shader. Returns success or failure and in that case
	/// prints the reason.
	/// </summary>
	/// <param name="program">Program object when linking or a vertex/fragment shader program</param>
	/// <param name="getProgramivFunc">E.g. glGetShaderiv or glGetProgramiv</param>
	/// <param name="statusToCheck">E.g. GL_COMPILE_STATUS or GL_LINK_STATUS</param>
	/// <param name="infoLogGetterFunc">E.g. glGetShaderInfoLog or glGetProgramInfoLog</param>
	/// <returns>True if program was </returns>
	bool CheckStatus(uint program, PFNGLGETSHADERIVPROC getProgramivFunc, uint statusToCheck, PFNGLGETPROGRAMINFOLOGPROC infoLogGetterFunc) const;
	
	/// <summary>
	/// Check status of shader. Returns success or failure and in that case
	/// prints the reason. Use after compiling a shader.
	/// </summary>
	/// <param name="shaderProgram">A vertex or fragment shader program.</param>
	/// <returns>True if shader compiled successfuly. Otherwise false and prints error.</returns>
	bool CheckCompilationStatus(const uint& shaderProgram) const;
	

	/// <summary>
	/// Check status of program linking using the member ID.
	/// </summary>
	/// <returns>True if program linked successfuly. Otherwise false and prints error.</returns>
	bool CheckLinkingStatus() const;
};