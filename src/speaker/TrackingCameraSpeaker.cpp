#include "speaker/TrackingCameraSpeaker.hpp"

using namespace worTCS;

TrackingCameraSpeaker::TrackingCameraSpeaker() {
    _speakerActivity = false;
}

TrackingCameraSpeaker::~TrackingCameraSpeaker() {
    stopSpeaker();
}

bool TrackingCameraSpeaker::startSpeaker(const std::string &localIp_, int16_t localPort_) {
    bool localPointDestination = worTCS::ServerUdpSocket::checkEndPoint(localIp_);
    if (!localPointDestination) {
        return false;
    }
    PointInfo pointInfo = PointInfo(localIp_, localPort_);
    _server.setPointInfo(pointInfo);
    _speakerActivity = _server.openSocket();
    if (!_speakerActivity) {
        return false;
    }

    _receivingThread = std::thread(&ServerUdpSocket::receivePacket, std::ref(_server));
    _parsingThread = std::thread(&TrackingCameraSpeaker::parsePacket, std::ref(*this));
    return true;
}

bool TrackingCameraSpeaker::stopSpeaker() {
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

void TrackingCameraSpeaker::parsePacket() {
    auto waitServerTimeout = std::chrono::milliseconds(1);
    while (_speakerActivity) {
        std::vector<std::byte> dataVArray(FreeDPacket::freed_packet_length);
        {
            std::unique_lock<std::mutex> lock(_server._receivingMutex);
            _server._dataReceived.wait_for(lock, waitServerTimeout);
            dataVArray = _server.getPacket();
        }
        std::array<std::byte, FreeDPacket::freed_packet_length> dataArray{};
        std::copy(dataVArray.begin(), dataVArray.begin() + FreeDPacket::freed_packet_length, dataArray.begin());
        _freedPacket.packetToData(dataArray);
    }
}

#pragma region Accessors

const PointInfo &TrackingCameraSpeaker::getPointInfo() const noexcept {
    return _server.getPointInfo();
}

SocketState TrackingCameraSpeaker::getServerState() const noexcept {
    return _server.getSocketState();
}

bool TrackingCameraSpeaker::getSpeakerActivity() const noexcept {
    return _speakerActivity;
}

float TrackingCameraSpeaker::getRz() const noexcept {
    return _freedPacket.getRotation().z;
}

float TrackingCameraSpeaker::getRy() const noexcept {
    return _freedPacket.getRotation().y;
}

float TrackingCameraSpeaker::getRx() const noexcept {
    return _freedPacket.getRotation().x;
}

float TrackingCameraSpeaker::getX() const noexcept {
    return _freedPacket.getPosition().x;
}

float TrackingCameraSpeaker::getY() const noexcept {
    return _freedPacket.getPosition().y;
}

float TrackingCameraSpeaker::getZ() const noexcept {
    return _freedPacket.getPosition().z;
}

int TrackingCameraSpeaker::getZoom() const noexcept {
    return _freedPacket.getZoom();
}

int TrackingCameraSpeaker::getFocus() const noexcept {
    return _freedPacket.getFocus();
}

bool TrackingCameraSpeaker::getUseFracture() const noexcept {
    return _freedPacket.getUseFracture();
}

const std::vector<std::byte> &TrackingCameraSpeaker::getBuffer() const noexcept {
    return _server.getPacket();
}

Vector3<float> TrackingCameraSpeaker::getRotation() const noexcept {
    return _freedPacket.getRotation();
}

Vector3<float> TrackingCameraSpeaker::getPosition() const noexcept {
    return _freedPacket.getPosition();
}

#pragma endregion Accessors

#pragma region Mutators

void TrackingCameraSpeaker::setOsFlag(FreeDPacket::CameraDataType flag_) noexcept {
    _freedPacket._streamFlag = flag_;
}

#pragma endregion Mutators

#pragma region Operators

std::ostream &worTCS::operator<<(std::ostream &os_, const TrackingCameraSpeaker &reader_) {
    os_ << reader_._freedPacket;
    return os_;
}

void TrackingCameraSpeaker::setPacketLength(int packetLength_) noexcept {
    _server.setPacketLength(packetLength_);
}

#pragma region Operators