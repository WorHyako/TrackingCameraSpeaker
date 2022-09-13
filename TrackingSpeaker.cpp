#include "TrackingSpeaker.h"

using namespace worLib;

TrackingSpeaker::TrackingSpeaker() {
    _speakerActivity = false;
    _receivingThread = nullptr;
    _parsingThread = nullptr;
}

TrackingSpeaker::~TrackingSpeaker() {
    stopReader();
}

bool TrackingSpeaker::startReader(const std::string &localIp_, int16_t localPort_) {
    _speakerActivity = _server.openSocket(localIp_, localPort_);
    if (!_speakerActivity) {
        return false;
    }

    _receivingThread = new std::thread(&ServerUdpSocket::startReceivingData, _server);
    _parsingThread = new std::thread(&TrackingSpeaker::startParse, this);
    return true;
}

bool TrackingSpeaker::stopReader() {
    if (_speakerActivity) {
        _speakerActivity = false;
        _receivingThread->detach();
        _parsingThread->detach();
        delete _receivingThread;
        delete _parsingThread;
    }
    Sleep(1);
    return _server.closeSocket();
}

void TrackingSpeaker::startParse() {
    while (_speakerActivity) {
        std::vector<byte> dataVArray = _server.getDataInStlVector();
        if (dataVArray.empty()) {
            continue;
        }
        std::array<byte, FREED_PACKET_LENGTH> dataArray{};
        std::copy(dataVArray.begin(), dataVArray.end(), dataArray.begin());
        _freedPacket.parseData(dataArray);

        Sleep(1);
    }
}

std::ostream &worLib::operator<<(std::ostream &os_, const TrackingSpeaker &reader_) {
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

bool TrackingSpeaker::getServerActivity() const {
    return _server._activity;
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

#pragma endregion Accessors

#pragma region Mutators

void TrackingSpeaker::setOsFlag(FreeDPacket::CameraDataType flag_) {
    _freedPacket._streamFlag = flag_;
}

#pragma endregion Mutators
