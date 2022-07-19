#ifndef TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_H
#define TRACKINGCAMERASPEAKER_TRACKINGSPEAKER_H

#include "lib/Socket/ServerUdpSocket.h"
#include "lib/FreeD/FreedPacket.h"

#include <thread>

namespace worLib {

    class TrackingSpeaker {
    public:
        TrackingSpeaker();

        ~TrackingSpeaker();

        friend std::ostream &operator<<(std::ostream &os, const TrackingSpeaker &reader);

    private:
        FreeDPacket freed_packet_;

        ServerUdpSocket server_;

        std::thread *receiving_thread_;

        std::thread *parsing_thread_;

        bool speaker_activity_;

        void startParse();
    public:
        bool startReader(const std::string& local_ip, int16_t local_port);

        bool stopReader();

        std::string getLocalIp() const { return server_.getNetParameters().local_ip_; }

        short int getLocalPort() const { return server_.getNetParameters().local_port_; }

        bool getServerActivity() const { return server_.activity_; }

        bool getSpeakerActivity() const { return speaker_activity_; }

        float getRz() const { return freed_packet_.getRz(); }

        float getRy() const { return freed_packet_.getRy(); }

        float getRx() const { return freed_packet_.getRx(); }

        float getX() const { return freed_packet_.getX(); }

        float getY() const { return freed_packet_.getY(); }

        float getZ() const { return freed_packet_.getZ(); }

        int getZoom() const { return freed_packet_.getZoom(); }

        int getFocus() const { return freed_packet_.getFocus(); }

        bool getUseFracture() const { return freed_packet_.getUseFracture(); }

        void setOsFlag(FreeDPacket::camera_data_type flag) { freed_packet_.os_flag_ = flag; }
    };
}
#endif