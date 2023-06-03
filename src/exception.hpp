#ifndef CORE_EXCEPTION_HPP
#define CORE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

struct ShaderProgramError : std::exception
{
	ShaderProgramError() : message()
	{
	}

	ShaderProgramError(const char *msg) : message(msg)
	{
	}

	ShaderProgramError(const std::string msg) : message(msg)
	{
	}

	const char *what() const noexcept
	{
		return (message_prefix + message).data();
	}

  private:
	const std::string message_prefix = "Shader program error. ";
	const std::string message;
};

struct OpenglError : std::exception
{
	OpenglError() : message()
	{
	}

	OpenglError(const char *msg) : message(msg)
	{
	}

	OpenglError(const std::string msg) : message(msg)
	{
	}

	const char *what() const noexcept
	{
		return (message_prefix + message).c_str();
	}

  private:
	const std::string message_prefix = "OpenGL error. ";
	const std::string message;
};

#endif //CORE_EXCEPTION_HPP
