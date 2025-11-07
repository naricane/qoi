#pragma once

#include <cstdint>
#include <span>
#include <vector>

namespace qoi {

std::vector<uint8_t>
decode(std::span<uint8_t> bytes);

}
