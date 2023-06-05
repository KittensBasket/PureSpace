#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "entt/entt.hpp"

#include <filesystem>
#include <iostream>
#include <ostream>
#include <random>


#include "frame_clock.hpp"
#include "game_constants.hpp"
#include "graphics.hpp"
#include "shader_program.hpp"
#include "factories.hpp"
#include "systems.hpp"

class Game {
  private:
	GLFWwindow *window;
	ShaderProgram shader_program;
	entt::registry registry;
	std::mt19937 gen_random;
	bool pauesd = false;

  public:
	Game(GLFWwindow *window, ShaderProgram &program) : window(window), shader_program(program){};
	~Game(){};


	void run() {
		std::vector<GraphicsData*> graphics_map(LAST_NONE);
		//GraphicsData chmonya_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/chmonya.jpg", 0.5, shader_program.get_loc(), MAX_CHMONYA_INSTANCES_CNT);
		GraphicsData background_data(BACKGROUND_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/background.png", 1, shader_program.get_loc(), 1);
		GraphicsData asteroid_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/asteroid.png", 0.4, shader_program.get_loc(), MAX_ASTEROIDS_INSTANCES_CNT);
		
		//graphics_map[CHMONYA] = &chmonya_data;
		graphics_map[ASTEROID] = &asteroid_data;
		graphics_map[BACKGROUND] = &background_data; 

		entt::entity background = makeBackground(registry); 
		entt::entity asteroid1 = makeAsteroid(registry);
		entt::entity asteroid2 = makeAsteroid(registry);
		entt::entity asteroid3 = makeAsteroid(registry);

		//entt::entity chmonya1 = makeChmonya(registry);
		//entt::entity chmonya2 = makeChmonya(registry);

		bool quit = 0;
		float angle = 0.0;

		while (!quit) {
			FrameClock frame{60};

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.f, 0.f, 0.f, 1.f);

			graphics_system(registry, graphics_map);

			registry.patch<PositionAngle>(asteroid1, [this](auto &PositionAngle) { PositionAngle.x = PositionAngle.y = PositionAngle.angle += 0.001; });
			registry.patch<PositionAngle>(asteroid2, [this](auto &PositionAngle) { PositionAngle.angle += 0.01; });
			registry.patch<PositionAngle>(asteroid3, [this](auto &PositionAngle) { PositionAngle.x = PositionAngle.y -= 0.003; });
			//registry.patch<PositionAngle>(chmonya2, [](auto &PositionAngle) { PositionAngle.angle += 0.01; });

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	};
};

#endif // CORE_GAME_HPP