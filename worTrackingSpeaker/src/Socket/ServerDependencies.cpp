#include "ServerDependencies.hpp"

using namespace worCameraTracking;

NetParameters::NetParameters() {
    _localIp = "";
    _localPort = -1;
    _destinationIp = "";
    _destinationPort = -1;
}

NetParameters::NetParameters(const std::string &localIp_, int16_t localPort_,
                             const std::string &destinationIp_, int16_t destinationPort_) {
    _localIp = localIp_;
    _localPort = localPort_;
    _destinationIp = destinationIp_;
    _destinationPort = destinationPort_;
}
