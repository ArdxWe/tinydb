//
// Created by ardxwe on 2022/1/30.
//

#ifndef SRC_DATAFILE_H_
#define SRC_DATAFILE_H_

#include <ctime>
#include <fstream>
#include <string>

class Block;

class Datafile {
 public:
  explicit Datafile(std::string file_name);
  bool insert(const Block& block);
  std::uint64_t offset();
  bool active() const;
  std::string read(std::size_t offset, std::size_t size);

  Datafile(const Datafile& other) = delete;
  Datafile& operator=(const Datafile& other) = delete;

 private:
  std::string file_name_;
  std::fstream io_;
  bool active_ = true;
};

#endif  // SRC_DATAFILE_H_
