#ifndef CLSBYTEQUEUE_H
#define CLSBYTEQUEUE_H

#include <vector>
#include <memory>
#include <string>
#include <exception>
#include <iterator>

#include "vb6compat.h"
#include "enums.h"

#define CLSBYTEQUEUE_CLIENT_ENCODING "Latin1"

class insufficient_data_error : public std::exception {

};

class bytequeue_data_error : public std::exception {
public:
	bytequeue_data_error(std::string msg) : msg_(msg) {}

	virtual const char* what() const noexcept override { return msg_.c_str(); }

private:
	std::string msg_;
};

class clsByteQueue {

private:
	std::vector<std::int8_t> data;

	std::size_t readPos;

public:
	clsByteQueue();

	enum BQ {
		BQ_MAX_STRING_SIZE = 20 * 1024
	};

public:
	void commitRead(int pos);
	void revertRead(int oldPos);

	int getReadPos() const {
		return readPos;
	}

	void swapAndCleanRawBuffer(std::vector<std::int8_t>& dest) {
		if (readPos != 0)
			throw bytequeue_data_error("swapAndCleanRawBuffer readPos != 0");
		dest.swap(data);
	}

public:

private:
	void WriteData(const std::vector<std::int8_t>& buf);

public:
	void WriteByte(std::int8_t value);

	void WriteInteger(std::int16_t value);

	void WriteLong(std::int32_t value);

	void WriteSingle(float value);

	void WriteDouble(double value);

	void WriteBoolean(bool value);

	void WriteUnicodeStringFixed(const std::string& value);

	template<typename Iterator>
    inline void WriteBinaryFixed(Iterator from, Iterator to) {
        data.insert(data.end(), from, to);
    }

    inline void WriteBinaryFixed(const std::string& value) {
        WriteBinaryFixed(value.begin(), value.end());
    }

    inline void WriteBinaryFixed(const std::vector<int8_t>& value) {
        WriteBinaryFixed(value.begin(), value.end());
    }

	void WriteUnicodeString(const std::string& value);

    void WriteBinary(const std::string& value);

	void WriteBlock(const char* buf, int n);

	inline void WriteBlock(const uint8_t* buf, int n) {
		WriteBlock(reinterpret_cast<const char*>(buf), n);
	}

public:
	inline std::int8_t ReadByte() {
		std::int8_t tmp = PeekByte();
		readPos += sizeof(tmp);
		return tmp;
	}

	inline std::int16_t ReadInteger() {
		std::int16_t tmp = PeekInteger();
		readPos += sizeof(tmp);
		return tmp;
	}

	inline std::int32_t ReadLong() {
		std::int32_t tmp = PeekLong();
		readPos += sizeof(tmp);
		return tmp;
	}

	inline float ReadSingle() {
		float tmp = PeekLong();
		readPos += sizeof(tmp);
		return tmp;
	}

	inline double ReadDouble() {
		double tmp = PeekLong();
		readPos += sizeof(tmp);
		return tmp;
	}

	inline bool ReadBoolean() {
		return ReadByte();
	}

    std::string ReadASCIIFixed(int length);

	std::string ReadBinaryFixed(int length);

	std::string ReadUnicodeStringFixed(int length);

	std::string ReadBinary();

	std::string ReadUnicodeString();

	inline std::int8_t PeekByte() {
		return PeekRaw<std::int8_t>();
	}

	inline std::int16_t PeekInteger() {
		return PeekRaw<std::int16_t>();
	}

	inline std::int32_t PeekLong() {
		return PeekRaw<std::int32_t>();
	}

	inline float PeekSingle() {
		return PeekRaw<float>();
	}

	inline double PeekDouble() {
		return PeekRaw<double>();
	}

	inline bool PeekBoolean() {
		return PeekRaw<std::int8_t>();
	}

	std::string PeekBinaryFixed(std::size_t length);

	std::string PeekUnicodeStringFixed(int length);

	std::string PeekBinary();

	std::string PeekUnicodeString();

	int length();

private:
	template <typename T>
	inline T PeekRaw() {
		if (readPos + sizeof(T) > data.size())
			throw insufficient_data_error();
		T* p = reinterpret_cast<T*>(data.data() + readPos);
		return *p;
	}

};

#endif
