#ifndef CORE_APP_HPP
#define CORE_APP_HPP

/* External: */
#include "GL/glew.h"
#include "GLFW/glfw3.h"

/* Own: */
#include "exception.hpp"
#include "game.hpp"
#include "shader_program.hpp"
#include "systems.hpp"

inline void glfw_error_callback(int error, const char *description)
{
	throw OpenglError(description);
}

class App
{
  public:
	App(){};
	~App(){};

	void run()
	{
		/* Set OpenGL error callback: */
		glfwSetErrorCallback(glfw_error_callback);

		/* Initialize GLFW and hint to use OpenGl 3.3: */
		if (!glfwInit())
			throw OpenglError("Unable to initalize GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

		/* Vsync: */
		glfwSwapInterval(1);

		/* Enable blend and transparency: */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/* Compile and use shader program: */
		ShaderProgram shader_program("../res/shaders/vertex.vert", "../res/shaders/fragment.frag");
		shader_program.use();

		/*!!! TODO: here must the be implementaion of main menu before game itself is launched !!!*/

		/* Laucnh game: */
		Game game(window, shader_program);
		game.run();

		glfwTerminate();
	};
};

#endif
