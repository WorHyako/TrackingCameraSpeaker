#ifndef TRACKINGCAMERASPEAKER_CAMERADATA_HPP
#define TRACKINGCAMERASPEAKER_CAMERADATA_HPP

#include "vector/Vector3.hpp"

namespace worTCS {

    /**
     * Store camera values and methods to data operations
     */
    struct CameraData {
    public:
        Vector3<float> rotation;
        Vector3<float> position;
        int zoom, focus;
        bool useFracture;
        bool empty;

        explicit CameraData(float jointValue_ = -1.0f) noexcept;

#pragma region Operators

        bool operator==(const CameraData &rhs_) const noexcept;

        bool operator!=(const CameraData &rhs_) const noexcept;

        friend CameraData operator-(CameraData lhs_, float rhs_) noexcept;

        friend CameraData operator-(CameraData lhs_, CameraData rhs_) noexcept;

        friend CameraData operator+(CameraData lhs_, CameraData rhs_) noexcept;

        friend CameraData operator+(CameraData lhs_, float rhs_) noexcept;

        friend CameraData operator*(CameraData lhs_, CameraData rhs_) noexcept;

        friend CameraData operator*(CameraData lhs_, float rhs_) noexcept;

        friend CameraData operator/(CameraData lhs_, CameraData rhs_) noexcept;

        friend CameraData operator/(CameraData lhs_, float rhs_) noexcept;

        CameraData absCameraData() noexcept;

#pragma endregion Operators
    };
}
#endif
