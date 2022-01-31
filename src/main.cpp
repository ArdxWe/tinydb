#include <iostream>
#include <string>

#include "Database.h"

namespace {
using std::string;
}  // namespace

int main() {
  Database db;
  string key = "fuck";
  string value = "adder";

  for (int i = 0; i < 500000; i++) {
    db.put(key, value + 'y');
  }

  db.put(key, "ardxwe");
  db.put("t", "hello");
  db.del("t");
  std::cout << db.get(key) << std::endl;

  return 0;
}
