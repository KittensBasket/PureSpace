#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "GLFW/glfw3.h"
#include "factories.hpp"

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

inline void controls_system(entt::registry* reg, float vel, float rot_vel) {
	auto view = reg->view<Player, Velocity>();
	for (const entt::entity e : view)
		reg->patch<Velocity>(e, [vel, rot_vel](auto &Velocity) {Velocity.velocity = vel; Velocity.rotation_velocity = rot_vel;});
}

#endif // SYSTEMS_HPP