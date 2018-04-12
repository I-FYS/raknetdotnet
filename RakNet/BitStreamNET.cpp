#include "Common.h"
#include <typeinfo>
#include "BitStreamNET.h"

BitStreamNET::BitStreamNET() {
	_bitStream = new RakNet::BitStream();
}

BitStreamNET::BitStreamNET(IntPtr data, int length) {
	_bitStream = new RakNet::BitStream(static_cast<Byte *>(data.ToPointer()), length, false);
}

BitStreamNET::~BitStreamNET() {
	delete _bitStream;
}

void BitStreamNET::WriteUInt8(uint8_t value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteUInt16(uint16_t value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteUInt32(uint32_t value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteInt8(int8_t value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteInt16(int16_t value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteInt32(int32_t value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteFloat(float value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteDouble(double value, bool compressed) {
	if (!compressed)
		_bitStream->Write(value);
	else
		_bitStream->WriteCompressed(value);
}

void BitStreamNET::WriteString(String ^str, bool compressed) {
	if (!compressed)
		_bitStream->Write(StringToChar(str), str->Length);
	else
		stringCompressor->EncodeString(StringToChar(str), str->Length, _bitStream);
}

uint8_t BitStreamNET::ReadUInt8(bool compressed) {
	uint8_t value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

uint16_t BitStreamNET::ReadUInt16(bool compressed) {
	uint16_t value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

uint32_t BitStreamNET::ReadUInt32(bool compressed) {
	uint32_t value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

int8_t BitStreamNET::ReadInt8(bool compressed) {
	int8_t value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

int16_t BitStreamNET::ReadInt16(bool compressed) {
	int16_t value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

int32_t BitStreamNET::ReadInt32(bool compressed) {
	int32_t value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

float BitStreamNET::ReadFloat(bool compressed) {
	float value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

double BitStreamNET::ReadDouble(bool compressed) {
	double value = 0;

	if (!compressed)
		_bitStream->Read(value);
	else
		_bitStream->ReadCompressed(value);

	return value;
}

String ^BitStreamNET::ReadString(int amount, bool compressed) {
	char *data = new char[amount + 1];

	if (!compressed)
		_bitStream->Read(data, amount);
	else
		stringCompressor->DecodeString(data, amount, _bitStream);
	data[amount] = 0;

	// String ^str = Marshal::PtrToStringAnsi(IntPtr(data), amount);
	String ^str = CharToString(data);
	delete data;

	return str;
}