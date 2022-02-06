//
// Created by ardxwe on 2022/1/31.
//

#include "Map.h"

namespace tinydb {

void Map::put(const std::string &key, const Value &value) { map_[key] = value; }

bool Map::find(const std::string &key) { return map_.find(key) != map_.end(); }

Value &Map::get(const std::string &key) { return map_[key]; }

void Map::erase(const std::string &key) { map_.erase(key); }

}  // namespace tinydb
