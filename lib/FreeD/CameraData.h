#ifndef TRACKINGCAMERASPEAKER_CAMERADATA_H
#define TRACKINGCAMERASPEAKER_CAMERADATA_H

namespace worLib {

    class CameraData {
    public:
        float rz_, ry_, rx_;
        float x_, y_, z_;
        int zoom_, focus_;
        bool use_fracture_;
        bool empty_;

        explicit CameraData(int joint_value = -1);

        bool operator==(const CameraData &b) const {
            return (rz_ == b.rz_
                    && ry_ == b.ry_
                    && rx_ == b.rx_
                    && x_ == b.x_
                    && y_ == b.y_
                    && z_ == b.z_
                    && zoom_ == b.zoom_
                    && focus_ == b.focus_);
        }

        bool operator!=(const CameraData &b) const {
            return (rz_ != b.rz_
                    && ry_ != b.ry_
                    && rx_ != b.rx_
                    && x_ != b.x_
                    && y_ != b.y_
                    && z_ != b.z_
                    && zoom_ != b.zoom_
                    && focus_ != b.focus_);
        }

        bool operator<(const CameraData &b) const {
            return (rz_ < b.rz_
                    && ry_ < b.ry_
                    && rx_ < b.rx_
                    && x_ < b.x_
                    && y_ < b.y_
                    && z_ < b.z_
                    && zoom_ < b.zoom_
                    && focus_ < b.focus_);
        }

        bool operator>(const CameraData &b) const {
            return (rz_ > b.rz_
                    && ry_ > b.ry_
                    && rx_ > b.rx_
                    && x_ > b.x_
                    && y_ > b.y_
                    && z_ > b.z_
                    && zoom_ > b.zoom_
                    && focus_ > b.focus_);
        }

        CameraData operator-(const CameraData &b) const {
            CameraData c;
            c.rz_ = rz_ - b.rz_;
            c.ry_ = ry_ - b.ry_;
            c.rx_ = rx_ - b.rx_;
            c.x_ = x_ - b.x_;
            c.y_ = y_ - b.y_;
            c.z_ = z_ - b.z_;
            c.zoom_ = zoom_ - b.zoom_;
            c.focus_ = focus_ - b.focus_;
            return c;
        }

        CameraData operator-(const float &b) const {
            CameraData c;
            c.rz_ = rz_ - b;
            c.ry_ = ry_ - b;
            c.rx_ = rx_ - b;
            c.x_ = x_ - b;
            c.y_ = y_ - b;
            c.z_ = z_ - b;
            c.zoom_ = zoom_ - static_cast<int>(b);
            c.focus_ = focus_ - static_cast<int>(b);
            return c;
        }

        CameraData operator+(const CameraData &b) const {
            CameraData c;
            c.rz_ = rz_ + b.rz_;
            c.ry_ = ry_ + b.ry_;
            c.rx_ = rx_ + b.rx_;
            c.x_ = x_ + b.x_;
            c.y_ = y_ + b.y_;
            c.z_ = z_ + b.z_;
            c.zoom_ = zoom_ + b.zoom_;
            c.focus_ = focus_ + b.focus_;
            return c;
        }

        CameraData operator+(const float &b) const {
            CameraData c;
            c.rz_ = rz_ + b;
            c.ry_ = ry_ + b;
            c.rx_ = rx_ + b;
            c.x_ = x_ + b;
            c.y_ = y_ + b;
            c.z_ = z_ + b;
            c.zoom_ = zoom_ + static_cast<int>(b);
            c.focus_ = focus_ + static_cast<int>(b);
            return c;
        }

        CameraData operator*(const CameraData &b) const {
            CameraData c;
            c.rz_ = rz_ * b.rz_;
            c.ry_ = ry_ * b.ry_;
            c.rx_ = rx_ * b.rx_;
            c.x_ = x_ * b.x_;
            c.y_ = y_ * b.y_;
            c.z_ = z_ * b.z_;
            c.zoom_ = zoom_ * b.zoom_;
            c.focus_ = focus_ * b.focus_;
            return c;
        }

        CameraData operator*(const float &b) const {
            CameraData c;
            c.rz_ = rz_ * b;
            c.ry_ = ry_ * b;
            c.rx_ = rx_ * b;
            c.x_ = x_ * b;
            c.y_ = y_ * b;
            c.z_ = z_ * b;
            c.zoom_ = zoom_ * static_cast<int>(b);
            c.focus_ = focus_ * static_cast<int>(b);
            return c;
        }

        CameraData operator/(const CameraData &b) const {
            CameraData c;
            c.rz_ = rz_ / b.rz_;
            c.ry_ = ry_ / b.ry_;
            c.rx_ = rx_ / b.rx_;
            c.x_ = x_ / b.x_;
            c.y_ = y_ / b.y_;
            c.z_ = z_ / b.z_;
            c.zoom_ = zoom_ / b.zoom_;
            c.focus_ = focus_ / b.focus_;
            return c;
        }

        CameraData operator/(const float &b) const {
            CameraData c;
            c.rz_ = rz_ / b;
            c.ry_ = ry_ / b;
            c.rx_ = rx_ / b;
            c.x_ = x_ / b;
            c.y_ = y_ / b;
            c.z_ = z_ / b;
            c.zoom_ = zoom_ / static_cast<int>(b);
            c.focus_ = focus_ / static_cast<int>(b);
            return c;
        }

        CameraData absCameraData();

    };
}
#endif
