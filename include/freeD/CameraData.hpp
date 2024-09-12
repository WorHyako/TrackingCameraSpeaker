#pragma once

#include "Wor/Vector/Vector3.hpp"

namespace WorTCS {
	/**
	 * @brief	Store camera values and methods to data operations.
	 *			<p>
	 *			Validate this object via read @code empty @endcode field.
	 *
	 * @author	WorHyako
	 */
	struct CameraData final {
		/**
		 * @brief	Ctor.
		 */
		CameraData() noexcept;

		/**
		 * @brief	Camera rotation.
		 */
		Wor::Math::Vector::Vector3<float> rotation;

		/**
		 * @brief	Camera position.
		 */
		Wor::Math::Vector::Vector3<float> position;

		/**
		 * @brief	Camera zoom.
		 */
		int zoom;

		/**
		 * @brief	Camera focus.
		 */
		int focus;

		/**
		 * @brief	Use fracture for camera data.
		 */
		bool useFracture;

		/**
		 * @brief	Is object has been filled or has default values.
		 */
		bool empty;

		/**
		 * @brief	Returns abs copy of all fields.
		 *
		 * @return	Abs value.
		 */
		[[nodiscard]]
		CameraData absCameraData() const noexcept;

#pragma region Operators

		[[nodiscard]]
		bool operator==(const CameraData& rhs) const noexcept;

		[[nodiscard]]
		bool operator!=(const CameraData& rhs) const noexcept;

		friend CameraData operator-(CameraData lhs, float rhs) noexcept;

		friend CameraData operator-(CameraData lhs, CameraData rhs) noexcept;

		friend CameraData operator+(CameraData lhs, CameraData rhs) noexcept;

		friend CameraData operator+(CameraData lhs, float rhs) noexcept;

		friend CameraData operator*(CameraData lhs, CameraData rhs) noexcept;

		friend CameraData operator*(CameraData lhs, float rhs) noexcept;

		friend CameraData operator/(CameraData lhs, CameraData rhs) noexcept;

		friend CameraData operator/(CameraData lhs, float rhs) noexcept;

#pragma endregion Operators
	};
}
