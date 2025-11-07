#pragma once

#include <cstdint>

namespace qoi {

enum class Opcode
{
	INDEX = 0b00,
	DIFF = 0b01,
	LUMA = 0b10,
	RUN = 0b11,
	RGB = 0xFE,
	RGBA = 0xFF,
};

struct ImageParams
{
	uint32_t width;
	uint32_t height;
	uint8_t channels;
	uint8_t colorspace;
};

struct RGBA
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 255;

	bool operator==(RGBA other)
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}
};

}
