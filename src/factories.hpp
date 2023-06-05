#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include "entt/entt.hpp"
#include "game_constants.hpp"
#include "graphics.hpp"

enum Types { FIRST_NONE = 0, CHMONYA = 0, BACKGROUND, ASTEROID, PLAYER, LAST_NONE };

struct Type {
	unsigned int type;
};

struct PositionAngle {
	float x, y;
	float angle;
};

struct Velocity {
	float velocity;
	float rotation_velocity;
};

struct Hitbox {
	std::vector<vertex> hitbox;

    size_t size() const
    {
        return hitbox.size();
    }
};

struct Asteroid {};

struct Player {};

inline entt::entity makeChmonya(entt::registry &reg) {
	const entt::entity e = reg.create();
	reg.emplace<Type>(e, CHMONYA);
	reg.emplace<PositionAngle>(e, 0., 0., 0.);
	return e;
}

inline entt::entity makeBackground(entt::registry &reg) {
	const entt::entity e = reg.create();
	reg.emplace<Type>(e, BACKGROUND);
	reg.emplace<PositionAngle>(e, 0., 0., 0.);
	return e;
}

inline entt::entity makeAsteroid(entt::registry &reg) {
	const entt::entity e = reg.create();
    reg.emplace<Asteroid>(e);
	reg.emplace<Type>(e, ASTEROID);
    reg.emplace<Hitbox>(e, ASTEROID_HITBOX);
	reg.emplace<PositionAngle>(e, 0., 0., 0.);
    reg.emplace<Velocity>(e, 0.f, 0.f);
	return e;
}

inline entt::entity makePlayer(entt::registry &reg) {
	const entt::entity e = reg.create();
	reg.emplace<Player>(e);
	reg.emplace<Type>(e, PLAYER);
    reg.emplace<Hitbox>(e, PLAYER_HITBOX);
	reg.emplace<PositionAngle>(e, 0., 0., 0.);
    reg.emplace<Velocity>(e, 0.f, 0.f);
	return e;
}

#endif // FACTORIES_HPP