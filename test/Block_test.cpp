//
// Created by hp on 2022/2/3.
//

#include "Block.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Util.h"
#include "gtest/gtest.h"

namespace {
using std::string;
using std::time_t;
using std::uint32_t;
using std::vector;
}  // namespace

TEST(BlockTest, deserializer) {
  using namespace tinydb;

  string key = "adder";
  string value = "database";

  time_t stamp = 0x11223344;
  uint32_t key_size = key.size();
  uint32_t value_size = value.size();

  if (!Util::big_endian()) {
    stamp = Util::reverse(stamp);
    key_size = Util::reverse(key_size);
    value_size = Util::reverse(value_size);
  }

  string st = string{reinterpret_cast<char*>(&stamp), sizeof(stamp)};
  string ks = string{reinterpret_cast<char*>(&key_size), sizeof(key_size)};
  string vs = string{reinterpret_cast<char*>(&value_size), sizeof(value_size)};

  string s;
  s += st + ks + vs;
  s += key + value;

  vector<char> buff;
  for (auto c : s) {
    buff.push_back(c);
  }

  auto v = Block::deserializer(buff);
  ASSERT_EQ(v.size(), 1);

  ASSERT_EQ(v[0].timestamp(),
            Util::big_endian() ? stamp : Util::reverse(stamp));
  ASSERT_EQ(v[0].key_size(),
            Util::big_endian() ? key_size : Util::reverse(key_size));
  ASSERT_EQ(v[0].value_size(),
            Util::big_endian() ? value_size : Util::reverse(value_size));
  ASSERT_EQ(v[0].key(), key);
  ASSERT_EQ(v[0].value(), value);
}
