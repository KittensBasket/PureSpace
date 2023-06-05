#ifndef CORE_SYSTEMS_HPP
#define CORE_SYSTEMS_HPP

#include <cmath>

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