//
// Created by ardxwe on 2022/1/31.
//

#include "Path.h"

#include <string>
#include <vector>

#include "Conf.h"

namespace {
using std::string;
using std::vector;
}  // namespace

std::string Path::data_file_name(std::uint64_t file_id) {
  return std::to_string(file_id) + Conf::data_file_suffix_;
}
