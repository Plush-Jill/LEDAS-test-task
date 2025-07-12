//
// Created by bocka on 2025-07-12.
//

#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include <initializer_list>

namespace ltt {
    class Vector3D {
        public:

            /**
             * Initializes a vector with three coordinates.
             * @throws std::invalid_argument if any of the arguments are NaN.
             */
            explicit Vector3D(double x, double y, double z) noexcept(false);

            /**
             * Initializes a vector with three coordinates.
             * @param xyz_values List of double values containing exactly three elements.
             * @throws std::invalid_argument if the initializer list does not contain exactly three elements.
             * @throws std::invalid_argument if any of the elements are NaN.
             */
            Vector3D(std::initializer_list<double> xyz_values) noexcept(false);

            Vector3D(const Vector3D& other) noexcept(true) = default;

            Vector3D(Vector3D&& other) noexcept(true) = default;

            Vector3D& operator=(const Vector3D& other) noexcept(true) = default;

            Vector3D& operator=(Vector3D&& other) noexcept(true) = default;

            ~Vector3D() = default;

            bool operator==(const Vector3D &other) const noexcept(true);

            /**
             * @param other The vector to add to this vector.
             * @return Sum of this vector and the other vector.
             * @throws std::overflow_error if sum of any coordinates is infinity.
             */
            Vector3D operator+(const Vector3D &other) const noexcept(false);

            /**
             * @param other The vector to subtract from this vector.
             * @return Difference of this vector and the other vector.
             * @throws std::overflow_error if difference of any coordinates is infinity.
             */
            Vector3D operator-(const Vector3D &other) const noexcept(false);

             /**
             * @param multiplier The multiplier to multiply this vector with.
             * @throws std::overflow_error if multiplication of any coordinate is infinity.
             */
            Vector3D& operator*(double multiplier) const noexcept(true);

            [[nodiscard]] double getX() const noexcept(true);

            [[nodiscard]] double getY() const noexcept(true);

            [[nodiscard]] double getZ() const noexcept(true);

            /**
             * @return Length of the vector.
             * @throws std::overflow_error if length is infinity.
             */
            [[nodiscard]] double getLength() const noexcept(false);

        private:
            double X;
            double Y;
            double Z;
    };

    /**
     * Computes the scalar product of two vectors.
     * @param a First vector.
     * @param b Second vector.
     * @return Scalar product of a and b.
     * @throws std::overflow_error if the result is infinity.
     */
    double scalarProduct(const Vector3D& a, const Vector3D& b) noexcept(false);

    /**
     * Computes the vector product of two vectors.
     * @param a First vector.
     * @param b Second vector.
     * @return Vector product of a and b.
     * @throws std::overflow_error if any coordinate of the result is infinity.
     */
    Vector3D vectorProduct(const Vector3D& a, const Vector3D& b) noexcept(false);
} // ltt

#endif //VECTOR_3D_HPP
