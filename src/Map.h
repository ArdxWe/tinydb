//
// Created by ardxwe on 2022/1/31.
//

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <string>
#include <unordered_map>

namespace tinydb {

struct Value {
  std::uint64_t file_id;
  std::size_t value_size;
  std::uint64_t offset;
  std::time_t timestamp;
};

class Map {
 public:
  void put(const std::string &key, const Value &value);
  bool find(const std::string &key);
  void erase(const std::string &key);

  Value &get(const std::string &key);

 private:
  std::unordered_map<std::string, Value> map_{};
};

}  // namespace tinydb

#endif  // SRC_MAP_H_
