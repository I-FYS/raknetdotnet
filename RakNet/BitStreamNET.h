#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

public ref class BitStreamNET {
private:
	RakNet::BitStream *_bitStream;

	char *StringToChar(String^ string) {
		return static_cast<char *>(Marshal::StringToHGlobalAnsi(string).ToPointer());
	}

	String ^CharToString(char *ch) {
		return gcnew String(ch);
		/* String ^str;
		for (int i = 0; ch[i] != 0; i++)
			str += wchar_t(ch[i]);
		return str; */
	}

public:
	BitStreamNET();
	BitStreamNET(IntPtr data, int size);
	~BitStreamNET();

	void WriteUInt8(uint8_t value, bool compressed);
	void WriteUInt16(uint16_t value, bool compressed);
	void WriteUInt32(uint32_t value, bool compressed);
	void WriteInt8(int8_t value, bool compressed);
	void WriteInt16(int16_t value, bool compressed);
	void WriteInt32(int32_t value, bool compressed);
	void WriteFloat(float value, bool compressed);
	void WriteDouble(double value, bool compressed);
	void WriteString(String ^str, bool compressed);

	uint8_t ReadUInt8(bool compressed);
	uint16_t ReadUInt16(bool compressed);
	uint32_t ReadUInt32(bool compressed);
	int8_t ReadInt8(bool compressed);
	int16_t ReadInt16(bool compressed);
	int32_t ReadInt32(bool compressed);
	float ReadFloat(bool compressed);
	double ReadDouble(bool compressed);
	String ^ReadString(int amount, bool compressed);

	void SetReadOffset(int offset) {
		_bitStream->SetReadOffset(offset);
	}

	void SetWriteOffset(int offset) {
		_bitStream->SetWriteOffset(offset);
	}

	int GetReadOffset() {
		return _bitStream->GetReadOffset();
	}

	int GetWriteOffset() {
		return _bitStream->GetWriteOffset();
	}

	void Reset() {
		_bitStream->Reset();
	}

	IntPtr GetData() {
		return IntPtr(_bitStream->GetData());
	}

	int GetSize() {
		return _bitStream->GetNumberOfBytesUsed();
	}

	void IgnoreBytes(int amount) {
		_bitStream->IgnoreBits(BYTES_TO_BITS(amount));
	}

	RakNet::BitStream *GetBitStream() {
		return _bitStream;
	}
};