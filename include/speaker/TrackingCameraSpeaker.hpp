#ifndef TRACKINGCAMERASPEAKER_TRACKINGCAMERASPEAKER_HPP
#define TRACKINGCAMERASPEAKER_TRACKINGCAMERASPEAKER_HPP

#include "socket/ServerUdpSocket.hpp"
#include "freeD/FreedPacket.hpp"

#include <thread>

namespace worTCS {

    /**
     * Class providing receiving UDP messages (protocol freeD) from socket
     * and convert it to camera x, y, z, rx, ry, rz, zoom, focus
     * Run two threads inside: receive packet and parse it to camera data
     * The main purpose is to manage connection between @b'_freedPacket' and @b'_server'
     */
    class TrackingCameraSpeaker {
    public:
        TrackingCameraSpeaker();

        ~TrackingCameraSpeaker();

        /**
         * Try to open socket and run two thread to listen port and parse packet to data
         * @param localIp_ local ip to lister
         * @param localPort_ local port to listen
         * @return successful open socket
         */
        bool startSpeaker(const std::string &localIp_, int16_t localPort_);

        /**
         * Close socket and join all threads
         * @return false if nothing to stop (already stopped)
         */
        bool stopSpeaker();

    private:
        FreeDPacket _freedPacket;
        ServerUdpSocket _server;

        std::thread _receivingThread;
        std::thread _parsingThread;

        bool _speakerActivity;

        /**
         * Wait notify from @b'_server' and copy buffer's data to parse by @b'_freedPacket'
         * Recommended run to other thread/task
         */
        void parsePacket();

    public:
#pragma region Accessors

        [[nodiscard]] const PointInfo &getPointInfo() const noexcept;

        [[nodiscard]] SocketState getServerState() const noexcept;

        [[nodiscard]] bool getSpeakerActivity() const noexcept;

        [[nodiscard]] float getRz() const noexcept;

        [[nodiscard]] Vector3<float> getPosition() const noexcept;

        [[nodiscard]] Vector3<float> getRotation() const noexcept;

        [[nodiscard]] float getRy() const noexcept;

        [[nodiscard]] float getRx() const noexcept;

        [[nodiscard]] float getX() const noexcept;

        [[nodiscard]] float getY() const noexcept;

        [[nodiscard]] float getZ() const noexcept;

        [[nodiscard]] int getZoom() const noexcept;

        [[nodiscard]] int getFocus() const noexcept;

        [[nodiscard]] bool getUseFracture() const noexcept;

        [[nodiscard]] const std::vector<std::byte> &getBuffer() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

        void setOsFlag(FreeDPacket::CameraDataType flag_) noexcept;

#pragma endregion Mutators

#pragma region Operators

        friend std::ostream &operator<<(std::ostream &os_, const TrackingCameraSpeaker &reader_);

#pragma region Operators
    };
}
#endif
