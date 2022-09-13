#ifndef TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_H
#define TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_H

#include "lib/Socket/ServerUdpSocket.hpp"
#include "lib/FreeD/FreedPacket.hpp"

#include <thread>

namespace worLib {

    class TrackingSpeaker {
    public:
        TrackingSpeaker();

        ~TrackingSpeaker();

        friend std::ostream &operator<<(std::ostream &os_, const TrackingSpeaker &reader_);

    private:
        FreeDPacket _freedPacket;
        ServerUdpSocket _server;

        std::thread *_receivingThread;
        std::thread *_parsingThread;

        bool _speakerActivity;

        void startParse();

    public:
        bool startReader(const std::string &localIp_, int16_t localPort_);

        bool stopReader();

#pragma region Accessors

        std::string getLocalIp() const;

        short int getLocalPort() const;

        bool getServerActivity() const;

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

#pragma endregion Accessors

#pragma region Mutators

        void setOsFlag(FreeDPacket::CameraDataType flag_);

#pragma endregion Mutators
    };
}
#endif
