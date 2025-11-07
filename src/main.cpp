#include "Decoder.hpp"
#include "Encoder.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int
main(int argc, char** args)
{
	int w;
	int h;
	int c;

	uint8_t* data;
	if (argc > 1) {
		data = stbi_load(args[1], &w, &h, &c, 3);
	}

	qoi::ImageParams params = {
		uint32_t(w),
		uint32_t(h),
		uint8_t(c),
		0,
	};
	auto encoded = qoi::encode({ data, size_t(w * h * c) }, params);
	auto decoded = qoi::decode(encoded);

	stbi_write_png("output.png", w, h, c, &decoded[0], w * c);

	return 0;
}
