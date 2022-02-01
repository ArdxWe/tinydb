//
// Created by ardxwe on 2022/1/30.
//

#ifndef SRC_BLOCK_H_
#define SRC_BLOCK_H_

#include <ctime>
#include <string>
#include <vector>

namespace tinydb {

class Datafile;

class Block {
 public:
  friend class Datafile;

  Block(const std::string &key, const std::string &value);
  [[nodiscard]] std::vector<char> serializer() const;
  [[nodiscard]] std::uint64_t value_offset() const;
  [[nodiscard]] std::time_t timestamp() const;

  Block(const Block &other) = delete;
  Block &operator=(const Block &other) = delete;

 private:
  std::time_t timestamp_;
  std::size_t key_size_;
  std::size_t value_size_;
  std::string key_;
  std::string value_;
};

}  // namespace tinydb

#endif  // SRC_BLOCK_H_
