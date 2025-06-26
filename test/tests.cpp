//
// Created by bocka on 2025-06-25.
//

#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/segment-3d.hpp"

TEST(Tests, Constructor_test) {
    // Test regular constructor
    const ltt::Segment3D segment1(ltt::Vector3D(0, 0, 0), ltt::Vector3D(1, 1, 1));
    EXPECT_EQ(segment1.getStart(), ltt::Vector3D(0, 0, 0));
    EXPECT_EQ(segment1.getEnd(), ltt::Vector3D(1, 1, 1));

    // Test initializer list constructor
    const ltt::Segment3D segment2 {ltt::Vector3D(2, 2, 2), ltt::Vector3D(3, 3, 3)};
    EXPECT_EQ(segment2.getStart(), ltt::Vector3D(2, 2, 2));
    EXPECT_EQ(segment2.getEnd(), ltt::Vector3D(3, 3, 3));

    // Test invalid initializer list
    EXPECT_THROW({
        const ltt::Segment3D invalid_segment{ltt::Vector3D(1, 1, 1)};
    }, std::invalid_argument);
}

TEST(Tests, getLength_test) {
    // Test zero length
    const ltt::Segment3D segment1 {{1, 1, 1}, {1, 1, 1}};
    EXPECT_DOUBLE_EQ(segment1.getLength(), 0.0);

    // Test unit length along x axis
    const ltt::Segment3D segment2 {{0, 0, 0}, {1, 0, 0}};
    EXPECT_DOUBLE_EQ(segment2.getLength(), 1.0);

    // Test diagonal length
    const ltt::Segment3D segment3 {{0, 0, 0}, {1, 1, 1}};
    EXPECT_DOUBLE_EQ(segment3.getLength(), std::sqrt(3.0));
}

TEST(Tests, getDirectionVector_test) {
    const ltt::Segment3D segment {{1, 2, 3}, {4, 6, 8}};
    const ltt::Vector3D direction = segment.getDirectionVector();
    EXPECT_EQ(direction, ltt::Vector3D(3, 4, 5));
}

TEST(Tests, isParallel_test) {
    // Test parallel segments
    const ltt::Segment3D segment1 {{0, 0, 0}, {2, 0, 0}};
    const ltt::Segment3D segment2 {{1, 1, 0}, {3, 1, 0}};
    EXPECT_TRUE(segment1.isParallel(segment2));

    // Test parallel segments in different planes
    const ltt::Segment3D segment3 {{0, 0, 0}, {2, 0, 0}};
    const ltt::Segment3D segment4 {{0, 1, 1}, {2, 1, 1}};
    EXPECT_TRUE(segment3.isParallel(segment4));

    // Test non-parallel segments
    const ltt::Segment3D segment5 {{0, 0, 0}, {1, 1, 0}};
    const ltt::Segment3D segment6 {{0, 0, 0}, {1, -1, 0}};
    EXPECT_FALSE(segment5.isParallel(segment6));

    // Test overlapping segments
    const ltt::Segment3D segment7 {{0, 0, 0}, {2, 0, 0}};
    const ltt::Segment3D segment8 {{1, 0, 0}, {3, 0, 0}};
    EXPECT_TRUE(segment7.isParallel(segment8));
}

TEST(Tests, isInSamePlane_test) {
    // Test coplanar segments
    const ltt::Segment3D segment1 {{0, 0, 0}, {2, 0, 0}};
    const ltt::Segment3D segment2 {{0, 1, 0}, {2, 1, 0}};
    EXPECT_TRUE(segment1.isInSamePlane(segment2));

    // Test non-coplanar segments
    const ltt::Segment3D segment3 {{0, 0, 0}, {1, 0, 0}};
    const ltt::Segment3D segment4 {{0, 1, 1}, {1, 1, 2}};
    EXPECT_FALSE(segment3.isInSamePlane(segment4));

    // Test segments with common point
    const ltt::Segment3D segment5 {{0, 0, 0}, {1, 1, 1}};
    const ltt::Segment3D segment6 {{0, 0, 0}, {1, -1, 1}};
    EXPECT_TRUE(segment5.isInSamePlane(segment6));
}

