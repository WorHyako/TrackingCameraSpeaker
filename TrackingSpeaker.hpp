#ifndef TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_HPP
#define TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_HPP

#include "ServerUdpSocket.hpp"
#include "FreedPacket.hpp"

#include <thread>

namespace worCameraTracking {

    /**
     * Class providing receiving UDP messages (protocol FreeD) from socket
     * and convert it to camera x, y, z, rx, ry, rz, zoom, focus
     * Run two threads inside: receive packet and parse it to camera data
     * The main purpose is to manage connection between @b'_freedPacket' and @b'_server'
     */
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
        /**
         * Wait notify from @b'_server' and copy buffer's data to parse by @b'_freedPacket'
         * Recommended run to other thread/task
         */
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
