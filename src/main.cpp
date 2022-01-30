#include <string>

#include "Block.h"
#include "Datafile.h"

using namespace std;

int main() {
  string key = "fuck";
  string value = "adder";

  Block block{key, value};
  Datafile file{"y"};
  file.insert(block);
  file.insert(block);
  for (int i = 0; i < 10000000; i++) {
    file.insert(block);
  }
  return 0;
}
