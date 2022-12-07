#ifndef TRACKINGCAMERASPEAKER_VECTOR3_HPP
#define TRACKINGCAMERASPEAKER_VECTOR3_HPP

#include "vector/Vector.hpp"

namespace worTCS {

    /// Struct to store int or float data via XYZ
    /// \tparam T int/float value
    template<typename T>
    struct Vector3
            : public Vector<T> {
        T x, y, z;

        Vector3() noexcept;

        Vector3(T x_, T y_, T z_) noexcept;

#pragma region Operators

        friend bool operator<(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept;

        friend bool operator>(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept;

        friend bool operator<=(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept;

        friend bool operator>=(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept;

        Vector3<T> &operator*=(T rhs_) noexcept;

        Vector3<T> &operator*=(const Vector3<T> &rhs_) noexcept;

        Vector3<T> &operator/=(T rhs_) noexcept;

        Vector3<T> &operator/=(const Vector3<T> &rhs_) noexcept;

        Vector3<T> &operator+=(T rhs_) noexcept;

        Vector3<T> &operator+=(const Vector3<T> &rhs_) noexcept;

        Vector3<T> &operator-=(T rhs_) noexcept;

        Vector3<T> &operator-=(const Vector3<T> &rhs_) noexcept;

        Vector3<T> &operator=(T rhs_) noexcept;

        friend Vector3<T> operator+(Vector3<T> lhs_, Vector3<T> rhs_) noexcept;

        friend Vector3<T> operator+(Vector3<T> lhs_, T rhs_) noexcept;

        friend Vector3<T> operator-(Vector3<T> lhs_, T rhs_) noexcept;

        friend Vector3<T> operator-(Vector3<T> lhs_, Vector3<T> rhs_) noexcept;

        bool operator==(const Vector3<T> &rhs_) const noexcept;

        bool operator!=(const Vector3<T> &rhs_) const noexcept;

#pragma endregion Operators
    };

    template<typename T>
    Vector3<T>::Vector3() noexcept {
        x = static_cast<T>(0);
        y = static_cast<T>(0);
        z = static_cast<T>(0);
    }

    template<typename T>
    Vector3<T>::Vector3(T x_, T y_, T z_) noexcept
            : x(x_), y(y_), z(z_) {}

#pragma region Operators

    template<typename T>
    bool operator<(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept {
        return lhs_.x < rhs_.x
               && lhs_.y < rhs_.y
               && lhs_.z < rhs_.z;
    }

    template<typename T>
    bool operator>(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept {
        return rhs_ < lhs_;
    }

    template<typename T>
    bool operator>=(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept {
        return !(lhs_ < rhs_);
    }

    template<typename T>
    bool operator<=(const Vector3<T> &lhs_, const Vector3<T> &rhs_) noexcept {
        return !(lhs_ > rhs_);
    }

    template<typename T>
    bool Vector3<T>::operator==(const Vector3<T> &rhs_) const noexcept {
        return x == rhs_.x
               && y == rhs_.y
               && z == rhs_.z;
    }

    template<typename T>
    bool Vector3<T>::operator!=(const Vector3<T> &rhs_) const noexcept {
        return x != rhs_.x
               && y != rhs_.y
               && z != rhs_.z;
    }

    template<typename T>
    Vector3<T> operator+(Vector3<T> lhs_, T rhs_) noexcept {
        lhs_ += rhs_;
        return lhs_;
    }

    template<typename T>
    Vector3<T> operator+(Vector3<T> lhs_, Vector3<T> rhs_) noexcept {
        lhs_ += rhs_;
        return lhs_;
    }

    template<typename T>
    Vector3<T> operator-(Vector3<T> lhs_, T rhs_) noexcept {
        return lhs_ -= rhs_;
    }

    template<typename T>
    Vector3<T> operator-(Vector3<T> lhs_, Vector3<T> rhs_) noexcept {
        return lhs_ -= rhs_;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &rhs_) noexcept {
        x *= rhs_.x;
        y *= rhs_.y;
        z *= rhs_.z;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator*=(T rhs_) noexcept {
        x *= rhs_;
        y *= rhs_;
        z *= rhs_;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator/=(const Vector3<T> &rhs_) noexcept {
        x /= rhs_.x;
        y /= rhs_.y;
        z /= rhs_.z;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator/=(T rhs_) noexcept {
        x /= rhs_;
        y /= rhs_;
        z /= rhs_;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &rhs_) noexcept {
        x += rhs_.x;
        y += rhs_.y;
        z += rhs_.z;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator+=(T rhs_) noexcept {
        x += rhs_;
        y += rhs_;
        z += rhs_;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator-=(T rhs_) noexcept {
        x -= rhs_;
        y -= rhs_;
        z -= rhs_;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &rhs_) noexcept {
        x -= rhs_.x;
        y -= rhs_.y;
        z -= rhs_.z;
        return *this;
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator=(T rhs_) noexcept {
        x = rhs_;
        y = rhs_;
        z = rhs_;
        return *this;
    }

#pragma endregion Operators
}
#endif
