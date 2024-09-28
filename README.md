# TrackingCameraSpeaker

### by Worshiper Hyakki Yakō(worHyako)

Library to to work UDP packet (FreeD protocol) from local network and convert it to camera parameters:
position, rotation and lens value.

---

## Platforms

- Windows (MSVC)
- macOS

---

## Dependencies

- WorLibrary [v0.7](https://github.com/WorHyako/WorLibrary/tree/5ef43c0)
  - Network
  - Log
  - Math

---

## Usage sample

[Example file](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/TCS_UserExample.cpp) contains simple
code to use worTCS.

---

### Basic usage

```c++
#include "Wor/Network/Utils/IoService.hpp"
#include "speaker/TrackingCameraSpeaker.hpp"

int main() {
	constexpr std::string_view targetAddress = "127.0.0.1";
	constexpr std::uint16_t targetPort = 6001;
	
	WorTCS::TrackingCameraSpeaker reader;
	if (!reader.startSpeaker(targetAddress, targetPort)) {
		/// Error
		...
	}
	
	Network::Utils::IoService::run();

	Wor::Math::Vector::Vector3<float> position = reader.position();
	Wor::Math::Vector::Vector3<float> rotation = reader.rotation();
	int zoom = reader.zoom();
	int focus = reader.focus();
	
	return 0;
}
```

---

### Accessing to raw buffer
```c++
#include "Wor/Network/Utils/IoService.hpp"
#include "speaker/TrackingCameraSpeaker.hpp"

int main() {
	constexpr std::string_view targetAddress{"127.0.0.1"};
	constexpr std::uint16_t targetPort{6001};
	
	WorTCS::TrackingCameraSpeaker reader;
	if (!reader.startSpeaker(targetAddress, targetPort)) {
		/// Error
		...
	}
	
	Network::Utils::IoService::run();
	
	std::array<std::byte, WorTCS::FreeDPacket::length> buffer{reader.rawBuffer()}; 
	
	return 0;
}
```

---

### Debug/string view
```c++
#include "Wor/Network/Utils/IoService.hpp"
#include "speaker/TrackingCameraSpeaker.hpp"

int main() {
	constexpr std::string_view targetAddress{"127.0.0.1"};
	constexpr std::uint16_t targetPort{6001};
	
	WorTCS::TrackingCameraSpeaker reader;
	if (!reader.startSpeaker(targetAddress, targetPort)) {
		/// Error
		...
	}
	
	Network::Utils::IoService::run();
	
	std::string str{reader.str(WorTCS::FreeDPacket::StrView::Rot
					    | WorTCS::FreeDPacket::StrView::Pos
						| WorTCS::FreeDPacket::StrView::Lens);
	/// str -> 
	/// Position:
	///     x: ...
	///     y: ...
	///     z: ...
	/// Rotation:
	///     rx: ...
	///     ry: ...
	///     rz: ...
	/// Lens:
	///     focus: ...
	///     zoom: ...
	return 0;
}
```
