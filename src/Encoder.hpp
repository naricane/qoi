#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "Common.hpp"

namespace qoi {

std::vector<uint8_t>
encode(std::span<uint8_t> bytes, ImageParams params);

}
