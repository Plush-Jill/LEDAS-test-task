//
// Created by bocka on 2025-06-25.
//

#ifndef SEGMENT_3D_HPP
#define SEGMENT_3D_HPP
#include "vector-3d.hpp"

namespace ltt {

    class Segment3D {
    private:
        Vector3D m_start_;
        Vector3D m_end_;

    public:
        explicit Segment3D(const Vector3D &start, const Vector3D &end) noexcept(true);

        Segment3D(std::initializer_list<Vector3D> endpoints) noexcept(false);
        Segment3D& operator=(Segment3D&& other) noexcept(true);
        [[nodiscard]] Vector3D getStart() const noexcept(true);
        [[nodiscard]] Vector3D getEnd() const noexcept(true);
        [[nodiscard]] double getLength() const noexcept(true);
        [[nodiscard]] Vector3D getDirectionVector() const noexcept(true);
        [[nodiscard]] bool isParallel(const Segment3D &other) const noexcept(true);
        [[nodiscard]] bool isInSamePlane(const Segment3D &other) const noexcept(true);
        [[nodiscard]] bool isIntersect(const Segment3D &other) const noexcept(true);
    };



} // ltt

#endif //SEGMENT_3D_HPP
