#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "entt/entt.hpp"

#include <filesystem>
#include <iostream>
#include <ostream>
#include <random>

#include "factories.hpp"
#include "frame_clock.hpp"
#include "game_constants.hpp"
#include "graphics.hpp"
#include "shader_program.hpp"
#include "systems.hpp"

inline float dx = 0;
inline float drot = 0;

void key_callback(GLFWwindow *window, int key, int scanmode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_W:
		if (action == GLFW_PRESS)
			dx = PLAYER_SPEED;
		if (action == GLFW_RELEASE)
			dx = 0;
		break;
	case GLFW_KEY_A:
		if (action == GLFW_PRESS)
			drot = PLAYER_ANGLE_SPEED;
		else if (action == GLFW_RELEASE)
			drot = 0;
		break;
	case GLFW_KEY_S:
		if (action == GLFW_PRESS)
			dx = -PLAYER_SPEED;
		else if (action == GLFW_RELEASE)
			dx = 0;
		break;
	case GLFW_KEY_D:
		if (action == GLFW_PRESS)
			drot = -PLAYER_ANGLE_SPEED;
		else if (action == GLFW_RELEASE)
			drot = 0;
		break;
	}

	entt::registry *registry = (entt::registry *)glfwGetWindowUserPointer(window);
	controls_system(registry, dx, drot);
}

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

		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowUserPointer(window, &registry);

		std::vector<GraphicsData *> graphics_map(LAST_NONE);
		// GraphicsData chmonya_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS,
		// "../res/textures/chmonya.jpg", 0.5, shader_program.get_loc(), MAX_CHMONYA_INSTANCES_CNT);
		GraphicsData background_data(BACKGROUND_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS,
		                             "../res/textures/background.png", 1, shader_program.get_loc(), 1);
		GraphicsData asteroid_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS,
		                           "../res/textures/asteroid.png", asteroid_scale, shader_program.get_loc(),
		                           MAX_ASTEROIDS_INSTANCES_CNT);
		GraphicsData player_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/ship.png",
		                         player_scale, shader_program.get_loc(), 2);

		// graphics_map[CHMONYA] = &chmonya_data;
		graphics_map[ASTEROID] = &asteroid_data;
		graphics_map[BACKGROUND] = &background_data;
		graphics_map[PLAYER] = &player_data;

		entt::entity background = makeBackground(registry);
		entt::entity player = makePlayer(registry);
		entt::entity asteroid1 = makeAsteroid(registry);

		registry.patch<PositionAngle>(player, [](auto &pos_ang) { pos_ang.x = 0.5f, pos_ang.y = 0.5f; });

		for(int i = 0; i < 4; i++)
			std::cerr << PLAYER_HITBOX[i].x << " " << PLAYER_HITBOX[i].y << "!" << std::endl;

		// registry.patch<PositionAngle>(asteroid1, [this](auto &PositionAngle) {
		// 	PositionAngle.x = PositionAngle.y = PositionAngle.angle += 0.5f;
		// });

		// entt::entity asteroid2 = makeAsteroid(registry);
		// entt::entity asteroid3 = makeAsteroid(registry);

		// entt::entity chmonya1 = makeChmonya(registry);
		// entt::entity chmonya2 = makeChmonya(registry);

		float angle = 0.0;
		bool is_player_alive = true;

		while (!glfwWindowShouldClose(window) && is_player_alive) {
			FrameClock frame{60};

			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.f, 0.f, 0.f, 1.f);

			collision_system(registry, is_player_alive);
			movement_system(registry);
			graphics_system(registry, graphics_map);

			// registry.patch<PositionAngle>(asteroid1, [this](auto &PositionAngle) { PositionAngle.x = PositionAngle.y
			// = PositionAngle.angle += 0.001; }); registry.patch<PositionAngle>(asteroid2, [this](auto &PositionAngle)
			// { PositionAngle.angle += 0.01; }); registry.patch<PositionAngle>(asteroid3, [this](auto &PositionAngle) {
			// PositionAngle.x = PositionAngle.y -= 0.003; });
			// registry.patch<PositionAngle>(chmonya2, [](auto &PositionAngle) { PositionAngle.angle += 0.01; });

			glfwSwapBuffers(window);
		}
	};
};

#endif // CORE_GAME_HPP