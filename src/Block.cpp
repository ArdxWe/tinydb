//
// Created by ardxwe on 2022/1/30.
//

#include "Block.h"

#include <cstddef>
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
using std::uint64_t;
using std::vector;
}  // namespace

namespace tinydb {

Block::Block(const string &key, const string &value)
    : timestamp_{time(nullptr)},
      key_size_{static_cast<size_t>(key.size())},
      value_size_{static_cast<size_t>(value.size())},
      key_{key},
      value_{value} {}

vector<char> Block::serializer() const {
  const size_t len = sizeof(timestamp_) + sizeof(key_size_) +
                     sizeof(value_size_) + key_.size() + value_.size();

  vector<char> res(len, ' ');

  char *cur = res.data();

  if (!Util::big_endian()) {
    time_t reverse = Util::reverse(timestamp_);

    memcpy(cur, &reverse, sizeof(reverse));
    cur += sizeof(reverse);

    size_t key_size = Util::reverse(key_size_);

    memcpy(cur, &key_size, sizeof(key_size));
    cur += sizeof(key_size);

    size_t value_size = Util::reverse(value_size_);

    memcpy(cur, &value_size, sizeof(value_size));
    cur += sizeof(value_size);
  } else {
    memcpy(cur, &timestamp_, sizeof(timestamp_));
    cur += sizeof(timestamp_);

    memcpy(cur, &key_size_, sizeof(key_size_));
    cur += sizeof(key_size_);

    memcpy(cur, &value_size_, sizeof(value_size_));
    cur += sizeof(value_size_);
  }

  memcpy(cur, key_.data(), key_.size());
  cur += key_.size();

  memcpy(cur, value_.data(), value_.size());

  return res;
}

uint64_t Block::value_offset() const {
  return sizeof(timestamp_) + sizeof(key_size_) + sizeof(value_size_) +
         key_.size();
}

time_t Block::timestamp() const { return timestamp_; }

// block format --- timestamp --- key size --- value size --- key --- value
vector<Block> Block::deserializer(const vector<char> &buff) {
  vector<Block> res;

  size_t offset = 0;
  const char *cur = buff.data();

  while (offset != static_cast<size_t>(buff.size())) {
    time_t timestamp;
    size_t key_size;
    size_t value_size;

    string time_str = string{cur, sizeof(time_t)};
    string key_size_str = string{cur + sizeof(time_t), sizeof(size_t)};
    string value_size_str =
        string{cur + sizeof(time_t) + sizeof(size_t), sizeof(size_t)};

    if (!Util::big_endian()) {
      timestamp = Util::reverse(*reinterpret_cast<time_t *>(time_str.data()));
      key_size =
          Util::reverse(*reinterpret_cast<size_t *>(key_size_str.data()));
      value_size =
          Util::reverse(*reinterpret_cast<size_t *>(value_size_str.data()));
    } else {
      timestamp = *reinterpret_cast<time_t *>(time_str.data());
      key_size = *reinterpret_cast<size_t *>(key_size_str.data());
      value_size = *reinterpret_cast<size_t *>(value_size_str.data());
    }

    string key =
        string{cur + sizeof(timestamp) + sizeof(key_size) + sizeof(value_size),
               key_size};
    string value = string{cur + sizeof(timestamp) + sizeof(key_size) +
                              sizeof(value_size) + key_size,
                          value_size};

    res.emplace_back(timestamp, key_size, value_size, move(key), move(value));

    std::size_t block_size = sizeof(timestamp) + sizeof(key_size) +
                             sizeof(value_size) + key_size + value_size;

    offset += block_size;
    cur += block_size;
  }

  return res;
}

Block::Block(time_t timestamp, size_t key_size, size_t value_size, string &&key,
             string &&value)
    : timestamp_{timestamp},
      key_size_{key_size},
      value_size_{value_size},
      key_{move(key)},
      value_{move(value)} {}

std::size_t Block::key_size() const { return key_size_; }

std::size_t Block::value_size() const { return value_size_; }

std::string Block::key() const { return key_; }

std::string Block::value() const { return value_; }

}  // namespace tinydb
