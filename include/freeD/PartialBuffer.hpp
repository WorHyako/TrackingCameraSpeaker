#pragma once

#include <array>
#include <string>

namespace WorTCS {
	/**
	 * @brief	Class to repair packet and fold data.
	 *
	 * @usage
	 * @code
	 *			PartialBuffer buffer;
	 *			buffer.tryToAppendNewData(data);
	 *			if (!(buffer.completed() && buffer.valid())) {
	 *				...
	 *			}
	 *			/// Ready to parse buffer.
	 * @endcode
	 *
	 * @author	WorHyako
	 */
	class PartialBuffer final {
	public:
		/**
		 * @brief	Partial buffer length.
		 *			<p>
		 *			It's equal with FreeD packet length.
		 */
		static constexpr std::size_t length{29};

		/**
		 * @brief	Ctor.
		 */
		PartialBuffer() noexcept;

		/**
		 * @brief	Tries to append new data to current and fixes if it needed.
		 *
		 * @param	new_data	New incoming packet.
		 */
		void tryToAppendNewData(const std::array<std::byte, length>& new_data);

		/**
		 * @brief	Validates checksum for packet.
		 *			<p>
		 *			Valid packet's checksum place in the last byte.
		 *
		 * @param	byte_array Packet to validate.
		 *
		 * @return	@code true @endcode		Valid packet.
		 *			<p>
		 *			@code false @endcode	Invalid packet.
		 */
		[[nodiscard]]
		bool checkChecksum(const std::array<std::byte, length>& byte_array) const;

	private:
		/**
		 * @brief	Packet to parse.
		 */
		std::array<std::byte, length> _packet;

		/**
		 * @brief	Packet's byte offset.
		 */
		int _delta_byte;

		/**
		 * @brief	Packet signalize.
		 */
		bool _packet_valid;

		/**
		 * @brief	Complete packet is packet which begins with 0xD1 symbol.
		 */
		bool _packet_complete;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief	Returns packet to parse.
		 *			<p>
		 *			Packet may be invalid and uncompleted.
		 *
		 * @return	Packet.
		 */
		[[nodiscard]]
		const std::array<std::byte, length>& packet() const noexcept;

		/**
		 * @brief	Validation is applying with checksum checking.
		 *
		 * @return	@code true @endcode		Packet is valid.
		 *			<p>
		 *			@code false @endcode	Packet is not valid.
		 */
		[[nodiscard]]
		bool valid() const noexcept;

		/**
		 * @brief	Check full packet to completed condition and signalize packet ready to parse.
		 *
		 * @return	@code true @endcode		Packet is completed.
		 *			<p>
		 *			@code false @endcode	Packet is not completed.
		 */
		[[nodiscard]]
		bool completed() const noexcept;

#pragma endregion Accessors/Mutators
	};
}
