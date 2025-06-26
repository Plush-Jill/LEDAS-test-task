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

        /**
         * Initializes a vector with three coordinates.
         * @param xyz_values List of double values containing exactly three elements.
         * @throws std::invalid_argument if the initializer list does not contain exactly three elements.
         */
        Vector3D(std::initializer_list<double> xyz_values) noexcept(false);

        Vector3D& operator=(const Vector3D &other) noexcept(true);

        bool operator==(const Vector3D &other) const noexcept(true);

        Vector3D operator+(const Vector3D &other) const noexcept(true);

        Vector3D operator-(const Vector3D &other) const noexcept(true);

        Vector3D& operator*(double multiplier) const noexcept(true);

        [[nodiscard]] double getX() const noexcept(true);

        [[nodiscard]] double getY() const noexcept(true);

        [[nodiscard]] double getZ() const noexcept(true);

        [[nodiscard]] double getLength() const noexcept(true);
    };

    Vector3D vectorProduct(const Vector3D& a, const Vector3D& b) noexcept(true);

    double scalarProduct(const Vector3D& a, const Vector3D& b) noexcept(true);

} // ltt

#endif //VECTOR_3D_HPP
