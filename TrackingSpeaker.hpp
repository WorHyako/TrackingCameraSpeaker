#ifndef TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_HPP
#define TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_HPP

#include "ServerUdpSocket.hpp"
#include "FreedPacket.hpp"

#include <thread>

namespace worCameraTracking {

    class TrackingSpeaker {
    public:
        TrackingSpeaker();

        ~TrackingSpeaker();

        friend std::ostream &operator<<(std::ostream &os_, const TrackingSpeaker &reader_);

    private:
        FreeDPacket _freedPacket;
        ServerUdpSocket _server;

        std::thread _receivingThread;
        std::thread _parsingThread;

        bool _speakerActivity;

    public:
        bool startSpeaker(const std::string &localIp_, int16_t localPort_);

        bool stopSpeaker();

    private:
        void parsePacket();

    public:
#pragma region Accessors

        std::string getLocalIp() const;

        short int getLocalPort() const;

        SocketState getServerState() const;

        bool getSpeakerActivity() const;

        float getRz() const;

        float getRy() const;

        float getRx() const;

        float getX() const;

        float getY() const;

        float getZ() const;

        int getZoom() const;

        int getFocus() const;

        bool getUseFracture() const;

        const std::vector<byte> &getBuffer() const;

#pragma endregion Accessors

#pragma region Mutators

        void setOsFlag(FreeDPacket::CameraDataType flag_);

#pragma endregion Mutators
    };
}
#endif
