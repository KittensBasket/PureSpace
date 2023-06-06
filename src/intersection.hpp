#ifndef CORE_INTERSECTION_HPP
#define CORE_INTERSECTION_HPP

#include <cmath>

#include "factories.hpp"
#include "game_constants.hpp"

inline float dot_product(const vertex &a, const vertex &b) { return a.x * b.x + a.y * b.y; }

bool SAT(const Hitbox &base, const Hitbox &oth) {

	for (int i = 0; i < base.size(); i++) {
		vertex side = (base[i] - base[(i + 1) % base.size()]);
		side = side * (1.f / std::sqrt(side.x * side.x + side.y * side.y));

		float base_proj_min = dot_product(side, base[0]), base_proj_max = dot_product(side, base[0]);

		for (int j = 0; j < base.size(); j++) {

			float cur_proj = dot_product(side, base[j]);
			base_proj_max = std::max(base_proj_max, cur_proj);
			base_proj_min = std::min(base_proj_min, cur_proj);
		}

		float oth_proj_min = dot_product(side, oth[0]), oth_proj_max = dot_product(side, oth[0]);

		for (int j = 0; j < oth.size(); j++) {
			float cur_proj = dot_product(side, oth[j]);
			oth_proj_max = std::max(oth_proj_max, cur_proj);
			oth_proj_min = std::min(oth_proj_min, cur_proj);
		}

		// They have a gap
		if (base_proj_min - oth_proj_max > 0 || oth_proj_min - base_proj_max > 0)
			return false;
	}

	return true;
}

bool is_intersect(const Hitbox &a, const Hitbox &b) { return SAT(a, b) || SAT(b, a); }

#endif // CORE_INTERSECTION_HPP