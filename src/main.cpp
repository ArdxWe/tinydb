#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

#include "Database.h"

namespace {
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

class Random {
 public:
  Random() : uniform_dist_{0, 25} {
    char start = 'a';
    for (int i = 0; i < 26; i++) {
      arr_[i] = start + i;
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
  std::random_device r_{};

  std::default_random_engine e_{};
  std::uniform_int_distribution<int> uniform_dist_;

  std::array<char, 26> arr_{};
};
}  // namespace

int main() {
  auto start = std::chrono::steady_clock::now();

  std::uint64_t bytes = 0;
  Random r;
  unordered_map<string, string> map;
  Database db;

  for (int i = 1; i < 40000; i++) {
    string key = r.get(i % 58);
    string value = r.get(i % 20000);
    map[key] = value;
    db.put(key, value);
  }

  for (auto& pair : map) {
    bytes += pair.first.size() + pair.second.size();
    if (db.get(pair.first) != pair.second) {
      cout << "error" << endl;
      break;
    }
  }

  std::cout << "items: " << map.size() << std::endl;
  std::cout << "bytes: " << bytes / 1024.0 / 1024.0 / 1024.0 << "GB"
            << std::endl;
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds =
      std::chrono::duration<double>(end - start);

  std::cout << "time: " << elapsed_seconds.count() << "s\n";

  return 0;
}
