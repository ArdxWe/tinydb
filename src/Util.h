//
// Created by ardxwe on 2022/1/30.
//

#ifndef BITMASK_UTIL_H
#define BITMASK_UTIL_H

#include <filesystem>
#include <string>

class Util {
 public:
  static bool big_endian();

  template <class T>
  static T reverse(T data) {
    T res;

    char* data_begin = reinterpret_cast<char*>(&data);
    char* res_begin = reinterpret_cast<char*>(&res);

    for (int i = 0; i < static_cast<int>(sizeof(data)); i++) {
      res_begin[i] = data_begin[sizeof(data) - 1 - i];
    }
    return res;
  }

  static std::size_t file_size(const std::string& file_name) {
    std::filesystem::path path{file_name};
    return static_cast<std::size_t>(std::filesystem::file_size(path));
  }
};

#endif  // BITMASK_UTIL_H
