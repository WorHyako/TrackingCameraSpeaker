#pragma once

#include "freeD/CameraData.hpp"
#include "freeD/PartialBuffer.hpp"

namespace WorTCS {
	/**
	 * @brief	Class to convert received packet to camera data and store result.
	 *
	 * @usage
	 * @code
	 *			FreedPacket parser;
	 *			parser.packetToData(dataArray);
	 * @endcode
	 *
	 * @author  WorHyako
	 *
	 * @see		@code PartialBuffer @endcode
	 */
	class FreeDPacket final {
	public:
		/**
		 * @brief	FreeD protocol packet length.
		 */
		static constexpr std::uint8_t length = 29;

		/**
		 * @brief	Represents flag to @code FreeDPacket @endcode string representation.
		 *
		 * @usage
		 * @code
		 *			auto strView = StrView::Pos
		 *							| StrView::Rot;
		 * @endcode
		 *
		 * @author	WorHyako
		 */
		enum class StrView
				: std::uint8_t {
			/**
			 * @brief	Show lens data.
			 */
			Lens = 0b1,
			/**
			 * @brief	Show position data.
			 */
			Pos = 0b01,
			/**
			 * @brief	Show rotation data.
			 */
			Rot = 0b001
		};

		/**
		 * @brief	Ctor.
		 */
		FreeDPacket() noexcept = default;

		/**
		 * @brief	Parses packet to data: x, y, z, rx, ry, rz, zoom, focus.
		 *			<p>
		 *			Uses PartialBuffer to repair broken packet.
		 *			<p>
		 *			Fold data (in future).
		 *
		 * @param	data Packet to parse.
		 *
		 * @see		@code PartialBuffer @endcode
		 */
		void packetToData(const std::array<std::byte, length>& data);

	private:
		/**
		 * @brief	Actual camera data from remote device.
		 */
		CameraData _cameraData;

		/**
		 * @brief	Partial buffer helps to repair packet when packets start to have offset.
		 */
		PartialBuffer _partialBuffer;

		/**
		 * @brief	Parses selected bytes pack to calculate device rotation angle.
		 *
		 * @param	a The first byte.
		 *
		 * @param	b The second byte.
		 *
		 * @param	c The third byte.
		 *
		 * @return	Calculated rotation angle.
		 */
		[[nodiscard]]
		float bytesToAngles(std::byte a, std::byte b, std::byte c) const noexcept;

		/**
		 * @brief	Parses selected bytes pack to calculate device position.
		 *
		 * @param	a The first byte.
		 *
		 * @param	b The second byte.
		 *
		 * @param	c The third byte.
		 *
		 * @return	Calculated position.
		 */
		[[nodiscard]]
		float bytesToLocation(std::byte a, std::byte b, std::byte c) const noexcept;

		/**
		 * @brief	Parses selected bytes pack to calculate device lens.
		 *
		 * @param	a The first byte.
		 *
		 * @param	b The second byte.
		 *
		 * @param	c The third byte.
		 *
		 * @return	Calculated lens.
		 */
		[[nodiscard]]
		int bytesToLens(std::byte a, std::byte b, std::byte c) const noexcept;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief   Camera data accessor.
		 *
		 * @return  Camera data.
		 *
		 * @see     @code CameraData @endcode.
		 */
		[[nodiscard]]
		const CameraData& cameraData() const noexcept;

		/**
		 * @brief	Use fracture accessor.
		 *
		 * @return	Use fracture.
		 */
		[[nodiscard]]
		bool useFracture() const noexcept;

		/**
		 * @brief	Use fracture mutator.
		 *
		 * @param	fracture Use fracture.
		 */
		void useFracture(bool fracture) noexcept;

		/**
		 * @brief	Raw buffer accessor from @code PartialBuffer @endcode.
		 *
		 * @return	Raw buffer.
		 */
		[[nodiscard]]
		const std::array<std::byte, FreeDPacket::length>& rawBuffer() const noexcept;

		/**
		 * @brief	Returns camera data via string.
		 *
		 * @param	strViewFlag	String view flag to fill returning string.
		 */
		[[nodiscard]]
		std::string str(StrView strViewFlag) const noexcept;

#pragma endregion Accessors/Mutators
	};

	/**
	 * @brief	Operator
	 *
	 * @param	lhs	Left hand side object.
	 *
	 * @param	rhs	Right hand side object.
	 *
	 * @return
	 *
	 * @author	WorHyako
	 */
	[[nodiscard]]
	FreeDPacket::StrView operator|(FreeDPacket::StrView lhs, FreeDPacket::StrView rhs) noexcept;

	/**
	 * @brief
	 *
	 * @param	lhs	Left hand side object.
	 *
	 * @param	rhs Right hand side object.
	 *
	 * @return
	 *
	 * @author	WorHyako
	 */
	[[nodiscard]]
	bool operator&(FreeDPacket::StrView lhs, FreeDPacket::StrView rhs) noexcept;
}
