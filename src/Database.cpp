//
// Created by ardxwe on 2022/1/31.
//

#include "Database.h"

#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

#include "Block.h"
#include "Map.h"
#include "Path.h"

namespace {
using std::make_unique;
using std::string;
using std::uint64_t;
}  // namespace

namespace tinydb {

Database::Database() {
  string active_file_name = Path::data_file_name(file_id_);
  active_file_ = make_unique<Datafile>(active_file_name);
}

void Database::put(const string &key, const string &value) {
  const Block block{key, value};

  assert(Datafile::include(block));

  std::uint64_t offset = active_file_->offset() + block.value_offset();

  if (!active_file_->insert(block)) {
    file_id_++;
    string active_file_name = Path::data_file_name(file_id_);
    old_files_.push_back(active_file_->filename());
    active_file_ = make_unique<Datafile>(active_file_name);

    // updated file has new offset
    offset = active_file_->offset() + block.value_offset();
    active_file_->insert(block);
  }

  // del
  if (value.empty()) {
    return;
  }

  Value v = {
      file_id_,
      value.size(),
      offset,
      block.timestamp(),
  };
  hashmap_.put(key, v);
}

void Database::del(const string &key) {
  put(key, string{});
  hashmap_.erase(key);
}

std::string Database::get(const string &key) {
  // assume all key in memory
  if (!hashmap_.find(key)) {
    return string{};
  }

  auto &value = hashmap_.get(key);

  if (Path::data_file_name(value.file_id) == active_file_->filename()) {
    return active_file_->read(value.offset, value.value_size);
  }

  string target_file_name = Path::data_file_name(value.file_id);
  auto target_file = make_unique<Datafile>(target_file_name, true);
  string s = target_file->read(value.offset, value.value_size);
  return s;
}

}  // namespace tinydb
