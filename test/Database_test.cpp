#include "Database.h"

#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace {
using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::pair;
using std::random_device;
using std::string;
using std::uint64_t;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;
using std::chrono::duration;
using std::chrono::steady_clock;
using tinydb::Database;

const int kSize = 26;
class Random {
 public:
  Random() : e_{r_()}, uniform_dist_{0, kSize - 1} {
    char start = 'a';
    for (int i = 0; i < 26; i++) {
      arr_[i] = static_cast<char>(start + i);
    }
  }

  string get(int size) {
    string res;
    for (int i = 0; i < size; i++) {
      res += arr_[uniform_dist_(e_)];
    }
    return res;
  }

 private:
  random_device r_{};

  default_random_engine e_;
  uniform_int_distribution<int> uniform_dist_;

  array<char, kSize> arr_{};
};
}  // namespace

TEST(DatabaseTest, put) {
  Database db;

  string key = "add";
  string value = "ardxwe";
  db.put(key, value);
  string get = db.get(key);
  ASSERT_EQ(get, value);

  int size = 10000;
  for (int i = 0; i < size; i++) {
    db.put(key, value);
  }
  string expected = value + "f";
  db.put(key, expected);
  ASSERT_EQ(db.get(key), expected);

  uint64_t bytes = 0;
  Random r;
  unordered_map<string, string> map;
  size = 100000;

  for (int i = 1; i < size; i++) {
    key = r.get(i % 0x100);
    value = r.get(i % 0x1000);
    map[key] = value;
  }

  auto start = steady_clock::now();

  for (const auto& pair : map) {
    db.put(pair.first, pair.second);
  }

  for (const auto& pair : map) {
    bytes += pair.first.size() + pair.second.size();

    if (db.get(pair.first) != pair.second) {
      cout << "error" << endl;
      break;
    }
  }

  cout << "pairs: " << map.size() << endl;
  cout << "bytes: " << static_cast<double>(bytes) / 1024 / 1024 / 1024 << "GB"
       << endl;

  auto end = steady_clock::now();
  duration<double> elapsed_seconds = duration<double>(end - start);

  cout << "time: " << elapsed_seconds.count() << "s" << endl;
}

TEST(DatabaseTest, put_del) {
  Database db;

  string key = "add";
  string value = "trade off";

  db.put(key, value);
  ASSERT_EQ(db.get(key), value);

  db.del(key);
  ASSERT_EQ(db.get(key), "");

  ASSERT_EQ(db.get("t"), "");
}

TEST(DatabaseTest, get) {
  Database db;

  ASSERT_EQ(db.get("key"), "");

  vector<pair<string, string>> v = {
      pair{"add", "add"},
      pair{"upper", "upper"},
      pair{"fuck", "fuck"},
      pair{"ardxwe", "ardxwe"},
      pair{"operating system", "database"},
  };

  for (const auto& item : v) {
    db.put(item.first, item.second);
    ASSERT_EQ(db.get(item.first), item.second);
  }
}
