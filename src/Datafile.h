//
// Created by ardxwe on 2022/1/30.
//

#ifndef SRC_DATAFILE_H_
#define SRC_DATAFILE_H_

#include <cstdint>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

namespace tinydb {

class Block;
class Datafile {
 public:
  static bool include(const Block &block);
  [[maybe_unused]] static std::vector<char> get_content(
      const std::string &file_name);

  explicit Datafile(std::string file_name, bool read_only = false);

  bool insert(const Block &block);
  std::uint64_t offset();
  bool active() const;
  std::string read(std::uint64_t offset, std::size_t size);
  std::string filename() const;

  Datafile(const Datafile &other) = delete;
  Datafile &operator=(const Datafile &other) = delete;

 private:
  std::string file_name_;
  std::fstream io_;
  bool active_ = true;
};

}  // namespace tinydb

#endif  // SRC_DATAFILE_H_
