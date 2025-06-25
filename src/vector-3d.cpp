//
// Created by bocka on 2025-06-25.
//

#include "vector-3d.hpp"
#include <stdexcept>
#include <cmath>

namespace ltt {
    Vector3D::Vector3D(const double x, const double y, const double z) noexcept(true)
        : m_x_(x), m_y_(y), m_z_(z) {}

    Vector3D::Vector3D(const Vector3D &other) noexcept(true) {
        m_x_ = other.m_x_;
        m_y_ = other.m_y_;
        m_z_ = other.m_z_;
    }

    Vector3D::Vector3D(const std::initializer_list<double> xyz_values) {
        if (xyz_values.size() != 3) {
            throw std::invalid_argument("Initializer list must contain exactly three elements.");
        }
        auto it = xyz_values.begin();
        m_x_ = *it++;
        m_y_ = *it++;
        m_z_ = *it;
    }

    Vector3D & Vector3D::operator=(const Vector3D &other) noexcept(true) {
        if (this != &other) {
            m_x_ = other.m_x_;
            m_y_ = other.m_y_;
            m_z_ = other.m_z_;
        }
        return *this;
    }

    bool Vector3D::operator==(const Vector3D &other) const noexcept(true) {
        return m_x_ == other.m_x_ && m_y_ == other.m_y_ && m_z_ == other.m_z_;
    }

    Vector3D Vector3D::operator+(const Vector3D &other) const noexcept(true) {
        return Vector3D(
            m_x_ + other.m_x_,
            m_y_ + other.m_y_,
            m_z_ + other.m_z_
        );
    }

    Vector3D Vector3D::operator-(const Vector3D &other) const noexcept(true) {
        return Vector3D(
            m_x_ - other.m_x_,
            m_y_ - other.m_y_,
            m_z_ - other.m_z_
        );
    }

    double Vector3D::getX() const noexcept(true) { return m_x_; }
    double Vector3D::getY() const noexcept(true) { return m_y_; }
    double Vector3D::getZ() const noexcept(true) { return m_z_; }

    double Vector3D::getLength() const noexcept(true) {
        return std::sqrt(m_x_ * m_x_ + m_y_ * m_y_ + m_z_ * m_z_);
    }


    Vector3D vectorProduct(const Vector3D& a, const Vector3D& b) {
        return Vector3D(
            a.getY() * b.getZ() - a.getZ() * b.getY(),
            a.getZ() * b.getX() - a.getX() * b.getZ(),
            a.getX() * b.getY() - a.getY() * b.getX()
        );
    }

    double scalarProduct(const Vector3D &a, const Vector3D &b) {
        return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
    }
} // ltt