TEST(Tests, isIntersect_test) {
    // Test intersecting segments
    const ltt::Segment3D segment1 {{-1, 0, 0}, {1, 0, 0}};
    const ltt::Segment3D segment2 {{0, -1, 0}, {0, 1, 0}};
    const std::optional<ltt::Vector3D> intersection = segment1.intersect(segment2);
    EXPECT_TRUE(intersection.has_value() & (intersection.value() == ltt::Vector3D(0, 0, 0)));

    const ltt::Segment3D segment3 {{0.0, 0.0, 0.0}, {3.0, 1.0, 0.0}};
    const ltt::Segment3D segment4 {{1.0, -1.0, 0.0}, {2.0, 2.0, 0.0}};
    const std::optional<ltt::Vector3D> intersection2 = segment3.intersect(segment4);
    EXPECT_TRUE(intersection2.has_value() & (intersection2.value() == ltt::Vector3D(1.5, 0.5, 0.0)));

    const ltt::Segment3D segment5 {{1, 1, 1}, {13.34, 1, 1}};
    const ltt::Segment3D segment6 {{1, 1, 2.23}, {15.76, 1, -5.42}};
    const std::optional<ltt::Vector3D> intersection3 = segment5.intersect(segment6);
    EXPECT_TRUE(intersection3.has_value());

    const ltt::Segment3D segment7 {{0, 0, 0}, {10, 0, 0}};
    const ltt::Segment3D segment8 {{0, 1, 1}, {10, -1, -1}};
    const std::optional<ltt::Vector3D> intersection4 = segment7.intersect(segment8);
    EXPECT_TRUE(intersection4.has_value());

    constexpr double x_add = 2.32;
    constexpr double y_add = 1.83;
    constexpr double z_add = 0.64;
    const ltt::Segment3D segment9 {{0 + x_add, 0 + y_add, 0 + z_add}, {10 + x_add, 0 + y_add, 0 + z_add}};
    const ltt::Segment3D segment10 {{0 + x_add, 1 + y_add, 1 + z_add}, {10 + x_add, -1 + y_add, -1 + z_add}};
    const std::optional<ltt::Vector3D> intersection5 = segment9.intersect(segment10);
    EXPECT_TRUE(intersection5.has_value());

    const ltt::Segment3D segment11 {{1.2, 1.15, 1}, {15.0, -1.3, 1}};
    const ltt::Segment3D segment12 {{-1.56, -2.32, 1}, {23.24, 4.0, 1}};;
    const std::optional<ltt::Vector3D> intersection6 = segment11.intersect(segment12);
    EXPECT_TRUE(intersection6.has_value());

    // Test non-intersecting segments in same plane
    const ltt::Segment3D segment13 {{-1, 0, 0}, {0, 0, 0}};
    const ltt::Segment3D segment14 {{1, 0, 0}, {2, 0, 0}};
    const std::optional<ltt::Vector3D> intersection7 = segment13.intersect(segment14);
    EXPECT_FALSE(intersection7.has_value());

    // Test non-coplanar segments
    const ltt::Segment3D segment15 {{0, 0, 0}, {1, 0, 0}};
    const ltt::Segment3D segment16 {{0, 1, 1}, {0, 2, 1}};
    const std::optional<ltt::Vector3D> intersection8 = segment15.intersect(segment16);
    EXPECT_FALSE(intersection8.has_value());

    // Test parallel segments
    const ltt::Segment3D segment17 {{0, 0, 0}, {1, 0, 0}};
    const ltt::Segment3D segment18 {{0, 1, 0}, {1, 1, 0}};
    const std::optional<ltt::Vector3D> intersection9 = segment17.intersect(segment18);
    EXPECT_FALSE(intersection9.has_value());
}