#ifndef CORE_EXCEPTION_HPP
#define CORE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

struct ShaderProgramError : std::exception
{
	ShaderProgramError() : message()
	{
	}

	ShaderProgramError(const char *msg) : message(message_prefix + std::string(msg))
	{
	}

	ShaderProgramError(const std::string msg) : message(message_prefix + msg)
	{
	}

	const char *what() const noexcept override
	{
		return message.data();
	}

  private:
	const std::string message_prefix = "Shader program error. ";
	const std::string message = "";
};

struct OpenglError : std::exception
{
	OpenglError() : message()
	{
	}

	OpenglError(const char *msg) : message(message_prefix + std::string(msg))
	{
	}

	OpenglError(const std::string msg) : message(message_prefix + msg)
	{
	}

	const char *what() const noexcept override
	{
		return message.data();
	}

  private:
	const std::string message_prefix = "OpenGL error. ";
	const std::string message = "";
};

#endif //CORE_EXCEPTION_HPP
