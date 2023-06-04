#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include "graphics.hpp"
#include "entt/entt.hpp"

enum Types {
    FIRST_NONE = 0,
    CHMONYA = 0,
    LAST_NONE
};

struct Type {
    unsigned int type;
};

struct PositionAngle {
    float x, y;
	float angle;
};

inline entt::entity makeChmonya(entt::registry &reg) {
    const entt::entity e = reg.create();
    reg.emplace<Type>(e, CHMONYA);
    reg.emplace<PositionAngle>(e, 0., 0., 0.);
    return e;
}

#endif // FACTORIES_HPP