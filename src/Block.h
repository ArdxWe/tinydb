//
// Created by ardxwe on 2022/1/30.
//

#ifndef BITMASK_BLOCK_H
#define BITMASK_BLOCK_H

#include <ctime>
#include <string>
#include <vector>

class Block {
 public:
  Block(const std::string& key, const std::string& value);
  [[nodiscard]] std::vector<char> serializer() const;

  Block(const Block& other) = delete;
  Block& operator=(const Block& other) = delete;

 private:
  std::time_t timestamp_;
  std::size_t key_size_;
  std::size_t value_size_;
  std::string key_;
  std::string value_;
};

#endif  // BITMASK_BLOCK_H
