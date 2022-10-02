#include "TrackingSpeaker.hpp"

using namespace worCameraTracking;

TrackingSpeaker::TrackingSpeaker() {
    _speakerActivity = false;
}

TrackingSpeaker::~TrackingSpeaker() {
    stopSpeaker();
}

bool TrackingSpeaker::startSpeaker(const std::string &localIp_, int16_t localPort_) {
    _speakerActivity = _server.openSocket(localIp_, localPort_);
    if (!_speakerActivity) {
        return false;
    }

    _receivingThread = std::thread(&ServerUdpSocket::receivePacket, std::ref(_server));
    _parsingThread = std::thread(&TrackingSpeaker::parsePacket, std::ref(*this));
    return true;
}

bool TrackingSpeaker::stopSpeaker() {
    if (!_speakerActivity) {
        return false;
    }
    _speakerActivity = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    auto closeSocketResult = _server.closeSocket();
    if (_receivingThread.joinable()) {
        _receivingThread.join();
    }

    if (_parsingThread.joinable()) {
        _parsingThread.join();
    }
    return closeSocketResult;
}

void TrackingSpeaker::parsePacket() {
    auto waitServerTimeout = std::chrono::milliseconds(10);
    while (_speakerActivity) {
        std::vector<byte> dataVArray;
        {
            std::unique_lock<std::mutex> lock(_server._receivingMutex);
            _server._dataReceived.wait_for(lock, waitServerTimeout);
            dataVArray = _server.getBuffer();
        }
        if (dataVArray.empty()) {
            continue;
        }
        std::array<byte, FREED_PACKET_LENGTH> dataArray{};
        std::copy(dataVArray.begin(), dataVArray.end(), dataArray.begin());
        _freedPacket.packetToData(dataArray);
    }
}

std::ostream &worCameraTracking::operator<<(std::ostream &os_, const TrackingSpeaker &reader_) {
    os_ << reader_._freedPacket;
    return os_;
}

#pragma region Accessors

std::string TrackingSpeaker::getLocalIp() const {
    return _server.getNetParameters()._localIp;
}

short int TrackingSpeaker::getLocalPort() const {
    return _server.getNetParameters()._localPort;
}

SocketState TrackingSpeaker::getServerState() const {
    return _server.getSocketState();
}

bool TrackingSpeaker::getSpeakerActivity() const {
    return _speakerActivity;
}

float TrackingSpeaker::getRz() const {
    return _freedPacket.getRz();
}

float TrackingSpeaker::getRy() const {
    return _freedPacket.getRy();
}

float TrackingSpeaker::getRx() const {
    return _freedPacket.getRx();
}

float TrackingSpeaker::getX() const {
    return _freedPacket.getX();
}

float TrackingSpeaker::getY() const {
    return _freedPacket.getY();
}

float TrackingSpeaker::getZ() const {
    return _freedPacket.getZ();
}

int TrackingSpeaker::getZoom() const {
    return _freedPacket.getZoom();
}

int TrackingSpeaker::getFocus() const {
    return _freedPacket.getFocus();
}

bool TrackingSpeaker::getUseFracture() const {
    return _freedPacket.getUseFracture();
}

const std::vector<byte> &TrackingSpeaker::getBuffer() const {
    return _server.getBuffer();
}

#pragma endregion Accessors

#pragma region Mutators

void TrackingSpeaker::setOsFlag(FreeDPacket::CameraDataType flag_) {
    _freedPacket._streamFlag = flag_;
}


#pragma endregion Mutators
