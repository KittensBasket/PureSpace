#ifndef CORE_SHADER_PROGRAM_HPP
#define CORE_SHADER_PROGRAM_HPP

#include <fstream>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "exception.hpp"

const size_t max_len = 2048;

void checkShaderErrors(unsigned int ShaderProgram);
void checkShaderProgramErrors(unsigned int program);

struct ShaderProgram
{
	ShaderProgram(const std::string vertex_path, const std::string fragment_path)
	{
		std::ifstream vertex_stream(vertex_path, std::ios::binary), fragment_stream(fragment_path, std::ios::binary);

		if (!vertex_stream)
			throw std::domain_error("Unable to open vertex shader in \"" + vertex_path + "\"");

		if (!fragment_stream)
			throw std::domain_error("Unable to open fragment shader in \"" + fragment_path + "\"");

		char *vertex_src = new char[max_len];
		char *fragment_src = new char[max_len];

		std::fill(vertex_src, vertex_src + max_len, 0);
		std::fill(fragment_src, fragment_src + max_len, 0);

		vertex_stream.read(vertex_src, max_len);
		fragment_stream.read(fragment_src, max_len);

		vertex_stream.close();
		fragment_stream.close();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_src, NULL);

		glCompileShader(vertex);
		checkShaderErrors(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_src, NULL);

		glCompileShader(fragment);
		checkShaderErrors(fragment);

		_id = glCreateProgram();

		glAttachShader(_id, vertex);
		glAttachShader(_id, fragment);

		glLinkProgram(_id);
		checkShaderProgramErrors(_id);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		delete[] vertex_src;
		delete[] fragment_src;

		_size_uniform_loc = glGetUniformLocation(_id, "Size");
		if(_size_uniform_loc == -1)
			throw ShaderProgramError("Unable to locate size uniform.");
	}

	~ShaderProgram()
	{
		glDeleteProgram(_id);
	}

	void use()
	{
		glUseProgram(_id);
	}

	void setSizeUniform(const float value)
	{
		glUniform1f(_size_uniform_loc, value);
	}

	int get_loc() {
		return _size_uniform_loc;
	}

  private:
	unsigned int _id;
	int _size_uniform_loc;
};

inline void checkShaderErrors(unsigned int ShaderProgram)
{
	int succes;
	char info_log[1024];

	glGetShaderiv(ShaderProgram, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(ShaderProgram, 1024, NULL, info_log);
		throw ShaderProgramError("Unable to compile: \n" + std::string(info_log));
	}
}

inline void checkShaderProgramErrors(unsigned int program)
{
	int succes;
	char info_log[1024];

	glGetProgramiv(program, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(program, 1024, NULL, info_log);
		throw ShaderProgramError("Unable to link: \n" + std::string(info_log));
	}
}

#endif // CORE_SHADER_PROGRAM_HPP
