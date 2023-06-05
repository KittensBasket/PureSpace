#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "GLFW/glfw3.h"
#include "factories.hpp"

#include "game_constants.hpp"
#include "intersection.hpp"
#include <cmath>

inline void graphics_system(entt::registry &reg, std::vector<GraphicsData *> &graphics_map) {
	auto view = reg.view<Type, PositionAngle>();
	for (const entt::entity e : view) {
		auto i = view.get<Type>(e);
		std::vector<instance> *vbo_vec = graphics_map[view.get<Type>(e).type]->get_vec();
		vbo_vec->push_back(
		    {view.get<PositionAngle>(e).x, view.get<PositionAngle>(e).y, view.get<PositionAngle>(e).angle});
	}
	for (GraphicsData *graphics_data : graphics_map) {
		if (graphics_data == nullptr)
			continue;
		graphics_data->draw();
	}
}

inline void controls_system(entt::registry *reg, float vel, float ang_vel) {
	auto view = reg->view<Player, Velocity>();
	for (const entt::entity e : view)
		reg->patch<Velocity>(e, [vel, ang_vel](auto &velocity) {
			velocity.velocity = vel;
			velocity.rotation_velocity = ang_vel;
		});
}

inline void movement_system(entt::registry &reg) {
	auto view = reg.view<Velocity, PositionAngle>();

	for (const entt::entity e : view) {
		auto vel = view.get<Velocity>(e);
		reg.patch<PositionAngle>(e, [&vel](PositionAngle &pos_ang) {
			pos_ang.angle += vel.rotation_velocity;
			pos_ang.x += vel.velocity * std::cos(pos_ang.angle);
			pos_ang.y += vel.velocity * std::sin(pos_ang.angle);
		});
	}
}

inline void collision_system(entt::registry &reg, bool &is_player_alive) {
	auto player_view = reg.view<Player, Hitbox, PositionAngle>();

	auto asteroids_view = reg.view<Asteroid, Hitbox, PositionAngle>();

	for (const entt::entity player : player_view) {
		
		PositionAngle pos_ang = player_view.get<PositionAngle>(player);
		Hitbox hitbox = player_view.get<Hitbox>(player);
		
		for(int i = 0; i < hitbox.size(); i++)
		{
			hitbox.hitbox[i].x *= std::cos(pos_ang.angle);
			hitbox.hitbox[i].y *= std::sin(pos_ang.angle);

			hitbox.hitbox[i].x += pos_ang.x;
			hitbox.hitbox[i].y += pos_ang.y;
		}

		for (const entt::entity asteroid : asteroids_view) {
			PositionAngle pos_ang2 = asteroids_view.get<PositionAngle>(asteroid);
			Hitbox hitbox2 = asteroids_view.get<Hitbox>(asteroid);
			
			for(int i = 0; i < hitbox2.size(); i++)
			{
				hitbox2.hitbox[i].x *= std::cos(pos_ang2.angle);
				hitbox2.hitbox[i].y *= std::sin(pos_ang2.angle);
				
				hitbox2.hitbox[i].x += pos_ang2.x;
				hitbox2.hitbox[i].y += pos_ang2.y;
			}

			if (is_intersect(hitbox, hitbox2)) {
				is_player_alive = false;
				reg.destroy(player);
				return;
			}
		}
	}
}

#endif // SYSTEMS_HPP