#ifndef TRACKINGCAMERASPEAKER_BASESOCKET_HPP
#define TRACKINGCAMERASPEAKER_BASESOCKET_HPP

#include "socket/SocketInfo.hpp"

#include <mutex>
#include <condition_variable>

#include <winsock2.h>

namespace worTCS {

    /**
     * Base abstract class to socket management\n
     * Provide mutex @b'_receivingMutex' and condition_variable @b'_dataReceived', base WinAPI fields to create
     * UDP or TCP full management classes
     */
    class BaseSocket {
    public:
        explicit BaseSocket(const PointInfo &pointInfo_) noexcept;

        virtual ~BaseSocket() = default;

        /// Condition variable in charge of @b'packet'. Notify then data received
        std::condition_variable _dataReceived;

        /// Mutex in charge of @b'packet'. Locked while the data is receiving
        std::mutex _receivingMutex;

        [[nodiscard]] virtual bool openSocket() = 0;

        [[nodiscard]] virtual bool closeSocket() = 0;

        /**
         * Check connection to destination IP
         * @param destinationIp_ destination IP to ping
         * @return successful connection
         */
        [[nodiscard]] static bool checkEndPoint(const std::string &destinationIp_) noexcept;

    protected:
        /// Contain socket parameters such as ip, mutex and buffer
        SocketInfo _socketInfo;

    public:
#pragma region Accessors

        [[nodiscard]] const PointInfo& getPointInfo() const noexcept;

        [[nodiscard]] const std::vector<std::byte> &getPacket() const noexcept;

        [[nodiscard]] SocketState getSocketState() const noexcept;

        [[nodiscard]] int getSocketFps() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

        void setPointInfo(const PointInfo& pointInfo_) noexcept;

        void setPacketLength(int length_) noexcept;

        void setSocketFps(int fps_) noexcept;

#pragma endregion Mutators
    };
}
#endif
