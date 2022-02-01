//
// Created by ardxwe on 2022/1/30.
//

#include "Util.h"

#include <cstdint>

namespace {
using std::uint32_t;
using std::uint8_t;
}  // namespace

namespace tinydb {

bool Util::big_endian() {
  uint32_t data = 0x11223344;
  uint8_t first_byte = *(reinterpret_cast<uint8_t *>(&data));

  return first_byte == 0x11;
}

}  // namespace tinydb
