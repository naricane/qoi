#include "Encoder.hpp"

namespace qoi {

RGBA
current_px(std::span<uint8_t> bytes, size_t pos, uint8_t channels)
{
	if (channels == 4) {
		return { bytes[pos], bytes[pos + 1], bytes[pos + 2], bytes[pos + 3] };
	} else {
		return { bytes[pos], bytes[pos + 1], bytes[pos + 2], 255 };
	}
}

void
write_px(RGBA px, uint8_t channels, std::vector<uint8_t>& out)
{
	if (channels == 3) {
		out.insert(out.end(), { uint8_t(Opcode::RGB), px.r, px.g, px.b });
	} else if (channels == 4) {
		out.insert(out.end(), { uint8_t(Opcode::RGBA), px.r, px.g, px.b, px.a });
	}
}

void
write_group(Opcode opcode, uint8_t data, std::vector<uint8_t>& out)
{
	uint8_t byte = (uint8_t(opcode) << 6) | data;
	out.insert(out.end(), { byte });
}

std::vector<uint8_t>
encode(std::span<uint8_t> bytes, ImageParams params)
{
	RGBA prev_px = { 0, 0, 0, 255 };
	RGBA px;
	uint8_t run = 0;
	std::vector<uint8_t> out;

	for (size_t pos = 0; pos < bytes.size(); pos += params.channels) {
		px = current_px(bytes, pos, params.channels);

		if (px == prev_px) {
			run += 1;
			if (run == 62 || pos == bytes.size() - params.channels) {
				write_group(Opcode::RUN, run - 1, out);
				run = 0;
			}
		} else {
			if (run > 0) {
				write_group(Opcode::RUN, run - 1, out);
				run = 0;
			}
			write_px(px, params.channels, out);
		}

		prev_px = px;
	}

	return out;
}

}
