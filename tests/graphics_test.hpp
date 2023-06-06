#ifndef TESTS_GRAPHICS_TEST_HPP
#define TESTS_GRAPHICS_TEST_HPP

#include "gtest/gtest.h"

#include "graphics.hpp"

TEST(graphics_test, create_graphics)
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

	Hitbox box = {{0, 0}};
	std::vector<vertex> vec = {{0.f, 0.f}}, vec2 = {{0, 0}, {1, 1}}, zero = {};
	std::vector<polygon> poly = {{1, 2, 3}};

	EXPECT_THROW(GraphicsData(zero, zero, poly, "res/textures/asteroid.png", 1.f, 0, 1), std::invalid_argument);

	EXPECT_THROW(GraphicsData(vec, zero, poly, "res/textures/asteroid.png", 1.f, 0, 1), std::invalid_argument);

	EXPECT_THROW(GraphicsData(vec, vec2, poly, "res/textures/asteroid.png", 1.f, 0, 1), std::invalid_argument);

	glfwTerminate();
}


TEST(graphics_test, create_graphics_correct)
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

	Hitbox box = {{0, 0}};
	std::vector<vertex> vec = {{0.f, 0.f}, {0.f, 0.f}, {0.f, 0.f}}, vec2 = {{0, 0}, {1, 1}}, zero = {};
	std::vector<polygon> poly = {{1, 2, 3}};

	EXPECT_NO_THROW(GraphicsData(vec, vec, poly, "res/textures/asteroid.png", 1.f, 0, 1));

	glfwTerminate();
}

TEST(graphics_test, instance_limit)
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

	Hitbox box = {{0, 0}};
	std::vector<vertex> vec = {{0.f, 0.f}, {0.f, 0.f}, {0.f, 0.f}}, vec2 = {{0, 0}, {1, 1}}, zero = {};
	std::vector<polygon> poly = {{1, 2, 3}};

	GraphicsData data = GraphicsData(vec, vec, poly, "res/textures/asteroid.png", 1.f, 0, 3);

	std::vector<instance>* inst_vec = data.get_vec();

	for(int i = 0; i < 10; i++) inst_vec->push_back({0, 0});

	EXPECT_THROW(data.draw(), std::length_error);

	glfwTerminate();
}

#endif // TESTS_GRAPHICS_TEST_HPP
