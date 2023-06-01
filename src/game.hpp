#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "entt/entt.hpp"

#include <iostream>
#include <ostream>
#include <random>

#include "game_constants.hpp"
#include "graphics.hpp"

class Game {
  private:
	GLFWwindow *window;
	entt::registry registry;
	std::mt19937 gen_random;
	bool pauesd = false;

  public:
	Game(GLFWwindow *window) : window(window){};
	~Game(){};

	void run() {
		std::vector<instance> instances = {{0.f , 0.f, 0}, {1.f, 1.f, 3.14f}};
		GraphicsData graphics(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/chmonya.jpg", MAX_CHMONYA_INSTANCES_CNT);
		graphics.writeInstances(instances);

		bool quit = 0;
		float angle = 0.0;

		while (!quit) {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.f, 0.5f, 0.5f, 1.f);

			for (auto &inst : instances) {
        		inst.angle += angle;
			}
			graphics.writeInstances(instances);

			graphics.use();
			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0, instances.size());

			angle += 0.00001;

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	};
};

#endif // CORE_GAME_HPP