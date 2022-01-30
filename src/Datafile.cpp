//
// Created by ardxwe on 2022/1/30.
//

#include "Datafile.h"

#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include "Block.h"
#include "Conf.h"

namespace {
using std::move;
using std::string;
using std::uint64_t;
using std::vector;
}  // namespace

Datafile::Datafile(string file_name)
    : file_name_{move(file_name)}, io_{file_name_, std::ios_base::out} {
  // default is active
  io_ << true;
  io_.sync();
}

bool Datafile::insert(const Block& block) {
  vector<char> buff = block.serializer();

  auto file_size = static_cast<std::size_t>(offset());

  if (file_size + buff.size() > Conf::data_file_size) {
    active_ = false;

    io_.seekp(0);
    io_ << false;
    io_.close();

    return false;
  }

  io_.write(buff.data(), static_cast<std::streamsize>(buff.size()));

  // write into disk
  io_.sync();
  return true;
}

bool Datafile::active() const { return active_; }

uint64_t Datafile::offset() { return static_cast<std::uint64_t>(io_.tellp()); }
