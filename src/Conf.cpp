//
// Created by ardxwe on 2022/1/30.
//

#include "Conf.h"

#include <cstddef>

namespace tinydb {

const std::size_t Conf::data_file_size = 8 * 1024 * 1024;  // 8 MB
const char *Conf::data_file_suffix_ = ".data";
const char *Conf::data_file_dir_ = "data";

}  // namespace tinydb
