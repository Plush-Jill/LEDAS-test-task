//
// Created by bocka on 2025-06-25.
//

#include "segment-3d.hpp"
#include <stdexcept>
#include <cmath>

namespace ltt {
    Segment3D::Segment3D(const Vector3D &start, const Vector3D &end) noexcept(true) : m_start_(start), m_end_(end) {}

    Segment3D::Segment3D(const std::initializer_list<Vector3D> endpoints)
        : Segment3D(endpoints.size() != 2 ?
                    throw std::invalid_argument("Segment3D must be initialized with exactly two Vector3D objects.")
                    : *endpoints.begin(),

                    *(endpoints.begin() + 1)) {
    }


    Segment3D& Segment3D::operator=(Segment3D &&other) noexcept(true) {
        if (this != &other) {
            m_start_ = other.m_start_;
            m_end_ = other.m_end_;
        }
        return *this;
    }

    Vector3D Segment3D::getStart() const noexcept(true) { return m_start_;}
    Vector3D Segment3D::getEnd() const noexcept(true) { return m_end_;}

    double Segment3D::getLength() const noexcept(true) {
        const double dx = m_end_.getX() - m_start_.getX();
        const double dy = m_end_.getY() - m_start_.getY();
        const double dz = m_end_.getZ() - m_start_.getZ();
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    Vector3D Segment3D::getDirectionVector() const noexcept(true) {
        return m_end_ - m_start_;
    }

    bool Segment3D::isParallel(const Segment3D &other) const noexcept(true) {
        const Vector3D direction1 = getDirectionVector();
        const Vector3D direction2 = other.getDirectionVector();

        const Vector3D normal = vectorProduct(direction1, direction2);
        if (normal.getLength() == 0) {
            return true;
        }
        return false;
    }

    bool Segment3D::isInSamePlane(const Segment3D &other) const noexcept(true) {
        const Vector3D start_connect_vector = m_start_ - other.m_start_;
        const double triple_vector_product = scalarProduct(
            start_connect_vector,
            vectorProduct(getDirectionVector(), other.getDirectionVector()));

        if (std::abs(triple_vector_product) > 0) {
            return false;
        }
        return true;
    }

    bool Segment3D::isIntersect(const Segment3D &other) const noexcept(true) {
        if (isParallel(other)) {
            return false;
        }

        const Vector3D direction1 = getDirectionVector();
        const Vector3D direction2 = other.getDirectionVector();
        const Vector3D start_connect_vector = m_start_ - other.m_start_;

        const double t1 = scalarProduct(vectorProduct(start_connect_vector, direction2), vectorProduct(direction1, direction2)) /
                          scalarProduct(vectorProduct(direction1, direction2), vectorProduct(direction1, direction2));

        const double t2 = scalarProduct(vectorProduct(start_connect_vector, direction1), vectorProduct(direction1, direction2)) /
                          scalarProduct(vectorProduct(direction1, direction2), vectorProduct(direction1, direction2));

        return (t1 >= 0 && t1 <= 1) && (t2 >= 0 && t2 <= 1);
    }
} // ltt