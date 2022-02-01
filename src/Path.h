//
// Created by ardxwe on 2022/1/31.
//

#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <string>

namespace tinydb {

class Path {
 public:
  static std::string data_file_name(std::uint64_t file_id);
};

}  // namespace tinydb

#endif  // SRC_PATH_H_
