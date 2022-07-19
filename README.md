# TrackingCameraSpeaker
#### by Worshiper Hyakki Yakō(worHyako)
### This repo is designed to accept UDP packet (FreeD protocol) from local network and convert it to camera parameters: position, rotation and lens value.

---

# Classes:
> ### TrackingSpeaker
>> This is your Speaker. Enjoy it
> ---
> public:
> * void setOsFlag(FreeDPacket::camera_data_type) - Set flag for desired output stream info
> * float get_%value%_() - Float/int getters for X,Y,Z,Rx,Ry,Rz,Zoom,Focus camera parameters
> * bool startReader(const std::string& local_ip, int16_t local_port) - Open socket if possible and start receiving and parsing (2) threads
> * bool stopReader() - Shutdown goddamn speaker. Stop threads, close socket.
> 
> private:
> * void startParse() - Endless func used by Speaker's thread. Unfortunately nothing interesting

> ### FreedPacket
>> Contains information about the package and methods for data parsing
> ---
> public:
> * float get_%value%_() - Float/int getters for camera data: x,y,z,Rx,Ry,Rz,Zoom,Focus,Rx,Ry,Rz,Zoom,Focus 
> * void parseData(std::array<unsigned char, FREED_PACKET_LENGTH> data) - Method for parsing a packet for camera data
> 
> private:
> * float parse_%type%_(unsigned char &a, unsigned char &b, unsigned char &c) - Float/int Angle/Location/Lens methods to calculate data from packet

> ### CameraData
>> Just for easy data manipulation
> ---
> * Literally just a set of operators, I swear

> ### PartialBuffer
>> Temp place (buffer) to packet repairing
> ---
> public:
> * bool tryToAppendNewData(const std::array<unsigned char, PARTIAL_BUFFER_PACKET_LENGTH> &new_data) - Packet integrity check and calculation info for repairing if it is needed
> * bool checkChecksum(const std::array<unsigned char, PARTIAL_BUFFER_PACKET_LENGTH> &byte_array) - Check checksum(tautology, but it's true)

> ### ServerUdpSocket : BaseSocket
>> Main class to accept packets
> ---
> Not so interesting. Just socket opening/closing and endless receiving func used by Speaker's thread 

> ### BaseSocket
>> Abstract class for UDP (and TCP in future) socket
> ---
> public:
> * static bool checkEndPoint(const std::string &destination_ip) - Check destination address. This code has been a bit refactored, but belongs to some person (can't remember which one)
> * char *getDataInCharPtr() - Return pointer to buffer
> * std::vector<byte> getDataInStlVector() - Return buffer in std::vector type
> * std::array<int, BUFFER_LENGTH> getDataInIntArray() - Return buffer in std::array type
> * NetParameters getNetParameters() - NetParameters contains address/port info. Usually useless (useless like the previous 2 functions)
