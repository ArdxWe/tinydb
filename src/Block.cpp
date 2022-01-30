//
// Created by ardxwe on 2022/1/30.
//

#include "Block.h"

#include <cstring>
#include <ctime>
#include <vector>

#include "Util.h"

namespace {
using std::size_t;
using std::time;
using std::time_t;
using std::vector;
}  // namespace

Block::Block(const std::string &key, const std::string &value)
    : timestamp_{time(nullptr)},
      key_size_{static_cast<size_t>(key.size())},
      value_size_{static_cast<size_t>(value.size())},
      key_{key},
      value_{value} {}

std::vector<char> Block::serializer() const {
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
