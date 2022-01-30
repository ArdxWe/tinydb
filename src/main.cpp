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
    db.put(key, value);
  }
  return 0;
}
