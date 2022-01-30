//
// Created by ardxwe on 2022/1/31.
//

#include "Database.h"

#include <memory>
#include <string>
#include <utility>

#include "Block.h"
#include "Map.h"
#include "Path.h"

namespace {
using std::make_unique;
using std::string;
}  // namespace

void Database::put(const string &key, const string &value) {
  Block block{key, value};
  std::uint64_t offset = active_file_->offset() + block.value_offset();

  if (!active_file_->insert(block)) {
    file_id_++;
    string active_file_name = Path::data_file_name(file_id_);
    old_files_.push_back(move(active_file_));
    active_file_ = make_unique<Datafile>(active_file_name);

    // updated file has new offset
    offset = active_file_->offset() + block.value_offset();
    active_file_->insert(block);
  }

  Value v = {
      file_id_,
      value.size(),
      offset,
      block.timestamp(),
  };
  hashmap_.put(key, v);
}

Database::Database() {
  string active_file_name = Path::data_file_name(file_id_);
  active_file_ = make_unique<Datafile>(active_file_name);
}
