//
// Created by ardxwe on 2022/1/30.
//

#include "Datafile.h"

#include <cassert>
#include <cstddef>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "Block.h"
#include "Conf.h"

namespace {
using std::ifstream;
using std::move;
using std::size_t;
using std::string;
using std::uint64_t;
using std::vector;
}  // namespace

namespace tinydb {

bool Datafile::include(const Block &block) {
  return block.size() + sizeof(bool) <= Conf::data_file_size;
}

[[maybe_unused]] std::vector<char> Datafile::get_content(
    const string &file_name) {
  auto get_file_size = [&file_name]() {
    std::ifstream in(file_name, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
  };

  std::size_t size = get_file_size();
  assert(size > 1);

  // ignore active flag
  vector<char> res(size - 1, 0);

  ifstream file{file_name};
  assert(file.is_open());

  // file should be un-active
  bool active;
  file >> active;
  assert(!active);

  file.read(res.data(), static_cast<std::streamsize>(res.size()));
  return res;
}

Datafile::Datafile(string file_name, bool read_only)
    : file_name_{move(file_name)},
      io_{file_name_, read_only ? std::ios_base::in | std::ios_base::ate
                                : std::ios_base::out | std::ios_base::in |
                                      std::ios_base::trunc} {
  // default is active
  if (!read_only) {
    io_ << true;
  }
}

bool Datafile::insert(const Block &block) {
  assert(active_);

  vector<char> buff = block.serializer();

  auto file_size = static_cast<size_t>(offset());

  // this file is full
  if (file_size + buff.size() > Conf::data_file_size) {
    active_ = false;

    io_.seekp(0);
    io_ << false;

    return false;
  }

  io_.write(buff.data(), static_cast<std::streamsize>(buff.size()));
  return true;
}

uint64_t Datafile::offset() { return static_cast<uint64_t>(io_.tellp()); }

bool Datafile::active() const { return active_; }

std::string Datafile::read(std::uint64_t offset, std::size_t size) {
  uint64_t old_offset = this->offset();

  assert(offset >= 0 && offset < old_offset);

  io_.seekg(static_cast<std::streamoff>(offset));

  vector<char> v(size, ' ');

  io_.read(v.data(), static_cast<std::streamsize>(size));

  io_.seekg(static_cast<std::streamoff>(old_offset));

  return string{v.data(), size};
}

std::string Datafile::filename() const { return file_name_; }
}  // namespace tinydb
