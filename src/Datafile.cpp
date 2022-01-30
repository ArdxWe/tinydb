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
#include "Util.h"

namespace {
using std::move;
using std::string;
using std::vector;
}  // namespace

Datafile::Datafile(string file_name)
    : file_name_{move(file_name)}, io_{file_name_, std::ios_base::out} {}

void Datafile::insert(const Block &block) {
  vector<char> buff = block.serializer();

  std::size_t file_size = Util::file_size(file_name_);
  assert(file_size + buff.size() <= Conf::data_file_size);
  io_.write(buff.data(), static_cast<std::streamsize>(buff.size()));
  io_.sync();
}
