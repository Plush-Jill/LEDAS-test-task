//
// Created by bocka on 2025-07-12.
//

#include "vector-3d.hpp"
#include <cmath>
#include <stdexcept>

#include <algorithm>

namespace ltt {

    Vector3D::Vector3D(const double x, const double y, const double z) noexcept(false) {
		if (std::isnan(x) || std::isnan(y) || std::isnan(z) ||
			std::isinf(x) || std::isinf(y) || std::isinf(z)) {
			throw std::invalid_argument("Coordinates cannot be NaN or inf.");
		}
		X = x;
		Y = y;
		Z = z;
	}

	Vector3D::Vector3D() noexcept(true) :
		X(0.0), Y(0.0), Z(0.0) {
	}

	Vector3D::Vector3D(const std::initializer_list<double> xyz_values) noexcept(false) {
        if (xyz_values.size() != 3) {
			throw std::invalid_argument("Initializer list must contain exactly three elements.");
		}

		if (std::ranges::any_of(xyz_values, [](const double val) { return std::isnan(val) || std::isinf(val); })) {
			throw std::invalid_argument("Coordinates cannot be NaN or inf.");
		}

		auto it = xyz_values.begin();
		X = *it++;
        Y = *it++;
        Z = *it;
    }

    bool Vector3D::operator==(const Vector3D &other) const noexcept(true) {
        return X == other.X && Y == other.Y && Z == other.Z;
    }

    Vector3D Vector3D::operator+(const Vector3D &other) const noexcept(false) {
    	const double sumX = X + other.X;
    	const double sumY = Y + other.Y;
    	const double sumZ = Z + other.Z;

		if (std::isinf(sumX) || std::isinf(sumY) || std::isinf(sumZ)) {
			throw std::overflow_error("Sum of vector coordinates is infinity.");
		}

    	return Vector3D(sumX, sumY, sumZ);
    }

    Vector3D Vector3D::operator-(const Vector3D &other) const noexcept(false) {
    	const double subX = X - other.X;
    	const double subY = Y - other.Y;
    	const double subZ = Z - other.Z;

    	if (std::isinf(subX) || std::isinf(subY) || std::isinf(subZ)) {
    		throw std::overflow_error("Sum of vector coordinates is infinity.");
    	}

    	return Vector3D(subX, subY, subZ);
    }

    double Vector3D::getX() const noexcept(true) { return X; }
    double Vector3D::getY() const noexcept(true) { return Y; }
    double Vector3D::getZ() const noexcept(true) { return Z; }

    double Vector3D::getLength() const noexcept(false) {
    	const double result = std::sqrt(X * X + Y * Y + Z * Z);
    	if (std::isinf(result)) {
			throw std::overflow_error("Length of the vector is infinity.");
    	}

        return result;
    }

    Vector3D Vector3D::operator*(const double multiplier) const noexcept(false) {
		const double productX = X * multiplier;
    	const double productY = Y * multiplier;
    	const double productZ = Z * multiplier;

    	if (std::isinf(productX) || std::isinf(productY) || std::isinf(productZ)) {
    		throw std::overflow_error("Multiplication of vector coordinates is infinity.");
    	}

        return Vector3D(productX,productY, productZ);
    }

    Vector3D vectorProduct(const Vector3D& a, const Vector3D& b) noexcept(false) {
        return Vector3D(
            a.getY() * b.getZ() - a.getZ() * b.getY(),
            a.getZ() * b.getX() - a.getX() * b.getZ(),
            a.getX() * b.getY() - a.getY() * b.getX()
        );
    }

    double scalarProduct(const Vector3D &a, const Vector3D &b) noexcept(false) {
    	const double result = std::sqrt(a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ());
    	if (std::isinf(result)) {
    		throw std::overflow_error("Length of the vector is infinity.");
    	}

        return result;
    }

} // ltt
