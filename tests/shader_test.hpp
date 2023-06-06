#ifndef TESTS_SHADER_TEST_HPP
#define TESTS_SHADER_TEST_HPP

#include "gtest/gtest.h"

#include "shader_program.hpp"

TEST(shader_test, shader_file)
{
	/* Initialize GLFW and hint to use OpenGl 3.3: */
	if (!glfwInit())
		throw OpenglError("Unable to initalize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	/* Create a window and make it current context: */
	GLFWwindow *window = glfwCreateWindow(1080, 1080, "Pure Space", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw OpenglError("Unable to create window.");
	}
	glfwMakeContextCurrent(window);

	/* Initialize GLEW: */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw OpenglError("Unable to initialize GLEW.");
	}

	EXPECT_THROW(ShaderProgram(" ", " "), std::domain_error);

	EXPECT_THROW(ShaderProgram("res/shaders/vertex.vert", " "), std::domain_error);
	EXPECT_THROW(ShaderProgram(" ", "res/shaders/fragment.frag"), std::domain_error);

	glfwTerminate();
}

TEST(shader_test, shader_compilation)
{
	/* Initialize GLFW and hint to use OpenGl 3.3: */
	if (!glfwInit())
		throw OpenglError("Unable to initalize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	/* Create a window and make it current context: */
	GLFWwindow *window = glfwCreateWindow(1080, 1080, "Pure Space", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw OpenglError("Unable to create window.");
	}
	glfwMakeContextCurrent(window);

	/* Initialize GLEW: */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw OpenglError("Unable to initialize GLEW.");
	}

	EXPECT_THROW(ShaderProgram("res/shaders/fragment.frag", "res/shaders/vertex.vert"), ShaderProgramError);
	EXPECT_THROW(ShaderProgram("res/shaders/fragment.frag", "res/shaders/vertex.vert"), ShaderProgramError);

	glfwTerminate();
}

TEST(shader_test, shader_construct_correct)
{
	/* Initialize GLFW and hint to use OpenGl 3.3: */
	if (!glfwInit())
		throw OpenglError("Unable to initalize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	/* Create a window and make it current context: */
	GLFWwindow *window = glfwCreateWindow(1080, 1080, "Pure Space", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw OpenglError("Unable to create window.");
	}
	glfwMakeContextCurrent(window);

	/* Initialize GLEW: */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw OpenglError("Unable to initialize GLEW.");
	}

	EXPECT_NO_THROW(ShaderProgram("res/shaders/vertex.vert", "res/shaders/fragment.frag"));

	glfwTerminate();
}

#endif // TESTS_SHADER_TEST_HPP
