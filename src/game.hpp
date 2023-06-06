#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <filesystem>
#include <iostream>
#include <ostream>

#include "factories.hpp"
#include "frame_clock.hpp"
#include "game_constants.hpp"
#include "graphics.hpp"
#include "shader_program.hpp"
#include "systems.hpp"

struct metadata {
	entt::registry &registry;

	float vel = 0;
	float ang_vel = 0;
};

void key_callback(GLFWwindow *window, int key, int scanmode, int action, int mods) {

	if (action == GLFW_REPEAT)
		return;

	metadata *meta = (metadata *)glfwGetWindowUserPointer(window);
	auto &[registry, vel, ang_vel] = *meta;

	switch (key) {
	case GLFW_KEY_W:
		vel = (action == GLFW_PRESS) * PLAYER_SPEED;
		break;
	case GLFW_KEY_A:
		ang_vel = (action == GLFW_PRESS) * PLAYER_ANGLE_SPEED;
		break;
	case GLFW_KEY_S:
		vel = (action == GLFW_PRESS) * -PLAYER_SPEED;
		break;
	case GLFW_KEY_D:
		ang_vel = (action == GLFW_PRESS) * -PLAYER_ANGLE_SPEED;
		break;
	}

	controls_system(registry, vel, ang_vel);
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

		gen_random.seed(time(0));
		metadata meta{registry, 0.f, 0.f};

		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowUserPointer(window, &meta);

		std::vector<GraphicsData *> graphics_map(LAST_NONE);
		// GraphicsData chmonya_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS,
		// "../res/textures/chmonya.jpg", 0.5, shader_program.get_loc(), MAX_CHMONYA_INSTANCES_CNT);
		GraphicsData background_data(BACKGROUND_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS,
		                             "../res/textures/background.png", 1, shader_program.get_loc(), 1);
		GraphicsData asteroid_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS,
		                           "../res/textures/asteroid.png", asteroid_scale, shader_program.get_loc(),
		                           MAX_ASTEROIDS_INSTANCES_CNT);
		GraphicsData player_data(SQUARE_VERTICES, SQUARE_TEXTURE_COORDS, SQUARE_POLYGONS, "../res/textures/ship.png",
		                         player_scale, shader_program.get_loc(), 1);

		// graphics_map[CHMONYA] = &chmonya_data;
		graphics_map[ASTEROID] = &asteroid_data;
		graphics_map[BACKGROUND] = &background_data;
		graphics_map[PLAYER] = &player_data;

		entt::entity background = makeBackground(registry);
		entt::entity player = makePlayer(registry, {0., 0., 3.14/2}, {0, 0});

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

			factory_system(registry, gen_random);
			destructor_system(registry);
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