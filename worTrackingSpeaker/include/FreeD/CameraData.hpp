#ifndef TRACKINGCAMERASPEAKER_CAMERADATA_HPP
#define TRACKINGCAMERASPEAKER_CAMERADATA_HPP

namespace worCameraTracking {

    class CameraData {
    public:
        float _rz, _ry, _rx;
        float _x, _y, _z;
        int _zoom, _focus;
        bool _useFracture;
        bool _empty;

        explicit CameraData(int jointValue_ = -1);

        bool operator==(const CameraData &b_) const;

        bool operator!=(const CameraData &b_) const;

        bool operator<(const CameraData &b_) const;

        bool operator>(const CameraData &b_) const;

        CameraData operator-(const CameraData &b_) const;

        CameraData operator-(const float &b_) const;

        CameraData operator+(const CameraData &b_) const;

        CameraData operator+(const float &b_) const;

        CameraData operator*(const CameraData &b_) const;

        CameraData operator*(const float &b_) const;

        CameraData operator/(const CameraData &b_) const;

        CameraData operator/(const float &b_) const;

        CameraData absCameraData();
    };
}
#endif
