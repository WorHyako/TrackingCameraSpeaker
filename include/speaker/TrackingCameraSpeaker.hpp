#pragma once

#include "freeD/FreedPacket.hpp"

#include "Wor/Vector/Vector3.hpp"
#include "Wor/Network/TcpServer.hpp"

#include <memory>

namespace WorTCS {
	/**
	 * @brief	Class provides receiving UDP messages (protocol freeD) from socket
	 *			and convert it to camera position, rotation, zoom, focus.
	 *			<p>
	 *			Run two threads inside: receive packet and parse it to camera data
	 *			The main purpose is to manage connection between @b'_freedPacket' and @b'_server'
	 *			<p>
	 *			God object.
	 *
	 * @usage
	 * @code
	 * @endcode
	 *
	 * @author	WorHyako
	 *
	 * @see		@code FreedPacket @endcode
	 * @see		@code Wor::Network::TcpServer @endcode
	 */
	class TrackingCameraSpeaker final {
	public:
		/**
		 * @brief  Ctor.
		 */
		TrackingCameraSpeaker() noexcept = default;

		/**
		 * @brief	Dtor.
		 */
		~TrackingCameraSpeaker() noexcept;

		/**
		 * @brief	Tries to open socket and run two thread to listen port and parse packet to data.
		 *
		 * @param	address		Local ip address to lister.
		 *
		 * @param	port		Local port to listen.
		 *
		 * @return	@code true @endcode		Started successfully.
		 *			<p>
		 *			@code false @endcode	Error in start speaker.
		 */
		bool startSpeaker(const std::string& address, std::uint16_t port) noexcept;

		/**
		 * @brief	Closes socket and join all threads.
		 */
		void stopSpeaker() noexcept;

	private:
		/**
		 * @brief	Field for parsing and operations with FreeD packets.
		 */
		FreeDPacket _freedPacket;

		/**
		 * @brief	Server to receive incoming packets.
		 */
		std::unique_ptr<Wor::Network::TcpServer> _server;

		/**
		 * @brief	Parses incoming message via FreeD protocol.
		 *			<p>
		 *			Recommend to use as callback on receive message from @code TcpServer @endcode.
		 */
		void parsePacket(const std::string& message) noexcept;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Raw buffer accessor from @code FreedPacket @endcode.
		 *
		 * @return	Raw buffer.
		 */
		[[nodiscard]]
		const std::array<std::byte, FreeDPacket::length>& rawBuffer() const noexcept;

		/**
		 * @brief	Remote device endpoint accessor.
		 *
		 * @return	Endpoint.
		 *			<p>
		 *			Empty endpoint if there is no active sessions.
		 */
		[[nodiscard]]
		boost::asio::ip::tcp::endpoint endPoint() const noexcept;

		/**
		 * @brief	Current speaker activity accessor.
		 *
		 * @return	@code true @endcode		Speaker is running.
		 *			<p>
		 *			@code false @endcode	Speaker is not running.
		 */
		[[nodiscard]]
		bool speakerActivity() const noexcept;

		/**
		 * @brief	Position accessor.
		 *
		 * @return	Device position.
		 */
		[[nodiscard]]
		const Wor::Math::Vector::Vector3<float>& position() const noexcept;

		/**
		 * @brief	Rotation accessor.
		 *
		 * @return	Device rotation.
		 */
		[[nodiscard]]
		const Wor::Math::Vector::Vector3<float>& rotation() const noexcept;

		/**
		 * @brief	Camera zoom accessor.
		 *
		 * @return	Zoom value.
		 */
		[[nodiscard]]
		int zoom() const noexcept;

		/**
		 * @brief	Camera focus accessor.
		 *
		 * @return	Focus value.
		 */
		[[nodiscard]]
		int focus() const noexcept;

		/**
		 * @brief	TODO: fill it
		 *
		 * @return	Use fracture
		 */
		[[nodiscard]]
		bool useFracture() const noexcept;

		/**
		 * @brief	Returns camera data via string.
		 *
		 * @param	strViewFlag	String view flag to fill returning string.
		 *
		 * @return	Camera data string representation.
		 */
		[[nodiscard]]
		std::string str(FreeDPacket::StrView strViewFlag) const noexcept;

#pragma endregion Accessors/Mutators
	};
}
