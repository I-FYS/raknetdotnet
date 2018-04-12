#include "Common.h"
#include "BitStreamNET.h"
#include "RakClientNET.h"

RakClientNET::RakClientNET() {
	_rakClient = RakNetworkFactory::GetRakClientInterface();
}

RakClientNET::~RakClientNET() {
	RakNetworkFactory::DestroyRakClientInterface(_rakClient);
}

int RakClientNET::Connect(String ^ address, int port) {
	return _rakClient->Connect(StringToChar(address), port, 0, 0, 5);
}

void RakClientNET::Disconnect(bool timeOut) {
	return _rakClient->Disconnect(timeOut ? 500 : 0);
}

PacketNET ^RakClientNET::Receive() {
	Packet *packet = _rakClient->Receive();
	PacketNET ^packetNet = gcnew PacketNET;
	packetNet->ID = static_cast<PacketEnumNET>(255);
	packetNet->Data = IntPtr(nullptr);
	packetNet->Length = 0;

	if (packet == nullptr)
		return packetNet;

	if (packet->data == nullptr)
		return packetNet;

	RakNet::BitStream bitStream(packet->data, packet->length, false);

	Byte packetId;
	bitStream.Read(packetId);

	int length = packet->length;
	char *data = new char[length];
	memcpy(data, packet->data, length);
	_rakClient->DeallocatePacket(packet);

	packetNet->ID = static_cast<PacketEnumNET>(packetId);
	packetNet->Data = IntPtr(data);
	packetNet->Length = length;
	return packetNet;
}

void RakClientNET::FreePacket(PacketNET ^packet) {
	void *data = packet->Data.ToPointer();

	if (data != nullptr)
		delete data;
}

bool RakClientNET::Send(BitStreamNET ^data) {
	return _rakClient->Send(data->GetBitStream(), SYSTEM_PRIORITY, RELIABLE, NULL);
}

bool RakClientNET::RPC(RPCEnumNET id, BitStreamNET ^data) {
	int rpcId = static_cast<int>(id);
	return _rakClient->RPC(&rpcId, data->GetBitStream(), HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}

RPCParamsNET ^RakClientNET::HandleRPCParams(IntPtr data, int length) {
	BYTE *packetData = static_cast<BYTE *>(data.ToPointer());
	int packetLength = length;

	RakNet::BitStream bitStream(packetData, packetLength, false);

	bitStream.IgnoreBits(8);
	/* if (packetId == ID_TIMESTAMP)
		bitStream.IgnoreBits(8 * (sizeof(RakNetTime) + sizeof(unsigned char))); */

	RPCParamsNET ^rpcParams = gcnew RPCParamsNET;
	rpcParams->Data = IntPtr(nullptr);
	rpcParams->Length = 0;

	BYTE rpcId;
	DWORD sizeBits;

	bitStream.Read(rpcId);
	if (!bitStream.ReadCompressed(sizeBits)) {
		rpcParams->ID = static_cast<RPCEnumNET>(255);
		return rpcParams;
	}

	rpcParams->ID = static_cast<RPCEnumNET>(rpcId);

	if (sizeBits == 0) {
		return rpcParams;

	} else {
		BYTE *rpcData = new BYTE[BITS_TO_BYTES(sizeBits)];
		if (rpcData == nullptr) {
			rpcParams->ID = static_cast<RPCEnumNET>(255);
			return rpcParams;
		}

		if (!bitStream.ReadBits(rpcData, sizeBits)) {
			delete rpcData;
			rpcParams->ID = static_cast<RPCEnumNET>(255);
			return rpcParams;
		}

		rpcParams->Data = IntPtr(rpcData);
		rpcParams->Length = BITS_TO_BYTES(sizeBits);
		return rpcParams;
	}
}

void RakClientNET::FreeRPC(RPCParamsNET ^rpcParams) {
	void *data = rpcParams->Data.ToPointer();

	if (data != nullptr)
		delete data;
}

void RakClientNET::SetNickName(String ^ nickName) {
	if (nickName->Length < 26)
		_rakClient->SetNickName(StringToChar(nickName));
}

String ^ RakClientNET::GetNickName() {
	return CharToString(_rakClient->GetNickName());
}
