#include <string>

#include "Database.h"
#include "gtest/gtest.h"

namespace {
using std::string;
}  // namespace

TEST(PutSuite, put) {
  Database db;
  string key = "add";
  string value = "hello";
  db.put(key, value);
  string get = db.get(key);

  ASSERT_EQ(get, value);
}