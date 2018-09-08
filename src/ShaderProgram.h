//-----------------------------------------------------------------------------
// ShaderProgram.h by Steve Jones 
// Copyright (c) 2015-2016 Game Institute. All Rights Reserved.
//
// GLSL shader manager class
//-----------------------------------------------------------------------------
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
using std::string;


class ShaderProgram
{
public:
	 ShaderProgram();
	~ShaderProgram();

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	// Only supports vertex and fragment (this series will only have those two)
	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();

	GLuint getProgram() const;

	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);
	void setUniform(const GLchar* name, const glm::mat4& m);

	// We are going to speed up looking for uniforms by keeping their locations in a map
	GLint getUniformLocation(const GLchar * name);

private:

	string fileToString(const string& filename);
	void  checkCompileErrors(GLuint shader, ShaderType type);

	
	GLuint mHandle;
	std::map<string, GLint> mUniformLocations;
};
#endif // SHADER_H