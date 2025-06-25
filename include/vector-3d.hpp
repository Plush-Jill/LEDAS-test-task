//
// Created by bocka on 2025-06-25.
//

#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP
#include <initializer_list>

namespace ltt {

    class Vector3D {
    private:
        double m_x_;
        double m_y_;
        double m_z_;

    public:

        explicit Vector3D(double x, double y, double z) noexcept(true);
        Vector3D(const Vector3D& other) noexcept(true);
        Vector3D(std::initializer_list<double> xyz_values) noexcept(false);
        Vector3D& operator=(const Vector3D &other) noexcept(true);
        bool operator==(const Vector3D &other) const noexcept(true);
        Vector3D operator+(const Vector3D &other) const noexcept(true);
        Vector3D operator-(const Vector3D &other) const noexcept(true);

        [[nodiscard]] double getX() const noexcept(true);
        [[nodiscard]] double getY() const noexcept(true);
        [[nodiscard]] double getZ() const noexcept(true);
        [[nodiscard]] double getLength() const noexcept(true);
    };

    Vector3D vectorProduct(const Vector3D& a, const Vector3D& b);

    double scalarProduct(const Vector3D& a, const Vector3D& b);

} // ltt

#endif //VECTOR_3D_HPP
