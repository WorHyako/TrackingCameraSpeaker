#include "CameraData.h"
#include <cmath>

namespace worLib {

    CameraData::CameraData(int joint_value) {
        rz_ = static_cast<float>(joint_value);
        rx_ = static_cast<float>(joint_value);
        ry_ = static_cast<float>(joint_value);
        x_ = static_cast<float>(joint_value);
        y_ = static_cast<float>(joint_value);
        z_ = static_cast<float>(joint_value);
        focus_ = joint_value;
        zoom_ = joint_value;
        use_fracture_ = false;
        empty_ = true;
    }

    CameraData CameraData::absCameraData() {
        CameraData result;
        result.rz_ = std::abs(rz_);
        result.rx_ = std::abs(rx_);
        result.ry_ = std::abs(ry_);
        result.x_ = std::abs(x_);
        result.y_ = std::abs(y_);
        result.z_ = std::abs(z_);
        result.focus_ = std::abs(focus_);
        result.zoom_ = std::abs(zoom_);
        use_fracture_ = false;
        empty_ = true;
        return result;
    }
}