/**
 * /mnt/z/my_git/RCRS-CSD-327/src/Main.cpp
 * @file Main.cpp
 * @author Avinal Kumar
 * @since February 18, 2021
 *
 * The driver code
 */

#include "Utils.hpp"
using namespace MCPS;
int main(int argc, char const *argv[]) {
  fileop start;
  auto data = start.scan_current_directory();

  for (auto d : data) {
    d.second.print();
  }
  return 0;
}
