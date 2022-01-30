//
// Created by ardxwe on 2022/1/30.
//

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

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
};

#endif  // SRC_UTIL_H_
