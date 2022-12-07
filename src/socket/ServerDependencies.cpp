#include "socket/ServerDependencies.hpp"

using namespace worTCS;

PointInfo::PointInfo() noexcept {
    localIp = "";
    localPort = -1;
    destinationIp = "";
    destinationPort = -1;
}

PointInfo::PointInfo(const std::string &localIp_, int16_t localPort_,
                     const std::string &destinationIp_, int16_t destinationPort_) noexcept {
    localIp = localIp_;
    localPort = localPort_;
    destinationIp = destinationIp_;
    destinationPort = destinationPort_;
}
