//
// Created by ardxwe on 2022/1/30.
//

#include "Block.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

#include "Util.h"

namespace {
using std::size_t;
using std::string;
using std::time;
using std::time_t;
using std::uint32_t;
using std::vector;
}  // namespace

namespace tinydb {

// block format --- timestamp --- key size --- value size --- key --- value
vector<Block> Block::deserializer(const vector<char> &buff) {
  vector<Block> res;

  size_t offset = 0;
  const char *cur = buff.data();

  while (offset != static_cast<size_t>(buff.size())) {
    time_t timestamp;
    uint32_t key_size;
    uint32_t value_size;

    string time_str = string{cur, sizeof(time_t)};
    string key_size_str = string{cur + sizeof(time_t), sizeof(uint32_t)};
    string value_size_str =
        string{cur + sizeof(time_t) + sizeof(uint32_t), sizeof(uint32_t)};

    if (!Util::big_endian()) {
      timestamp = Util::reverse(*reinterpret_cast<time_t *>(time_str.data()));
      key_size =
          Util::reverse(*reinterpret_cast<uint32_t *>(key_size_str.data()));
      value_size =
          Util::reverse(*reinterpret_cast<uint32_t *>(value_size_str.data()));
    } else {
      timestamp = *reinterpret_cast<time_t *>(time_str.data());
      key_size = *reinterpret_cast<uint32_t *>(key_size_str.data());
      value_size = *reinterpret_cast<uint32_t *>(value_size_str.data());
    }

    string key =
        string{cur + sizeof(timestamp) + sizeof(key_size) + sizeof(value_size),
               key_size};
    string value = string{cur + sizeof(timestamp) + sizeof(key_size) +
                              sizeof(value_size) + key_size,
                          value_size};

    res.emplace_back(timestamp, key_size, value_size, move(key), move(value));

    size_t block_size = sizeof(timestamp) + sizeof(key_size) +
                        sizeof(value_size) + key_size + value_size;

    offset += block_size;
    cur += block_size;
  }

  return res;
}

Block::Block(const string &key, const string &value)
    : timestamp_{time(nullptr)},
      key_size_{static_cast<uint32_t>(key.size())},
      value_size_{static_cast<uint32_t>(value.size())},
      key_{key},
      value_{value} {}

Block::Block(time_t timestamp, uint32_t key_size, uint32_t value_size,
             string &&key, string &&value)
    : timestamp_{timestamp},
      key_size_{key_size},
      value_size_{value_size},
      key_{key},
      value_{value} {}

vector<char> Block::serializer() const {
  const size_t block_size = sizeof(timestamp_) + sizeof(key_size_) +
                            sizeof(value_size_) + key_.size() + value_.size();

  vector<char> res(block_size, ' ');

  char *cur = res.data();

  time_t tm;
  uint32_t key_size;
  uint32_t value_size;

  if (!Util::big_endian()) {
    tm = Util::reverse(timestamp_);
    key_size = Util::reverse(key_size_);
    value_size = Util::reverse(value_size_);
  } else {
    tm = timestamp_;
    key_size = key_size_;
    value_size = value_size_;
  }

  memcpy(cur, &tm, sizeof(tm));
  cur += sizeof(tm);

  memcpy(cur, &key_size, sizeof(key_size));
  cur += sizeof(key_size);

  memcpy(cur, &value_size, sizeof(value_size));
  cur += sizeof(value_size);

  memcpy(cur, key_.data(), key_.size());
  cur += key_.size();

  memcpy(cur, value_.data(), value_.size());

  return res;
}

uint32_t Block::value_offset() const {
  return sizeof(timestamp_) + sizeof(key_size_) + sizeof(value_size_) +
         key_.size();
}

time_t Block::timestamp() const { return timestamp_; }

std::uint32_t Block::key_size() const { return key_size_; }

std::uint32_t Block::value_size() const { return value_size_; }

std::string Block::key() const { return key_; }

std::string Block::value() const { return value_; }

std::size_t Block::size() const {
  return sizeof(timestamp_) + sizeof(key_size_) + sizeof(value_size_) +
         key_.size() + value_.size();
}

}  // namespace tinydb
