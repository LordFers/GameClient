#ifndef CLSBYTEBUFFER_H
#define CLSBYTEBUFFER_H
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include "vb6compat.h"
#include "enums.h"

class clsByteBuffer {

private:
	std::vector<std::int8_t> data;
	std::size_t position;

public:
	void initializeReader(std::vector<std::int8_t>& v);

public:
	void initializeWriter();

public:
	int getByte();

public:
	int getInteger();

public:
	int getLong();

public:
	float getSingle();

public:
	double getDouble();

public:
	std::string getString(int length = -1);

public:
	void putByte(int value);

public:
	void putInteger(int value);

public:
	void putLong(int value);

public:
	void putSingle(float value);

public:
	void putDouble(double value);

public:
	void putString(const std::string & str, bool withLength = true);

public:
	std::vector<std::int8_t>& getBuffer();

};
#endif
