#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "entt/entt.hpp"

#include <filesystem>
#include <iostream>
#include <ostream>
#include <random>


#include "game_constants.hpp"
#include "shader_program.hpp"
#include "factories.hpp"
#include "systems.hpp"

class Game {
  private:
	GLFWwindow *window;
	ShaderProgram program;
	entt::registry registry;
	std::mt19937 gen_random;
	bool pauesd = false;

  public:
	Game(GLFWwindow *window, ShaderProgram &program) : window(window), program(program){};
	~Game(){};

	void run() {
		std::vector<GraphicsData*> graphics_map(LAST_NONE); 
		GraphicsData chmonyas_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/chmonya.jpg", MAX_CHMONYA_INSTANCES_CNT);
		graphics_map[CHMONYA] = &chmonyas_data;

		entt::entity chmonya1 = makeChmonya(registry);
		entt::entity chmonya2 = makeChmonya(registry);
		//registry.patch<PositionAngle>(chmonya1, [](auto &PositionAngle) { PositionAngle.x = PositionAngle.y = PositionAngle.angle = 0.; });
		//registry.patch<PositionAngle>(chmonya2, [](auto &PositionAngle) { PositionAngle.x = PositionAngle.y = PositionAngle.angle = 0.; });

		bool quit = 0;
		float angle = 0.0;

		while (!quit) {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.f, 0.5f, 0.5f, 1.f);

			graphics_system(registry, graphics_map);

			registry.patch<PositionAngle>(chmonya1, [](auto &PositionAngle) { PositionAngle.x = PositionAngle.y = PositionAngle.angle += 0.0001; });
			registry.patch<PositionAngle>(chmonya2, [](auto &PositionAngle) { PositionAngle.angle += 0.01; });

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	};
};

#endif // CORE_GAME_HPP