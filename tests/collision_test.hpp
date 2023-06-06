#ifndef TESTS_COLLISION_TEST_HPP
#define TESTS_COLLISION_TEST_HPP

#include "gtest/gtest.h"

#include "intersection.hpp"

const float pi = 3.141592f;

TEST(collision_test, collides)
{
	Hitbox a = SQUARE_VERTICES;
	Hitbox b = SQUARE_VERTICES;
	Hitbox c = SQUARE_VERTICES;

	//moved on Ox by 0.51
	for(vertex& v : b)
		v.x += 0.5f;

	//rotated 45 degrees ccw and moved by 0.5
	const float angle = pi/4.f;
	for(vertex& v : c)
	{
		vertex old_v = v;
		v.x = old_v.x*std::cos(angle) - old_v.y*std::sin(angle);
		v.y = old_v.x*std::sin(angle) + old_v.y*std::cos(angle);

		v = v + vertex{.5f, 0.f};
	}

	EXPECT_TRUE(is_intersect(a, a));
	EXPECT_TRUE(is_intersect(a, b));
	EXPECT_TRUE(is_intersect(a, c));
}

TEST(collision_test, not_collides)
{
	Hitbox a = SQUARE_VERTICES;
	Hitbox b = SQUARE_VERTICES;
	Hitbox c = SQUARE_VERTICES;

	//moved on Ox by 1.1
	for(vertex& v : b)
		v.x += 1.1f;

	//rotated 45 deg ccw and moved by (1.5, 1.5) - roughly a diagonal of this square
	const float angle = pi/4.f;
	for(vertex& v : c)
	{
		vertex old_v = v;
		v.x = old_v.x*std::cos(angle) - old_v.y*std::sin(angle);
		v.y = old_v.x*std::sin(angle) + old_v.y*std::cos(angle);

		v = v + vertex{1.5f, 1.5f};
	}

	EXPECT_FALSE(is_intersect(a, b));
	EXPECT_FALSE(is_intersect(a, c));
}

#endif // TESTS_COLLISION_TEST_HPP
