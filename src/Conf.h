//
// Created by ardxwe on 2022/1/30.
//

#ifndef SRC_CONF_H_
#define SRC_CONF_H_

#include <cstddef>

namespace tinydb {

class Conf {
 public:
  static const std::size_t data_file_size;
  static const char *data_file_suffix_;
  static const char *data_file_dir_;
};

}  // namespace tinydb

#endif  // SRC_CONF_H_
