//
// Created by ardxwe on 2022/1/30.
//

#ifndef SRC_BLOCK_H_
#define SRC_BLOCK_H_

#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

namespace tinydb {

class Block {
 public:
  friend class Datafile;

  static std::vector<Block> deserializer(const std::vector<char>& buff);

  Block(const std::string& key, const std::string& value);
  Block(std::time_t timestamp, std::uint32_t key_size, std::uint32_t value_size,
        std::string&& key, std::string&& value);

  [[nodiscard]] std::vector<char> serializer() const;
  [[nodiscard]] std::uint32_t value_offset() const;
  [[nodiscard]] std::time_t timestamp() const;

  // for test
  [[nodiscard]] std::uint32_t key_size() const;
  [[nodiscard]] std::uint32_t value_size() const;
  [[nodiscard]] std::string key() const;
  [[nodiscard]] std::string value() const;
  [[nodiscard]] std::size_t size() const;

 private:
  const std::time_t timestamp_;
  const std::uint32_t key_size_;
  const std::uint32_t value_size_;
  const std::string key_;
  const std::string value_;
};

}  // namespace tinydb

#endif  // SRC_BLOCK_H_
