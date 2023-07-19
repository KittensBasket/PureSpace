#include "gtest/gtest.h"

#include "collision_test.hpp"
#include "graphics_test.hpp"
#include "shader_test.hpp"

int main(int argc, char *argv[]) {
	glfwSetErrorCallback([](int error, const char *description) { throw OpenglError(description); });

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}