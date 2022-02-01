//
// Created by ardxwe on 2022/1/31.
//

#include "Path.h"

#include <cstdint>
#include <string>
#include <vector>

#include "Conf.h"

namespace {
using std::string;
using std::vector;
}  // namespace

string Path::data_file_name(uint64_t file_id) {
  return string("./") + Conf::data_file_dir_ + "/" + std::to_string(file_id) +
         Conf::data_file_suffix_;
}
