# TrackingCameraSpeaker

#### by Worshiper Hyakki Yakō(worHyako)

This repo is designed to accept UDP packet (FreeD protocol) from local network and convert it to camera parameters:
position, rotation and lens value.

[Using example file](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/TCS_UserExample.cpp) contains simple 
code to use worTCS

---
## Classes:

### [TrackingCameraSpeaker](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/speaker/TrackingCameraSpeaker.hpp)

> This is your Speaker constructed as divine class-manager. Enjoy it.

public:

* ``` 
  bool TrackingCameraSpeaker::startSpeaker(const std::string& localIp_, int16_t localPort_) 
  ```
  Open socket if possible and start receiving and parsing threads
* ```
  void TrackingCameraSpeaker::setPacketLength(int packetLength_) 
  ```
  Set buffer length to read incoming packet. FreeD protocol has 29-length packets, but Udp server has 256-length buffer
  than default. Don't forget configure to 29, if u use usual FreeD format.
* ```
  SocketState TrackingCameraSpeaker::getServerState() 
  ```
  Remember check socket state due starting
* ```
  const Vector3<float>& TrackingCameraSpeaker::getPosition()
  const Vector3<float>& TrackingCameraSpeaker::getRotation()
  ```
  Getters for camera parameters and position. See in Accessors region in code.

* ``` 
  bool stopSpeaker() 
  ```
  Shutdown speaker. Stop threads and close socket.

private:

* ``` 
  void TrackingCameraSpeaker::parsePacket()
  ```
  Endless func used by Speaker's thread, that controls by _speakerActivity. Unfortunately nothing interesting

---

### [FreedPacket](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/freeD/FreedPacket.hpp)

> Contains information about the package and methods for data parsing

public:

* ``` 
  std::string FreeDPacket::getRotationViaString()
  ``` 
  In addition to the above getters we have getters via string
* ``` 
  void FreeDPacket::packetToData(std::array<unsigned char, freed_packet_length> data_)
  ```
  Method for parsing a packet in write data to _cameraData field

private:

* ``` 
  float FreeDPacket::bytesToAngles(const std::byte &a_, const std::byte &b_, const std::byte &c_)
  ```
  Float/int Angle/Location/Lens methods to calculate data from packet

---

### [CameraData](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/freeD/CameraData.hpp)

### [Vector](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/vector/Vector.hpp)

### [Vector3](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/vector/Vector3.hpp) : Vector

> Just for easy data manipulation

* Literally just a set of operators, I swear

---

### [PartialBuffer](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/freeD/PartialBuffer.hpp)

> Temp place (buffer) to packet repairing

public:

* ```
  void PartialBuffer::tryToAppendNewData(const std::array<std::byte, partial_buffer_length> &newData_)
  ```
  Packet integrity check and calculation info for repairing if it's need
* ```
  bool PartialBuffer::checkChecksum(const std::array<std::byte, partial_buffer_length> &byteArray_)
  ```
  Check checksum in packet(tautology, but it's true)

---

### [ServerUdpSocket](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/socket/ServerUdpSocket.hpp) : BaseSocket

> Main class to accept packets

Not so interesting. Just socket opening/closing and endless receiving func for Speaker's thread

---

### [BaseSocket](https://github.com/WorHyako/TrackingCameraSpeaker/blob/main/include/socket/BaseSocket.hpp)

> Abstract class for UDP (and TCP in future) socket

public:

* ```
  static bool BaseSocket::checkEndPoint(const std::string &destinationIp_)
  ```
  Check destination address. This code has been a bit refactored, but belongs to some person (can't remember which one)
* ```
  const std::vector<std::byte> &BaseSocket::getPacket() 
  ```
  Return last incoming packet
* ```
  std::condition_variable _dataReceived
  ```
  CV-var to notify other threads to data received
* ```
  std::mutex _receivingMutex
  ```
  Mutex to control buffer accessing. Used by both Server and FreeDPacket