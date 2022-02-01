//
// Created by ardxwe on 2022/1/31.
//

#ifndef SRC_DATABASE_H_
#define SRC_DATABASE_H_

#include <memory>
#include <string>
#include <vector>

#include "Datafile.h"
#include "Map.h"

class Database {
 public:
  Database();
  Database(const Database& other) = delete;
  Database& operator=(const Database& other) = delete;

  void put(const std::string& key, const std::string& value);
  void del(const std::string& key);
  std::string get(const std::string& key);

 private:
  std::vector<std::string> old_files_{};
  std::unique_ptr<Datafile> active_file_{};
  Map hashmap_{};

  std::uint64_t file_id_ = 0;
};

#endif  // SRC_DATABASE_H_
