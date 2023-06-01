#ifndef CORE_APP_HPP
#define CORE_APP_HPP

/* Std: */
#include <iostream>


/* External: */
#include "GL/glew.h"
#include "GLFW/glfw3.h"


/* Own: */
#include "shader_program.hpp"
#include "game.hpp"

class App {
  public:
	App(){};
	~App(){};

	void run() {
		/* Set OpenGL error callback: */
        glfwSetErrorCallback([](int error, const char* descriprion){throw std::runtime_error("TODO: NORMAL EXCEPTION!" + std::string(descriprion));});

		/* Initialize GLFW and hint to use OpenGl 3.3: */
		if (!glfwInit())
			throw std::runtime_error("TODO: make normal exception");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a window and make it current context: */
		GLFWwindow *window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
		if (!window) {
			glfwTerminate();
			throw std::runtime_error("TODO: make normal exception");
		}
		glfwMakeContextCurrent(window);

		/* Initialize GLEW: */
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			throw std::runtime_error("TODO: make normal exception");
		}

		/* Compile and use shader program: */
		ShaderProgram shader_program("../res/shaders/vertex.vert", "../res/shaders/fragment.frag");
		shader_program.use();

		/*!!! TODO: here must the be implementaion of main menu before game itself is launched !!!*/

		/* Laucnh game: */
		Game game(window);
		game.run();

		glfwTerminate();
	};
};

#endif
