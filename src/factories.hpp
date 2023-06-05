#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include "entt/entt.hpp"
#include "game_constants.hpp"
#include "graphics.hpp"

enum Types { FIRST_NONE = 0, CHMONYA = 0, BACKGROUND, ASTEROID, PLAYER, LAST_NONE };

struct Asteroid {};

struct Player {};

Hitbox transform(const Hitbox& hitbox, const PositionAngle& transf);

inline entt::entity makeChmonya(entt::registry &reg) {
	const entt::entity e = reg.create();
	reg.emplace<Types>(e, CHMONYA);
	reg.emplace<PositionAngle>(e, 0., 0., 0.);
	return e;
}

inline entt::entity makeBackground(entt::registry &reg) {
	const entt::entity e = reg.create();
	reg.emplace<Types>(e, BACKGROUND);
	reg.emplace<PositionAngle>(e, 0., 0., 0.);
	return e;
}

inline entt::entity makeAsteroid(entt::registry &reg, const PositionAngle& base, const Velocity& vel) {
	const entt::entity e = reg.create();
	reg.emplace<Asteroid>(e);
	reg.emplace<Types>(e, ASTEROID);
	reg.emplace<Hitbox>(e, transform(ASTEROID_HITBOX, base));
	reg.emplace<PositionAngle>(e, base);
	reg.emplace<Velocity>(e, vel);
	return e;
}

inline entt::entity makePlayer(entt::registry &reg, const PositionAngle& base, const Velocity& vel) {
	const entt::entity e = reg.create();
	reg.emplace<Player>(e);
	reg.emplace<Types>(e, PLAYER);
	reg.emplace<Hitbox>(e, transform(PLAYER_HITBOX, base));
	reg.emplace<PositionAngle>(e, base);
	reg.emplace<Velocity>(e, vel);
	return e;
}

Hitbox transform(const Hitbox& hitbox, const PositionAngle& transf)
{
	const auto [x, y, angle] = transf;

	Hitbox transf_hitbox = hitbox;
	for(vertex& v : transf_hitbox)
	{
		vertex old_v = v;
		v.x = old_v.x*std::cos(angle) - old_v.y*std::sin(angle);
		v.y = old_v.x*std::sin(angle) + old_v.y*std::cos(angle);

		v = v + vertex{x, y};
	}

	return transf_hitbox;
}

#endif // CORE_FACTORIES_HPP