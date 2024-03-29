#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
private:
	std::vector<GLuint> shaders;
public:
	GLuint program;
	Shader();
	~Shader();

	void addVertexShader(const char* filepath);
	void addGeometryShader(const char* filepath);
	void addFragmentShader(const char* filepath);
	void addProgram(const char* shader_path, GLenum type);
	void compileShader() const;

	/*
		IMPORTANT:
		Before setting any uniforms, be sure to bind shader.
		Ex:
		shader.bind()
		shader.setUniform1f("width", texture.getWidth());
	*/
	void setUniform1f(const GLchar* name, float value) const;
	void setUniform1fv(const GLchar* name, float* value, int count) const;
	void setUniform1i(const GLchar* name, int value) const;
	void setUniform1iv(const GLchar* name, int* value, int count) const;
	void setUniform2f(const GLchar* name, const glm::vec2& vector) const;
	void setUniform3f(const GLchar* name, const glm::vec3& vector) const;
	void setUniform4f(const GLchar* name, const glm::vec4& vector) const;
	void setUniformMat4(const GLchar* name, const glm::mat4& matrix) const;

	void bind() const;
	void unbind() const;
private:
	GLint getUniformLocation(const GLchar* name) const;

};
