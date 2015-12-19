#include "ByteQueue.h"

#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SCOPED_ENUMS

#include <locale>
#include <codecvt>

clsByteQueue::clsByteQueue() : readPos(0) {

}

void clsByteQueue::commitRead(int pos) {
	data.erase(data.begin(), data.begin() + pos);
	readPos -= pos;
}

void clsByteQueue::revertRead(int oldPos) {
	readPos = oldPos;
}

void clsByteQueue::WriteByte(std::int8_t value) {
	data.push_back(static_cast<std::int8_t>(0xff & value));
}

void clsByteQueue::WriteInteger(std::int16_t value) {
	union {
		std::int16_t a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteLong(std::int32_t value) {
	union {
		std::int32_t a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteSingle(float value) {
	union {
		float a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteDouble(double value) {
	union {
		double a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteBoolean(bool value) {
	data.push_back(value ? 1 : 0);
}

void clsByteQueue::WriteUnicodeStringFixed(const std::string& value) {
	WriteBinaryFixed(value);
}

void clsByteQueue::WriteUnicodeString(const std::string& value) {
	WriteBinary(value);
}

void clsByteQueue::WriteBinary(const std::string& value) {
	WriteInteger(value.size());
	WriteBinaryFixed(value);
}

void clsByteQueue::WriteBlock(const char* buf, int n) {
	data.insert(data.end(), buf, buf + n);
}

std::string clsByteQueue::ReadASCIIFixed(int length){
    return PeekBinaryFixed(length);
}

std::string clsByteQueue::ReadBinaryFixed(int length) {
	std::string tmp = PeekBinaryFixed(length);
	readPos += tmp.size();
	return tmp;
}

std::string clsByteQueue::ReadUnicodeStringFixed(int length) {
	return ReadBinaryFixed(length);
}

std::string clsByteQueue::ReadBinary() {
	std::string tmp = PeekBinary();
	readPos += tmp.size() + 2;
	return tmp;
}

std::string clsByteQueue::ReadUnicodeString() {
	return ReadBinary();
}

std::string clsByteQueue::PeekBinaryFixed(std::size_t length) {
	if (length > BQ_MAX_STRING_SIZE)
		throw bytequeue_data_error("length > BQ_MAX_STRING_SIZE");
	if (readPos + length > data.size())
		throw insufficient_data_error();
	const char* p = reinterpret_cast<const char*>(data.data() + readPos);
	return std::string(p, p + length);
}

std::string clsByteQueue::PeekUnicodeStringFixed(int length) {
	return PeekBinaryFixed(length);
}

std::string clsByteQueue::PeekBinary() {
	std::size_t length = PeekInteger();
	if (length > BQ_MAX_STRING_SIZE)
		throw bytequeue_data_error("length > BQ_MAX_STRING_SIZE");
	if (readPos + length + 2 > data.size())
		throw insufficient_data_error();
	const char* p = reinterpret_cast<const char*>(data.data() + readPos);
	return std::string(p + 2, p + 2 + length);
}

std::string clsByteQueue::PeekUnicodeString() {
	return PeekBinary();
}

int clsByteQueue::length() {
	return data.size() - readPos;
}

