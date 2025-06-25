//
// Created by bocka on 2025-06-25.
//

#include <gtest/gtest.h>

#include "../include/segment-3d.hpp"

TEST(test, test1) {
    ASSERT_EQ(1, 1);
    const ltt::Segment3D segment1(
        ltt::Vector3D(0, 0, 0),
        ltt::Vector3D(2, 0, 0)
    );
    const ltt::Segment3D segment2(
        ltt::Vector3D(1, 0, 1),
        ltt::Vector3D(1, 0, -1)
    );
    ASSERT_EQ(segment1.getStart(), ltt::Vector3D(0, 0, 0));
    EXPECT_EQ(segment1.isIntersect(segment2), true);

}
