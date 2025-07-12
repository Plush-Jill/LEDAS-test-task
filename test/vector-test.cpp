//
// Created by bocka on 2025-07-12.
//

#include <cmath>
#include <gtest/gtest.h>
#include "vector-3d.hpp"

const ltt::Vector3D lowest_vector (
	std::numeric_limits<double>::lowest(),
	std::numeric_limits<double>::lowest(),
	std::numeric_limits<double>::lowest()
);

const ltt::Vector3D max_vector (
	std::numeric_limits<double>::max(),
	std::numeric_limits<double>::max(),
	std::numeric_limits<double>::max()
);


TEST(VectorTests, Constructor_test) {
	const ltt::Vector3D vector1 (1.0, 2.0, 3.0);
	EXPECT_DOUBLE_EQ(vector1.getX(), 1.0);
	EXPECT_DOUBLE_EQ(vector1.getY(), 2.0);
	EXPECT_DOUBLE_EQ(vector1.getZ(), 3.0);

	const ltt::Vector3D vector2;
	EXPECT_DOUBLE_EQ(vector2.getX(), 0.0);
	EXPECT_DOUBLE_EQ(vector2.getY(), 0.0);
	EXPECT_DOUBLE_EQ(vector2.getZ(), 0.0);

	const ltt::Vector3D vector3 {2.0, 3.0, 4.0};
	EXPECT_DOUBLE_EQ(vector3.getX(), 2.0);
	EXPECT_DOUBLE_EQ(vector3.getY(), 3.0);
	EXPECT_DOUBLE_EQ(vector3.getZ(), 4.0);

	EXPECT_THROW(
		const ltt::Vector3D vector4 (std::initializer_list<double>{1.0, 2.0}),
		std::invalid_argument);
	EXPECT_THROW(
		const ltt::Vector3D vector5 (std::initializer_list<double>{1.0, 2.0, std::numeric_limits<double>::quiet_NaN()}),
		std::invalid_argument);
}

TEST(VectorTests, Equality_test) {
	const ltt::Vector3D vector1 (1.0, 2.0, 3.0);
	const ltt::Vector3D vector2 (1.0, 2.0, 3.0);
	const ltt::Vector3D vector3 (4.0, 5.0, 6.0);

	EXPECT_TRUE(vector1 == vector2);
	EXPECT_FALSE(vector1 == vector3);
}

TEST(VectorTests, Addition_test) {
	const ltt::Vector3D vector1 (1.0, 2.0, 3.0);
	const ltt::Vector3D vector2 (4.0, 5.0, 6.0);
	const ltt::Vector3D result = vector1 + vector2;

	EXPECT_DOUBLE_EQ(result.getX(), 5.0);
	EXPECT_DOUBLE_EQ(result.getY(), 7.0);
	EXPECT_DOUBLE_EQ(result.getZ(), 9.0);

	EXPECT_THROW(
		const ltt::Vector3D overflow_result = max_vector + max_vector,
		std::overflow_error);
}

TEST(VectorTests, Subtraction_test) {
	const ltt::Vector3D vector1 (5.0, 7.0, 9.0);
	const ltt::Vector3D vector2 (4.0, 5.0, 6.0);
	const ltt::Vector3D result = vector1 - vector2;

	EXPECT_DOUBLE_EQ(result.getX(), 1.0);
	EXPECT_DOUBLE_EQ(result.getY(), 2.0);
	EXPECT_DOUBLE_EQ(result.getZ(), 3.0);

	EXPECT_THROW(
		const ltt::Vector3D overflow_result = lowest_vector - max_vector,
		std::overflow_error);
}

TEST(VectorTests, Multiplication_test) {
	const ltt::Vector3D vector1(1.0, 2.0, 3.0);
	constexpr double multiplier = 2.0;
	const ltt::Vector3D result = vector1 * multiplier;

	EXPECT_DOUBLE_EQ(result.getX(), 2.0);
	EXPECT_DOUBLE_EQ(result.getY(), 4.0);
	EXPECT_DOUBLE_EQ(result.getZ(), 6.0);

	EXPECT_THROW(
		const ltt::Vector3D overflow_result = vector1 * std::numeric_limits<double>::infinity(),
		std::overflow_error);
}

TEST(VectorTests, Length_test) {
	const ltt::Vector3D vector1 (3.0, 4.0, 0.0);
	EXPECT_DOUBLE_EQ(vector1.getLength(), 5.0);

	const ltt::Vector3D vector2 (1.0, 2.0, 2.0);
	EXPECT_DOUBLE_EQ(vector2.getLength(), std::sqrt(9.0));
}

TEST(VectorTests, ScalarProduct_test) {
	const ltt::Vector3D vector1 (1.0, 2.0, 3.0);
	const ltt::Vector3D vector2 (8.0, 5.0, 6.0);
	const double result = ltt::scalarProduct(vector1, vector2);

	EXPECT_DOUBLE_EQ(result, 6);
}

TEST(VectorTests, VectorProduct_test) {
	const ltt::Vector3D vector1 (1.0, 2.0, 3.0);
	const ltt::Vector3D vector2 (4.0, 5.0, 6.0);
	const ltt::Vector3D result = ltt::vectorProduct(vector1, vector2);

	EXPECT_DOUBLE_EQ(result.getX(), -3.0);
	EXPECT_DOUBLE_EQ(result.getY(), 6.0);
	EXPECT_DOUBLE_EQ(result.getZ(), -3.0);
}

// int main(int argc, char **argv) {
// 	::testing::InitGoogleTest(&argc, argv);
// 	return RUN_ALL_TESTS();
// }
