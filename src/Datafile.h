//
// Created by ardxwe on 2022/1/30.
//

#ifndef BITMASK_DATAFILE_H
#define BITMASK_DATAFILE_H

#include <fstream>
#include <string>

class Block;

class Datafile {
 public:
  explicit Datafile(std::string file_name);
  void insert(const Block& block);

  Datafile(const Datafile& other) = delete;
  Datafile& operator=(const Datafile& other) = delete;

 private:
  std::string file_name_;
  std::fstream io_;
};

#endif  // BITMASK_DATAFILE_H
