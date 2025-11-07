#include "Decoder.hpp"
#include "Common.hpp"

namespace qoi {

std::vector<uint8_t>
decode(std::span<uint8_t> bytes)
{
	std::vector<uint8_t> img;
	std::size_t pos = 0;
	qoi::RGBA px;

	while (pos < bytes.size()) {
		uint8_t byte = bytes[pos];

		if (byte == uint8_t(Opcode::RGBA)) {
			px = { bytes[pos + 1], bytes[pos + 2], bytes[pos + 3], bytes[pos + 4] };
			img.insert(img.end(), { px.r, px.g, px.b, px.a });
			pos += 5;
		} else if (byte == uint8_t(Opcode::RGB)) {
			px = { bytes[pos + 1], bytes[pos + 2], bytes[pos + 3] };
			img.insert(img.end(), { px.r, px.g, px.b });
			pos += 4;
		} else {
			switch (byte >> 6) {
				case uint8_t(Opcode::RUN):
					int8_t length = int(byte & 0x3F);
					for (int i = 0; i <= length; i++) {
						img.insert(img.end(), { px.r, px.g, px.b });
					}
					pos += 1;
					break;
			}
		}
	}

	return img;
}

}
