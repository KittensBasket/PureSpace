#ifndef CORE_SYSTEMS_HPP
#define CORE_SYSTEMS_HPP

#include <cmath>
#include <random>
#include <iostream>

#include "GLFW/glfw3.h"

#include "factories.hpp"
#include "game_constants.hpp"
#include "intersection.hpp"

inline void graphics_system(entt::registry &reg, std::vector<GraphicsData *> &graphics_map) {
	auto view = reg.view<Types, PositionAngle>();
	for (const entt::entity e : view)
		graphics_map[view.get<Types>(e)]->get_vec()->push_back(view.get<PositionAngle>(e));

	for (GraphicsData *graphics_data : graphics_map) {
		if (graphics_data == nullptr)
			continue;
		graphics_data->draw();
	}
}

inline void controls_system(entt::registry &reg, const float input_vel, const float input_ang_vel) {
	auto view = reg.view<Player, Velocity>();
	for (const entt::entity e : view) {
		auto &[vel, ang_vel] = view.get<Velocity>(e);
		vel = input_vel;
		ang_vel = input_ang_vel;
	}
}

inline void factory_system(entt::registry &reg, std::mt19937& random) {
	auto view = reg.view<Asteroid>();
	unsigned int asteroid_cnt = view.size();

	while (asteroid_cnt < ASTEROIDS_CNT) {
		float x_rand, y_rand, rot_rand;
		float vel, rot_vel;
		switch (random() % 4) {
		 	case 0:
		 		x_rand = float(random() % 31 - 15) / 10.;
		 		y_rand = float(random() % 5 + 11) / 10.;
				break;
		 	case 1:
		 		x_rand = float(random() % 31 - 15) / 10.;
		 		y_rand = float(random() % 5 + 11) / -10.;
				break;
		 	case 2:
		 		x_rand = float(random() % 5 + 11) / 10.;  
		 		y_rand = float(random() % 31 - 15) / 10.;
				break;
		 	case 3:
		 		x_rand = float(random() % 5 + 11) / -10.;  
		 		y_rand = float(random() % 31 - 15) / 10.;
				break;
		 }
		rot_rand = float(random() % 360);

		rot_vel = 0;
		vel = float(random() % ASTEROIDS_SPEED - (ASTEROIDS_SPEED/ 2.)) / 100. + 0.01;

		PositionAngle pos_rand = {x_rand, y_rand, rot_rand};
		Velocity vel_rand = {vel, rot_vel};

		makeAsteroid(reg, pos_rand, vel_rand);
		asteroid_cnt++;
	}
 }

inline void destructor_system(entt::registry &reg) {
	auto view = reg.view<PositionAngle>();
	for(entt::entity e : view) {
		PositionAngle pos =  view.get<PositionAngle>(e);
		if (pos.x > 1.5 || pos.x < -1.5 || pos.y > 1.5 || pos.y < -1.5)
			reg.destroy(e);
	}
}

inline void movement_system(entt::registry &reg) {
	auto view = reg.view<Velocity, Hitbox, PositionAngle>();

	for (const entt::entity e : view) {
		const auto [vel, ang_vel] = view.get<Velocity>(e);
		auto &[x, y, angle] = view.get<PositionAngle>(e);

		angle += ang_vel;

		const float old_x = x, old_y = y;
		x += vel * std::cos(angle);
		y += vel * std::sin(angle);

		Hitbox &hitbox = view.get<Hitbox>(e);
		for (vertex &v : hitbox) {
			const vertex old_v = v;
			v.x = (old_v.x - old_x) * std::cos(ang_vel) - (old_v.y - old_y) * std::sin(ang_vel) + x;
			v.y = (old_v.x - old_x) * std::sin(ang_vel) + (old_v.y - old_y) * std::cos(ang_vel) + y;
		}
	}
}

inline void collision_system(entt::registry &reg, bool &is_player_alive) {
	auto player_view = reg.view<Player, Hitbox>();
	auto asteroid_view = reg.view<Asteroid, Hitbox>();

	for (const entt::entity player : player_view) {
		for (const entt::entity asteroid : asteroid_view) {
			if (is_intersect(player_view.get<Hitbox>(player), asteroid_view.get<Hitbox>(asteroid))) {
				is_player_alive = false;
				return;
			}
		}
	}
}

#endif // CORE_SYSTEMS_HPP