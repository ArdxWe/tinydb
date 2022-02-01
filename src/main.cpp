#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

#include "Database.h"

namespace {
using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uint64_t;
using std::uniform_int_distribution;
using std::unordered_map;
using std::chrono::duration;
using std::chrono::steady_clock;

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

int main() {
  uint64_t bytes = 0;
  Random r;
  unordered_map<string, string> map;
  Database db;

  for (int i = 1; i < 1000000; i++) {
    string key = r.get(i % 0x100);
    string value = r.get(i % 0x1000);
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
  return 0;
}
